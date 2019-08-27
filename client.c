#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define SERVER_PATH "./serv"

int main()
{
    int sock, bytes_read;
    char buf[] = "HI!\n";
    struct sockaddr_un addr;
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(-1);
    }
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SERVER_PATH);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(-1);
    }
    send(sock, buf, sizeof(buf), 0);
    bytes_read = recv(sock, buf, 16, 0);
    printf("%d %s\n", bytes_read, buf);
    unlink(SERVER_PATH);
    close(sock);
    exit(0);
}
