# include <stdio.h>
// function main to cause signfaault 
int main(void)
{
    // we can cause a segfault by deferencing a invliad memory 
    int i = 0;
    char *str = "hello";
    while (i < 100000)
    {
        printf("%c", str[i]);
        i++;
    }

}