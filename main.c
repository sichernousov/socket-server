#include "sequence.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
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
            while(1)
            {
                bytes_read = recv(sock, buf, 1024, 0);
                if(bytes_read <= 0) break;
                generate_one(buf, s1, s2, s3, 0);
                send(sock, buf, strlen(buf), 0);
                generate_one(buf, s1, s2, s3, 1);
                send(sock, buf, strlen(buf), 0);
                generate_one(buf, s1, s2, s3, 2);
                send(sock, buf, strlen(buf), 0);
            }

            close(sock);
            _exit(0);
            
        default:
            close(sock);
        }
    }
    
    close(listener);

    return 0;
}
