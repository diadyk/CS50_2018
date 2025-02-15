// gcc -o caesar caesar/caesar.c cs50.c
// ./caesar

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cs50.h"

int main(int argc,string argv[])
{
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    string num_list = "0123456789";
    string code = argv[1];
    int len_code = strlen(argv[1]);
    int c = atoi(code);
    int counter = 0;
    char symbol = 0;
    int text_code[len_code];
    string text = get_string("plaintext: ");
    int len_text = strlen(text); 
    
    while (c > 26)
    {
        c -= 26;
    }
    
    
    for (int i = 0; i != len_code;i++)
    {
        int num = (int) code[i];
        text_code[i] = num; 
        for (int h = 0; h != 10;h++)
        {  
            if(code[i] == num_list[h])
            {
                counter++;
            }
        }
    }
    
    if (counter == len_code){
        
        printf("ciphertext: ");
        for (int i = 0; i != len_text;i++)
        {
            int num = (int) text[i];
            if ((num >= 97 && num <= 122))
            {
                if (num + c > 122)
                {
                    symbol = 96+(c-(122-num));
                    printf("%c",symbol);
                }
                else
                {
                    symbol = text[i] + c;
                    printf("%c",symbol);
                }
            }

            else if (num >= 65 && num <= 90)
            {
                 if (num + c > 90)
                {
                    symbol = 64+(c-(90-num));
                    printf("%c",symbol);
                }
                else
                {
                    symbol = text[i] + c;
                    printf("%c",symbol);
                }
            }

            else
            {
                symbol = text[i];
                printf("%c",symbol);
            }    
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key");
    }
}
