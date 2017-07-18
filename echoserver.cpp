#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
   LOG(INFO) << "server start";
   int listenfd;
   if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
       LOG(ERROR) << "create socket for server fail";
       return -1;
   }
   
   
   // set server address and port
   struct sockaddr_in serve;
   memset(&serve, 0, sizeof(serve));
   serve.sin_family = AF_INET;
   serve.sin_addr.s_addr = 

   

   

   return 0;
}
