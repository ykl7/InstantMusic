#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in server, client;
    sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = INADDR_ANY;

    printf("Binding server...");

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    listen(sockfd, 5);
    socklen_t clen = sizeof(client);
    int newsockfd;

    while(1) {
        printf("Waiting for client.");
        newsockfd = accept(sockfd, (struct sockaddr *)&client, &clen);
        pid_t pid = fork();
        if(pid == 0) {
            printf("\nClient connection opened. Transferring.\n");
            int fd = open("./MusicProvider/closer.mp3", O_RDONLY);
            char buff[BUFFER_SIZE + 1];
            if(fd == -1) {
              printf("Shit no");
            }
            else {
              int nob;
              while((nob = read(fd, buff, BUFFER_SIZE)) > 0) {
                printf("Bytes: %d\n", nob);
                printf("Sending...\n");
                send(newsockfd, buff, nob, 0);
              };
              printf("Done.\n");
              close(fd);
            }
            close(newsockfd);
            exit(1);
        }
    }
    close(sockfd);
    return 0;
}