// gcc -o credit credit/credit.c cs50.c
// ./credit

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "cs50.h"



int doubles(long* list_num_fun,int length)
{
    
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (i % 2 == 0)
        {
            if (list_num_fun[i] * 2 > 9)
            {
                sum += (list_num_fun[i] * 2) - 10;
                sum += 1;
            }
            else
            {
                sum += list_num_fun[i] * 2;
            }
        }   
    }
    return sum;   
}


int singles(long* list_num_fun,int length)
{
    int sum = 0;
    for (int i = 0; i < length+1; i++) {
        if (i % 2 == 1)
        {
            sum += list_num_fun[i];
        }   
    }
    return sum; 
      
}



int main(void)
{
    int sum = 0;
    char card[20];
    printf("Number: ");
    fgets(card,sizeof(card), stdin);
    int length = strlen(card) - 1;

    long card_nums_long[length];
    for (int i = 0; i < strlen(card); i++) {
        card_nums_long[i] = card[i] - '0';
    }

    
    int dou = doubles(card_nums_long,length);
    
    int sin = singles(card_nums_long,length);
    
    sum = sin+dou;
    //printf("%d",sum);
    
    if (sum % 10 == 0 && length == 15 && card_nums_long[0] == 3 && card_nums_long[1] == 4 || card_nums_long[1] == 7)
    {
        printf("AMEX\n");
    }  
    else if (sum % 10 == 0 && length == 16 && card_nums_long[0] == 5 && (card_nums_long[1] == 1 || card_nums_long[1] == 2 || card_nums_long[1] == 3 || card_nums_long[1] == 4 || card_nums_long[1] == 5))
    {
        printf("MASTERCARD\n");
    }
    else if (sum % 10 == 0 && card_nums_long[0] == 4 && (length == 13  || length == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }  

}





