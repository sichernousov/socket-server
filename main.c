#include "sequence.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUF_LEN 128

int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
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
            set_param_seq(s1, 1, 1);
            set_param_seq(s2, 2, 2);
            set_param_seq(s3, 3, 3);
            memset(out_buf, '\0', BUF_LEN);

            while(1)
            {
                bytes_read = recv(sock, buf, 1024, 0);
                if(bytes_read <= 0) break;

                generate_seq(out_buf, 128, s1, s2, s3);
                send(sock, out_buf, strlen(out_buf), 0);
            }

            delete_seq(s1);
            delete_seq(s2);
            delete_seq(s3);

            close(sock);
            _exit(0);
            
        default:
            close(sock);
        }
    }
    
    close(listener);

    return 0;
}
