#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void signup_ui()
{
    clrscr();
    char *name;
    name = (char *)malloc(20);
    char *mno;
    mno = (char *)malloc(20);
    char *email;
    email = (char *)malloc(40);
    printf("\t\t\t\t\t\tWelcome to signup,enter your details below\n");
    printf("\t\t\t\t\t\tEnter your name :");
    scanf("%s", name);
    printf("\n\t\t\t\t\t\tEnter your mobile number:");
    scanf("%s", mno);
    printf("\n\t\t\t\t\t\tEnter your email id");
    scanf("%s", email);
    int status = c_newuser(name, mno, email);
    if (status == 1)
    {
        printf("\n\n\t\t\t\t\t\tUser succesfully created");
        delay(2);
        clrscr();
        main_splash_screen();
    }
    else
        printf("\n\n\t\t\t\t\t\tUser creation unsuccesful");
}

void login_ui()
{
    printf("test");
}
void main_splash_screen()
{
    printf("\t\t\t\t\t\t****Welcome to our library management system!****\n");
    printf("\n\t\t\t\t\t\tChoose your option below to access the library\n");
    printf("\n\t\t\t\t\t\t\t1.Signup to the library");
    printf("\n\t\t\t\t\t\t\t2.Login to the library");
    printf("\n\n\t\t\t\t\t\tEnter your option below:\n");
    int chval;
    scanf("\t\t\t\t\t\t\t%d", &chval);

    if (chval == 1)
    {
        signup_ui();
    }

    else if (chval == 2)
    {
        login_ui();
    }

    else
    {
        printf("\t\t\t\t\tInvalid input received \n");
        delay(5);
        clrscr();
        main_splash_screen();
    }
}

int c_newuser(char *name, char *mno, char *email)
{
    FILE *fp;
    fp = fopen("userdb.txt", "a");
    fprintf(fp, "%s %s %s\n", name, mno, email);
    fclose(fp);
    return 1;
}

void clrscr()
{
    system("clear");
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}