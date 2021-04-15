#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
void signup_ui()
{
    clrscr();
    char *name;
    name = (char *)malloc(20);
    char *mno;
    mno = (char *)malloc(20);
    char *email;
    email = (char *)malloc(40);
    char *passwd;
    email = (char *)malloc(40);
    printf("\t\t\t\t\t\tWelcome to signup,enter your details below\n");
    printf("\t\t\t\t\t\tEnter your name :");
    scanf("%s", name);
    printf("\n\t\t\t\t\t\tEnter your mobile number:");
    scanf("%s", mno);
    printf("\n\t\t\t\t\t\tEnter your email id:");
    scanf("%s", email);
    printf("\n\t\t\t\t\t\tEnter your password:");
    scanf("%s", passwd);
    int status = c_newuser(name, mno, email, passwd);
    free(name);
    free(mno);
    free(email);
    free(passwd);
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
    clrscr();
    char *name;
    name = (char *)malloc(20);
    char lpswd[20];
    char c;
    int z = 0;
    //c = (char *)malloc(4);
    printf("\t\t\t\t\t\tWelcome to login,enter your details below\n");
    printf("\t\t\t\t\t\tEnter your name :");
    scanf("%s", name);
    printf("\n\t\t\t\t\t\tEnter your password:");

    while ((c = getch()) != 13)
    {
        lpswd[z++] = c;
        printf("%c", '*');
    }
    int rvalue = login_check(name, lpswd);
    printf("%d", rvalue);
    if (rvalue == 1)
    {
        main_screen_ui(name);
    }
    else if (rvalue == 2)
    {
        printf("\n\t\t\t\t\t\tSorry,your entered password is wrong,please try again\n");
        delay(2);
        login_ui();
    }
    else if (rvalue == 3)
    {
        printf("\t\t\t\t\t\tSorry,this user does not exist\n");
        delay(2);
        login_ui();
    }
}
uschema *userstruct(char *fp)
{
    FILE *lfp = fopen(fp, "r");
    uschema *uarr = malloc(sizeof(uschema) * 20);
    char name[40];
    char mno[40];
    char mail[40];
    char passwd[40];
    int count = 0;
    while (fscanf(lfp, "%s %s %s %s\n", name, mno, mail, passwd) != EOF)
    {
        uarr[count].name = name;
        uarr[count].mno = mno;
        uarr[count].email = mail;
        uarr[count].passwd = passwd;
        count += 1;
    }
    fclose(fp);
    return uarr;
}

void update_file(char *path, libschema *books)
{
    FILE *fp = fopen(path, 'w');
    int flag = 0;
    while (books->author != NULL)
    {
        fprintf(fp, "%s %s %s %s %s", books->title, books->author, books->status, books->user, books->duedate);
        flag += 1;
    }
    fclose(fp);
}

int login_check(char *name, char *lpswd)
{
    uschema *cuser = userstruct("userdb.txt");
    int c = 0;
    while (cuser[c].email != NULL)
    {
        if (strcmp(cuser->name, name))
        {
            if (strcmp(cuser->passwd, lpswd) == 0)
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 3;
        }
        c += 1;
    }
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
void main_screen_ui(char *name)
{
    printf("\t\t\t\t\tYou have succesfully logged into the library\n");
    printf("\t\t\t\t\tChose your options below\n");
    printf("\t\t\t\t\t1.Check book availability\n");
    printf("\t\t\t\t\t2.Borrow book\n");
    printf("\t\t\t\t\t3.Return book\n");
}

int c_newuser(char *name, char *mno, char *email, char *passwd)
{
    FILE *fp;
    fp = fopen("userdb.txt", "a");
    fprintf(fp, "%s %s %s %s\n", name, mno, email, passwd);
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