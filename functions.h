#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <conio.h>
typedef struct libstatus
{
    char title[40];
    char author[40];
    char status[40];
    char user[40];
    char duedate[20];
} libschema;

typedef struct userd
{
    char name[40];
    char mno[40];
    char email[40];
    char passwd[40];
} uschema;

void signup_ui();

void login_ui();
void main_splash_screen();

void clrscr();
void return_flow(char *path, char *name);
void borrow_flow(char *path, char *name);
void delay(int number_of_seconds);
int c_newuser(char *, char *, char *, char *);
void main_screen_ui(char *name);
int login_check(char *name, char *passwd);
void show_avail(char *, char *);
libschema *libstruct(char *fp);

void update_file(char *path, libschema *books);

uschema *userstruct(char *fp);