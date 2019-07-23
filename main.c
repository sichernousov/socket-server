#include "general_types.h"
#include "sequence.h"
#include "parse.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const char hello_msg[] = "\nServer: Enter the command\n";
const char ok_msg[] = "\nServer: Ok!\n";
const char err_msg_1[] = "\nServer: Error. Invalid command\n";
const char err_msg_2[] = "\nServer: Error. All sequences are empty\n";

int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char in_buf[BUF_LEN];
    char out_buf[BUF_LEN];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1);
    
    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }
        
        switch(fork())
        {
            case -1:
                perror("fork");
            break;
            
            case 0:
                close(listener);

                seq_t * s1 = create_seq();
                seq_t * s2 = create_seq();
                seq_t * s3 = create_seq();
                do
                {
                    memset(out_buf, '\0', BUF_LEN);
                    memset(in_buf, '\0', BUF_LEN);
                    send(sock, hello_msg, strlen(hello_msg), 0);
                    bytes_read = recv(sock, in_buf, BUF_LEN, 0);
                    if(bytes_read > 0)
                    {
                        //Парсим входной буфер
                        parse_t pars = {0, 0, 0};
                        if (parse_buf(in_buf, &pars))
                        { 
                            //Выполняем команды
                            switch (pars.cmd)
                            {
                                case CMD_ExportSeq:
                                    if (generate_seq(out_buf, BUF_LEN, s1, s2, s3))
                                      send(sock, out_buf, strlen(out_buf), 0);
                                    else
                                      send(sock, err_msg_2, strlen(err_msg_2), 0);
                                break;

                                case CMD_SetSeq1:
                                    set_param_seq (s1, pars.param1, pars.param2);
                                    send(sock, ok_msg, strlen(ok_msg), 0);
                                break;

                                case CMD_SetSeq2:
                                    set_param_seq (s2, pars.param1, pars.param2);
                                    send(sock, ok_msg, strlen(ok_msg), 0);
                                break;

                                case CMD_SetSeq3:
                                    set_param_seq (s3, pars.param1, pars.param2);
                                    send(sock, ok_msg, strlen(ok_msg), 0);
                                break;

                                default:
                                    send(sock, err_msg_1, strlen(err_msg_1), 0);
                                break;
                            }
                        }
                        else
                          send(sock, err_msg_1, strlen(err_msg_1), 0);
                    }
                }while (bytes_read > 0);

                delete_seq(s1);
                delete_seq(s2);
                delete_seq(s3);

                close(sock);
                _exit(0);
            break;

            default:
                close(sock);
        }
    }   
    close(listener);

    return 0;
}
