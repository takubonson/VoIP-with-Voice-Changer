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

int main(int argc, char ** argv){
    if (argc != 3){perror("input FAILED");exit(1);}
    char* input_address = argv[1];
    int input_port = atoi(argv[2]);

    int s = socket(PF_INET, SOCK_STREAM, 0);
    if(s == -1){perror("socket FAILED"); exit(1);}

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    int addr_ret = inet_aton(input_address, &addr.sin_addr);
    if(addr_ret==0){perror("IP_address_input FAILED"); exit(1);}
    addr.sin_port = htons(input_port);
    int ret = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    if (ret ==-1){perror("connect FAILED"); exit(1);}

    char data[LEN];
    FILE *play_input = popen("./pitch_shift_exec 8192 | play -t raw -b 16 -c 1 -e s -r 44100 - ", "w");

    while (1)
    {
        int receive_num = recv(s, data, LEN, 0);
        if (receive_num == -1){perror("receive_FAILED"); exit(1);}
        if (receive_num == 0) break;
        int write_num = fwrite(data, sizeof(char), receive_num, play_input);
        // write(1, data, receive_num);
    }
    pclose(play_input);
    close(s);
}