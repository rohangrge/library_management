#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
void signup_ui();

void login_ui();
void main_splash_screen();

void clrscr();

void delay(int number_of_seconds);
int c_newuser(char *, char *, char *, char *);
void main_screen_ui(char *name);
int login_check(char *name, char *passwd);
void update_file(char *path, libschema *books);

typedef struct userd
{
    char name[40];
    char mno[40];
    char email[40];
    char passwd[40];
} uschema;

typedef struct libstatus
{
    char title[40];
    char author[40];
    char status[40];
    char user[40];
    char duedate[20];
} libschema;

uschema *userstruct(char *fp);