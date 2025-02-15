// gcc -o hello hello/hello.c cs50.c
// ./hello

#include <stdio.h>
#include "cs50.h"

int main(void)
{
    string name = get_string("Name: ");
    printf("Hello, %s\n", name);
    return 0;
}
