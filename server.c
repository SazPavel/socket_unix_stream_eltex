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
    char buf[16];
    char buf2[] = "priv\n";
    int sock, bytes_read;
    struct sockaddr_un addr;
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(-1);
    }
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SERVER_PATH);
    unlink(SERVER_PATH);
    if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(-1);
    }
    listen(sock, 1);
    sock = accept(sock, NULL, NULL);
    if(sock < 0)
    {
        perror("sock2");
        exit(-1);
    }
    bytes_read = recv(sock, buf, 16, 0);
    printf("%d %s\n", bytes_read, buf);
    send(sock, buf2, sizeof(buf2), 0);
    close(sock);
    exit(0);
}
