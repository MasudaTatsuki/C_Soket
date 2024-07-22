#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    char hostname[256];
    struct hostent *host_info;
    struct in_addr **addr_list;

    printf("Enter a URL: ");
    scanf("%255s", hostname);

    // URLからホスト情報を取得
    if ((host_info = gethostbyname(hostname)) == NULL) {
        // エラー処理
        herror("gethostbyname");
        return 1;
    }

    // IPアドレスのリストを取得
    addr_list = (struct in_addr **)host_info->h_addr_list;

    // 最初のIPアドレスを表示
    printf("IP Address: %s\n", inet_ntoa(*addr_list[0]));

    return 0;
}
