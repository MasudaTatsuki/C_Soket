#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ECHOMAX 255 /* エコー文字列の最大長 */

void DieWithError(char *errorMessage); /* 外部エラー処理関数 */

int main(int argc, char *argv[])
{
    int sock;                         /* ソケットディスクリプタ */
    struct sockaddr_in echoServAddr;  /* エコーサーバーのアドレス */
    struct sockaddr_in fromAddr;      /* エコー送信元のアドレス */
    unsigned short echoServPort;      /* エコーサーバのポート番号 */
    unsigned int fromSize;            /* recvfrom()のアドレスの入出力サイズ*/
    char *servIP;                     /* サーバのIPアドレス */
    char *echoString;                 /* エコーサーバへ送信する文字列 */
    char echoBuffer[ECHOMAX+1];       /* エコー文字列の受信用バッファ */
    int echoStringLen;                /* エコー文字列の長さ */
    int respStringLen;                /* 受信した応答の長さ */

    if ((argc < 3) || (argc > 4))
    {
        fprintf(stderr, "Usage: %s <Server IP> <Echo World> [<Echo Port>]\n", argv[0]);
        exit(1);
    }

    servIP = argv[1];
    echoString = argv[2];

    if ((echoStringLen = strlen(echoString)) > ECHOMAX)
        DieWithError("Echo word too long");

    if (argc == 4)
        echoServPort = atoi(argv[3]);
    else
        echoServPort = 7;

    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("socket() failed");

    memset(&echoServAddr, 0, sizeof(echoServAddr));

    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);
    echoServAddr.sin_port = htons(echoServPort);

    if (sendto(sock, echoString, echoStringLen, 0, (struct sockaddr *)
        &echoServAddr, sizeof(echoServAddr)) != echoStringLen)
        DieWithError("sendto() sent a different number of bytes than expected");

    fromSize = sizeof(fromAddr);
    if ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0,
        (struct sockaddr *) &fromAddr, &fromSize)) != echoStringLen)
        DieWithError("recvfrom() failed");

    if (echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
    {
        fprintf(stderr, "Error: received a packet from unknown source.\n");
        exit(1);
    }

    echoBuffer[respStringLen] = '\0';
    printf("Received: %s\n", echoBuffer);

    close(sock);
    exit(0);
}