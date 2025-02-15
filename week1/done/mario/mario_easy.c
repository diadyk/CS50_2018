// gcc -o mario_easy mario/mario_easy.c cs50.c
// ./mario_easy

#include <stdio.h>
#include "cs50.h"

int main(void)
{
    int a = 1;
    int num = get_int("Height: ");
    while (num > 8 || num < 1){
        while (num > 8 || num < 1)
        {
            num = get_int("Height: ");  
        }  
    printf("Stored: %d\n",num);    
    } 

    while (a <= num)
    {
        for (int b = 0;num-b > a;b++)
        {
            printf(" ");
        }
        for (int b = 0;b < a;b++)
        {
            printf("#");
        }
    printf("\n");   
    a++;
    }
}