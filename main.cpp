#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define HELLO_WORLD_SERVER_PORT    4050
#define LENGTH_OF_LISTEN_QUEUE     20
#define BUFFER_SIZE                1024

typedef struct
{
    int ab;
    int num[1000000];
}Node;


typedef struct
{
    char TradingDay[9];
    char InstrumentID[31];
    double LastPrice;
    int Volume;
}Ticker;
#define MAXBUF 65536

int main(int argc, char **argv)
{
    int sock, status, buflen;
    unsigned sinlen;
    char buffer[MAXBUF];
    struct sockaddr_in sock_in;
    int yes = 1;
    sinlen = sizeof(struct sockaddr_in);
    memset(&sock_in, 0, sinlen);
    sock = socket (PF_INET, SOCK_DGRAM, 0);
    sock_in.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    sock_in.sin_port = htons(4050);
    sock_in.sin_family = PF_INET;
    status = bind(sock, (struct sockaddr *)&sock_in, sinlen);
    printf("Bind Status = %d\n", status);
    status = getsockname(sock, (struct sockaddr *)&sock_in, &sinlen);
    printf("Sock port %d\n",htons(sock_in.sin_port));
    buflen = MAXBUF;
    memset(buffer, 0, buflen);
    Ticker *myTicker=(Ticker*)malloc(sizeof(Ticker));
    int needRecv=sizeof(Ticker);
    while(1)
    {

        status = recvfrom(sock, buffer, buflen, 0, (struct sockaddr *)&sock_in, &sinlen);
        printf("sendto Status = %d\n", status);

        memcpy(myTicker,buffer,needRecv);
        printf("recv over TradingDay=%s InstrumentID=%s LastPrice=%f Volume=%d \n", myTicker->TradingDay,
               myTicker->InstrumentID, myTicker->LastPrice, myTicker->Volume);


        printf("%s\n", inet_ntoa(sock_in.sin_addr));
        printf("%s\n", buffer);
        //bzero(buffer, 256);
        bzero(buffer, needRecv);
    }


//    while(1)
//    {
//        struct sockaddr_in client_addr;
//        socklen_t          length = sizeof(client_addr);
//
//
//        Ticker *myTicker=(Ticker*)malloc(sizeof(Ticker));
//
//        int recTimes = 1000;
//        int needRecv=sizeof(Ticker);
//        char *buffer=(char*)malloc(needRecv);
//        while(recTimes > 0){
//            recTimes--;
//            printf("%s\n", inet_ntoa(client_addr.sin_addr));
//            int pos=0;
//            int len;
//
//            int status = recvfrom(server_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&sock_in, (socklen_t* )&sinlen);
////            len = recv(new_server_socket, buffer+pos, BUFFER_SIZE, 0);
//
//            printf("sock_in = %s\n", inet_ntoa(sock_in.sin_addr));
//
//            memcpy(myTicker,buffer,needRecv);
//            printf("recv over TradingDay=%s InstrumentID=%s LastPrice=%f Volume=%d \n", myTicker->TradingDay,
//                   myTicker->InstrumentID, myTicker->LastPrice, myTicker->Volume);
//            bzero(buffer, needRecv);
//        }
//
//        close(server_socket);
//
//        free(buffer);
//        free(myTicker);
//    }
//    close(server_socket);

    return 0;
}