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
    passwd = (char *)malloc(40);
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
    lpswd[z] = '\0';
    //printf("%s", lpswd);
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
        printf("\n\t\t\t\t\t\tSorry,this user does not exist\n");
        delay(2);
        login_ui();
    }
    free(name);
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
        strcpy(uarr[count].name, name);
        strcpy(uarr[count].mno, mno);
        strcpy(uarr[count].email, mail);
        strcpy(uarr[count].passwd, passwd);
        count += 1;
    }
    fclose(lfp);
    return uarr;
}

libschema *libstruct(char *fp)
{
    FILE *lfp = fopen(fp, "r");
    libschema *uarr = malloc(sizeof(uschema) * 20);
    char title[40];
    char author[40];
    char status[40];
    char user[40];
    char duedate[40];
    int count = 0;
    int tcount = 0;
    while (tcount != 20)
    {
        strcpy(uarr[tcount].title, "\0");
        tcount += 1;
    }
    while (fscanf(lfp, "%s %s %s %s %s\n", title, author, status, user, duedate) != EOF)
    {
        strcpy(uarr[count].title, title);
        strcpy(uarr[count].author, author);
        strcpy(uarr[count].status, status);
        strcpy(uarr[count].user, user);
        strcpy(uarr[count].duedate, duedate);
        count += 1;
    }
    fclose(lfp);
    return uarr;
}

void update_file(char *path, libschema *books)
{
    FILE *fp = fopen(path, "w");
    int flag = 0;
    while (flag < 5)
    {
        fprintf(fp, "%s %s %s %s %s\n", books[flag].title, books[flag].author, books[flag].status, books[flag].user, books[flag].duedate);
        flag += 1;
    }
    fclose(fp);
}

void show_avail(char *path, char *name)
{
    clrscr();
    libschema *listbooks = libstruct(path);
    int cr = 0;
    printf("\t\t\t\tList of available books are\n");
    printf("\t\t\t\tTitle Author Status\n");
    printf("\t\t\t\t--------------------\n");
    while (cr != 5)
    {
        printf("\t\t\t\t%s %s %s\n\n", listbooks[cr].title, listbooks[cr].author, listbooks[cr].status);

        cr += 1;
    }
    main_screen_ui("user");
}

int login_check(char *name, char *lpswd)
{
    uschema *cuser = userstruct("userdb.txt");
    int c = 0;
    while (cuser[c].email != NULL)
    {
        if (strcmp(cuser[c].name, name) == 0)
        {
            //printf("%s\n", lpswd);
            //printf("%s", cuser[c].passwd);
            if (strcmp(cuser[c].passwd, lpswd) == 0)
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
        c += 1;
    }
    return 3;
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
    int choice;
    scanf("\t\t\t\t%d", &choice);
    if (choice == 1)
    {
        show_avail("libdb.txt", name);
    }
    if (choice == 2)
    {
        borrow_flow("libdb.txt", name);
    }
    if (choice == 3)
    {
        return_flow("libdb.txt", name);
    }
}

void borrow_flow(char *path, char *name)
{
    libschema *out = libstruct(path);
    char title[50];
    printf("\t\t\t\tPlease enter the name of the book would like to borrow below");
    scanf("%s", title);
    int count = 0;
    while (count < 5)
    {
        printf("%s", out[count].title);
        if (strcmp(out[count].title, title) == 0)
        {
            if (strcmp(out[count].status, "Available") == 0)
            {
                time_t seconds;
                seconds = (time(NULL) / 3600) + 72;
                char time[50];
                itoa(seconds, time, 10);
                printf("\t\t\t\tyou have successfully borrowed the book\n");
                strcpy(out[count].status, "Borrowed");
                strcpy(out[count].duedate, time);
                strcpy(out[count].user, name);
                update_file("libdb.txt", out);
                main_screen_ui(name);
            }
            else
            {
                printf("\t\t\t\tEntered book is not available\n");
            }
        }
        else
        {
            count += 1;
            continue;
        }
    }
    printf("\t\t\t\tEntered book is not available in our inventory\n");
}

int c_newuser(char *name, char *mno, char *email, char *passwd)
{
    FILE *fp;
    fp = fopen("userdb.txt", "a");
    fprintf(fp, "%s %s %s %s\n", name, mno, email, passwd);
    fclose(fp);
    return 1;
}

void return_flow(char *path, char *name)
{
    libschema *rflow = libstruct(path);
    int c = 0;
    char opt[10];
    while (c <= 5)
    {
        if (strcmp(rflow[c].user, name) == 0)
        {
            printf("\t\t\t\tYou have one pending book to return\n\n");
            printf("\t\t\t\t%s %s %s\n\n", rflow[c].title, rflow[c].author, rflow[c].status);
            printf("\t\t\t\tPlease enter yes to return this book\n");
            scanf("%s", opt);
            if (strcmp(opt, "yes") == 0)
            {
                int days = atoi(rflow[c].duedate);
                time_t seconds;
                seconds = (time(NULL) / 3600);
                if ((seconds - days) < 72)
                {
                    printf("\t\t\t\tNo fine will be applied\n\n");
                    strcpy(rflow[c].status, "Available");
                    strcpy(rflow[c].user, "null");
                    strcpy(rflow[c].duedate, "null");
                    update_file("libdb.txt", rflow);
                    free(rflow);
                    main_screen_ui(name);
                }
                else
                {
                    printf("\t\t\t\tPlease pay a fine of Rs.50\n\n");
                    free(rflow);
                    main_screen_ui(name);
                }
            }
            else
            {
                printf("\t\t\t\tInvalid input received,please reenter");
                free(rflow);
                return_flow(path, name);
            }
        }
        else
        {
            c += 1;
            continue;
        }
    }
    if (c > 5)
    {
        printf("\t\t\t\tYou have no pending book to return\n");
        printf("\t\t\t\tReturning to main screen");
        delay(3);
        clrscr();
        free(rflow);
        main_screen_ui(name);
    }
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