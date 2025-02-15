// Input word. Program output hash word

// gcc -o crack_hashing crack_hashing.c cs50.c
// ./crack_hashing

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "sha1-master\sha1.c"
#include "cs50.h" 






int main() {

    SHA1_CTX sha; uint8_t results[20]; char *buf; int n;

    buf = get_string("Word to hash: ");
    n = strlen(buf); 
    SHA1Init(&sha); 
    SHA1Update(&sha, (uint8_t *)buf, n); 
    SHA1Final(results, &sha);

    printf("Hash word: ");
    for (n = 0; n < 20; n++)
    {
        printf("%02x", results[n]);
    }

    return 0;
}
    
    