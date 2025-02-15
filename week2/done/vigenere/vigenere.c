// gcc -o vigenere vigenere/vigenere.c cs50.c
// ./vigenere

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
    string Lit_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lit_list = "abcdefghijklmnopqrstuvwxyz"; 
    int len_code = strlen(argv[1]);
    string code = argv[1];
    int c = 0;
    int counter = 0;
    char symbol = 0;
    int text_code[len_code];
    
    


    for (int i = 0; i != len_code;i++)
    {
        int num = (int) code[i];
        text_code[i] = num; 
        for (int h = 0; h != 10;h++)
        {  
            if(code[i] == num_list[h])
            {
                printf("Usage: ./caesar key");
                return 1;
            }
        }
    }

    string text = get_string("plaintext: ");
    int len_text = strlen(text); 
    char code_code[len_text+1];
    int v = 0;
    for(int i = 0; i < len_text; i++){
        int num = (int) text[i];
        if ((num >= 97 && num <= 122) || (num >= 65 && num <= 90))
        {
            code_code[i] = code[v];
            if (v == len_code-1)
            {
                v = 0;
            }
            else
            {
                v++;
            }
        }
        
    }
 
    printf("ciphertext: ");
    for (int i = 0; i != len_text;i++)
    {
        int num = (int) text[i];
        
        if ((num >= 97 && num <= 122))
        {
            for (int l = 0; l != 27;l++)
            {
                if (code_code[i] == lit_list[l] || code_code[i] == Lit_list[l])
                {
                    c = l;
                }
            }
            
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
            for (int l = 0; l != 27;l++)
            {
                if (code_code[i] == lit_list[l] || code_code[i] == Lit_list[l])
                {
                    c = l;
                }
            }

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
    return 0;
}
    
        
    
