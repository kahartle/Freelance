#include <stdio.h>
#include <string.h>

int main()
{
   char ch;
   char str[100];
   int val;
   
   /*
   printf("Enter any character \n");
   scanf("%c", &ch);
   printf("Entered character is %c \n", ch);
   printf("Enter any string ( upto 100 character ) \n");
   scanf("%s", &str);
   printf("Entered string is %s \n", str);
   
   printf("Give me:");
   scanf("%d", &val);
   
   printf("Entered : %d\n", val);
   */
   
   char foo[100];
   strcpy(foo, "Foopah");
   
   printf("The value of foo is %s\n", foo);
   
}