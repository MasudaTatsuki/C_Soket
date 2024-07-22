# include <stdio.h>

# define BUFSIZE 132

char msgBuf[BUFSIZE];

int main() 
{
    int deposits;
    int wishdrawals;

    printf("Enter a deposits: ");
    scanf("%d", &deposits);
    printf("Enter a wishdrawals: ");
    scanf("%d", &wishdrawals);
    sprintf(msgBuf, "%d %d ", deposits, wishdrawals);
    printf("%s\n", msgBuf);
    //  send(s, msgBuf)

}