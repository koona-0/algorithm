#include <stdio.h>
#include <stdlib.h>

void hanoi(char from, char to, char spare, int ndisk){
    if(ndisk ==1) printf("%c -> %c \n", from, to);
    else{
        hanoi(from, spare, to, ndisk - 1);
        printf("%c -> %c \n", from, to);
        hanoi(spare, to, from, ndisk - 1);
    }
}

int main (){
    int ndisk = 0;

    printf("hanoi disk number : ");
    scanf("%d", &ndisk);

    if(ndisk < 1){
        printf("error : disk number >= 1\n");
        exit(0);
    }
    else{
        hanoi('A', 'B', 'C', ndisk);
    }
    return 0;
}