// gcc -o mario_hard mario/mario_hard.c cs50.c
// ./mario_hard

#include <stdio.h>
#include "cs50.h"

int space(int a, int num)
{
for (int b = 0;num-b > a;b++)
        {
            printf(" ");
        }
}


int hashtag(int a)
{
    for (int b = 0;b < a;b++)
        {
            printf("#");
        } 
}



int main(void)
{
    int a = 1;
    int num = get_int("Height: ");
    while (num > 8 || num < 1){
        while (num > 8 || num < 1)
        {
            num = get_int("Height: ");  
        }      
    } 

    while (a <= num)
    {
        
        space(a,num);
        hashtag(a);
        printf(" ");  
        hashtag(a);
        printf("\n");   
        a++;
        
    }
}
