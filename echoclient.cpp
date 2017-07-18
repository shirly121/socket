#include <sys/types.h>
#include <sys/socket.h>
#include "easylogging++.h"

static const int LINEMAX = 1024;

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
    LOG(INFO) << "My first info log using default logger:";
    // create socket
    int clientfd;
    if((clientfd = socket(AF_INET, SOCK_STREAM, 0)) > 0){
        LOG(ERROR) << "create socket for client fail";
        return -1;
    }

    // set socket address and port of server
    struct sockaddr_in serve;
    // pad
    memset(&serve, 0, sizeof(serve));
    // address first
    char *host = argv[1];
    int port = argv[2];
    struct hostent *hp = gethostbyname(host);
    memcpy(&serve.sin_addr.s_addr, hp->h_addr_list[0], hp->h_length);
    // port
    serve.sin_port = htons(port); 

    // connect to server
    if(connect(clientfd, (struct sockaddr *)&serve, sizeof(serve)) < 0){
        LOG(ERROR) << "connect to server fail";
        return -1;
    }

    // send request and fetch response
    char buf[LINEMAX];
    while(fgets(buf, LINEMAX, stdin) != NULL){
        rio_writen(clientfd, buf, strlen(buf));
        rio_readline(clientfd, buf, LINEMAX);
        printf("response is: %s\n", buf);
    }

    close(clientfd);
    return 0;
}
