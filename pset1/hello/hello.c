#include <stdio.h>
#include <cs50.h>


int main(void)
{
    // Request string input from user
    string name = get_string("Your name?\n");
    // Print result
    printf("hello, %s\n", name);
}
