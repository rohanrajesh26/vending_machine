#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<strings.h>
#include <ctype.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"

#define BOLD_YELLOW "\e[1;32m"
#define BOLD_GREEN "\e[1;32m"
#define BOLD_RED "\e[1;31m"

#define UNDER_LINE_RED "\e[4;31m"
#define UNDERLINE_CYAN "\e[4;36m"
#define UNDERLINE_GREEN "\e[4;32m"
#define UNDERLINE_YELLOW "\e[4;33m"

#define BOLD_HIGH_INTENSITY_RED "\e[1;91m"
#define BOLD_HIGH_INTENSITY_GREEN "\e[1;92m"
#define RESET   "\x1b[0m"

struct item    //an 'item' structure which contains the price, quantity & item_name of each item in the vending machine
{
        int price;
        int qty;
        char item_name[20];
};

struct category    //an 'category' structure which contains the number of items in that category, an array cat to store all items in that category & category_name of each item in the vending machine
{
        int no_of_item;
        char cat_name[20];
        struct item cat[20];    //number of items in a category
};


struct bill_item    //an 'item' structure which contains the price, quantity & item_name of each item in the vending machine
{
        int price;
        int qty;
        char item_name[20];
        int item_total_cost;
};

extern int cost;    //Global variable cost
extern int counter;
char choice[5];
int no_of_categories;
struct category categ[200];
struct bill_item bill_item_array[100];


int len(int);
int del();
int edit();
void cart();
void seller_input();    
void f(int i);    
void buyer_input(); 
void update();    
void pay();

//Kushal's declarations
typedef unsigned long long llu;
//A

typedef struct acc {
	long long password;
	long long key;
	char *uname;
} acc;


typedef union dtype_t {
	acc ac;	
	long double Lf;
	double lf;
	long long lli;
	unsigned long long llu;
	float f;
	long li;
	unsigned long lu;
	void *p;
	unsigned int u;
	int i;
	short sh;
	char c;
} dtype;

int fscan_profile (FILE *fp, long index, acc *pac);
acc *init ();
int browse (FILE *fp, char *uname,  char *pass);
int sign_up (FILE *fp, char *uname, char *pass);
int update_key (char *fname, char *uname, llu new_key);
