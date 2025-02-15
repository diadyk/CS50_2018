// Input hash password. Program generate password, hash it and compare with hash password.
// Output password

// gcc -o test test.c cs50.c
// ./test

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "sha1-master\sha1.c"
#include "cs50.h" 


int checkPassword(char password[], size_t length, string value) 
{   
    int num = 0;
    char result[41];
    int n = strlen(password);
    SHA1_CTX sha; 
    uint8_t hash_result[20];
    SHA1Init(&sha); 
    SHA1Update(&sha, (uint8_t *)password, n); 
    SHA1Final(hash_result, &sha);

    for (n = 0; n < 20; n++)
        sprintf(result + n * 2, "%02x", hash_result[n]);

    result[40] = '\0';
    if (strcmp(result, value) == 0)
    {
        
        printf("Password is %s", password);
    
        num = 1;
    }
    return num;
}

int letter(int number)
{
    if (number+65 == 90)
    {
        number = 32;
    }
    else
    {
        number = number;
    }
    return number;
}


struct KeyValue {
    char key[50];
    char value[50];
};

    
    
    


int main() {
    struct KeyValue myDictionary[6] = {
        {"login", "hash_password"}, 
        {"maxd", "d623c430b633bb8c5387bb5cefaad42b97fd3e01"}, // password:masik
        {"vasya", "76557b88a6da99a5d495eebf630073ee5c44cfa0"}, // password:ABCCB
        {"lox", "9cbf24002ae002b6a0914906c749d71633b36eb2"}, // password:BCDEF
        {"ar", "258790a5d61a8038178865c5e2ddabb5f38279c8"} // password:AAABA
    };
          
    char password[5];
    password[5] = '\0';
    size_t length = strlen(password);
    int check = 0;
    string value = get_string("Hash password: ");
    printf("%s\n",value);



    
    
    
    
    

    






    for(int i = 5; i != 0 && check != 1;i--)
    {
        for(int l = 0; l != 52 && check != 1 && i >= 1;l++)
        {
            password[0] = letter(l)+65;
            length = strlen(password);
            check = checkPassword(password, length, value);

            for(int t = 0; t != 52 && check != 1 && i >= 2;t++)
            {
                password[1] = letter(t)+65;
                length = strlen(password);
                check = checkPassword(password, length, value);

                for(int h = 0; h != 52 && check != 1 && i >= 3;h++)
                {
                    password[2] = letter(h)+65;
                    length = strlen(password);
                    check = checkPassword(password, length, value);

                    for(int v = 0; v != 52 && check != 1 && i >= 4;v++)
                    {
                        password[3] = letter(v)+65;
                        length = strlen(password);
                        check = checkPassword(password, length, value);

                        for(int n = 0; n != 52 && check != 1 && i == 5;n++)
                        {
                            password[4] = letter(n)+65;
                            printf("%c,%c,%c,%c,%c\n",password[0],password[1],password[2],password[3],password[4]);
                            printf("1)%c,%d,%d ",password[0],letter(l),l);
                            printf("2)%c,%d,%d ",password[1],letter(t),t);
                            printf("3)%c,%d,%d ",password[2],letter(h),h);
                            printf("4)%c,%d,%d ",password[3],letter(v),v);
                            printf("5)%c,%d,%d ",password[4],letter(n),n);
                            printf("%d,%d,%d,%d,%d\n",l,t,h,v,n);
                            printf("\n");
                            length = strlen(password);              
                            check = checkPassword(password, length, value); 
                            //printf("%d\n",i);
                            
                                  
                        }
                    }
                }
            }
        }
    }    
    

    return 0;
}    
