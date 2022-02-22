#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#define LEN 1000

int main(int argc, char **argv){
    if (argc != 2){perror("input FAILED");exit(1);}
    int input_port = atoi(argv[1]);

    int ss = socket(PF_INET, SOCK_STREAM, 0);
    if(ss == -1){perror("socket FAILED"); exit(1);}

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(input_port);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(ss, (struct sockaddr *)&addr, sizeof(addr));
    listen(ss, 10);

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    int s = accept(ss, (struct sockaddr *)&client_addr, &len);
    close(ss);

    FILE *rec_output = popen("rec -t raw -b 16 -c 1 -e s -r 44100 -", "r");    

    char data[LEN];
    while (1)
    {
        int read_num = fread(data, sizeof(char), LEN, rec_output);
        if (read_num == -1){perror("read_FAILED"); exit(1);}
        if (read_num == 0) break;
        int send_num = send(s, data, read_num, 0);
        if (send_num == -1){perror("send_FAILED"); exit(1);}
    }
    
    pclose(rec_output);
    close(s);
}