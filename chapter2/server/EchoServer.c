#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <unistd.h>

#define PORT 8080

int main(){
  int i;
  int srcSocket;
  int dstSocket; 
  struct sockaddr_in srcAddr;
  struct sockaddr_in dstAddr;
  socklen_t dstAddrSize = sizeof(dstAddr);

  int status;
  int numrcv;
  char buf[1024];

  while(1){
    bzero((char *)&srcAddr, sizeof(srcAddr));
    srcAddr.sin_port = htons(PORT);
    srcAddr.sin_family = AF_INET;
    srcAddr.sin_addr.s_addr = INADDR_ANY;
    
    srcSocket = socket(AF_INET, SOCK_STREAM, 0);
    bind(srcSocket, (struct sockaddr *)&srcAddr, sizeof(srcAddr));
    listen(srcSocket, 1);
    
    printf("接続を待っています\nクライアントプログラムを動かして下さい\n");
    dstSocket = accept(srcSocket, (struct sockaddr *)&dstAddr, &dstAddrSize);
    printf("%s から接続を受けました\n",inet_ntoa(dstAddr.sin_addr));
    close(srcSocket);
        
    while(1){
      numrcv = read(dstSocket, buf, 1024);
      if(numrcv ==0 || numrcv ==-1 ){
	close(dstSocket); break;
      }
      printf("変換前 %s",buf);
      for (i=0; i< numrcv; i++){ 
	if(isalpha(buf[i])) buf[i] = toupper(buf[i]);
      }
      write(dstSocket, buf, 1024);
      fprintf(stdout,"→ 変換後 %s \n",buf);
    }
  }
  return(0);
}