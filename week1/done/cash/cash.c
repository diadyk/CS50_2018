// gcc -o cash cash/cash.c cs50.c
// ./cash

#include <stdio.h>
#include <math.h>
#include "cs50.h"

int number(int num, int coin)
{
    int numfun = num;
    while (numfun >= coin)
    {
        numfun = numfun-coin;
    }
    return numfun;
}

int con(int num, int coin , int coins)
{ 
    int numfun = num;
    while (numfun >= coin)
    {
        coins++;
        numfun = numfun - coin;
    }
    return coins;
}


int main(void)
{
    float dollar = get_float("Change owed: ");
    int num = roundf(dollar * 100); 

    int numfun = 0;
    int num1 = 0;
    int num5 = 0;
    int num10 = 0;
    int num25 = 0;

    int coins = 0;
    int coins1 = 0;
    int coins5 = 0;
    int coins10 = 0;
    int coins25 = 0;

    coins25 = con(num,25,coins);
    num25 = number(num,25);
    num = num25; 

    coins10 = con(num,10,coins);
    num10 = number(num,10);
    num = num10;

    coins5 = con(num,5,coins);
    num5 = number(num,5);
    num = num5;

    coins1 = con(num,1,coins);

    coins = coins1 + coins5 + coins10 + coins25; 
    printf("%d",coins);
}
    

