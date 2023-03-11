/*
 *				----	  profile.c	----
 *			
 *			------------	   V 4.3.0	------------
 *			       ::: Author: Kushal Jenamani ::: 
 *
 *				Revision: 19:55 07/03/2023
 *
 *	NOTE: 	"accdbase" is just an acronym for Accounts Database File. The file can have any name.
 *		The program works closely with file "accdbase" (Accounts database). 
 *		This file must be opened for both appending and writing.
 *
 *	
 *	The program implements functions that allow CREATING, RETRIEVING, UPDATING & DELETING accounts
 *	from "accdbase". The program offers the following funcitons:
 *
 * 	unsigned long long shah_pass (char *password);
 *	Return uniquely encoded value for a password string
 *
 *	int fscan_profile(FILE * __accdbase_file_pointer, long index, acc * _new_acc_ptr);
 *	Description: assigns to account structure in paramter the account stored at index "index" in accdbase.
 *	Returns 0 on success, 1 if it index out of bounds. 
 *	
 *	int browse (FILE * __accdbase_file_pointer, char *username, char *password);
 *	Description: Scans the entire Account Database file for the Account
 *	Return Number of Transactions if username and password are correct
 *	Returns -2 if wrong username
 *	Return -1 if valid username but wrong password
 *
 *	int sign_up (FILE * __accdbase_file_pointer, char *username, char *password);
 *	Description: Creates a new account with the passed on username and password
 *	Returns 0 if successful
 *	Return 1 if Username already exists
 *
 *	int update_key (char * __accdbase_file_name, char *username, unsigned long long key);
 *	Description: Updates the number of transactions for the user "username" to "key"
 *	REMARK: The function accepts file name as argument, not file pointer.
 *		The function will safely open and close the file internally.
 *
 *	int delete_acc (char *__accdbase_file_name, char *username);
 *	Description: Deleted the account corresponding to the username
 *	Returns 0 if successful
 *	Returns 1 if username not found
 *	REMARK: The function accepts file name as argument, NOT file pointer
 *		The function will safely open and close the file internally.
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned long long llu;
// The
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

// This function is responsible to return encoded version of the password
#define elif else if
llu shah_pass (char *pass) {
	llu shah_val = 0L;

	llu adder = 0;
	while (*pass) {
		shah_val *= 67;

		if (*pass <= 'Z' && *pass >= 'A') {	
			adder = *pass - 'A' + 27;
		}
		elif (*pass <= 'z' && *pass >= 'a') {
			adder = *pass - 'a' + 1;
		}
		elif (*pass <= '9' && *pass >= '0') {
			adder = *pass - '0' + 53;
		}
		elif (*pass == ' ') {
			adder = 63;
		}
		elif (*pass == '*') {
			adder = 64;
		}
		elif (*pass == '-') {
			adder = 65;
		}
		elif (*pass == '_') {
			adder = 66;
		}
		elif (*pass == '@') {
			adder = 67;
		}
		shah_val += adder;
		pass++;
	}
	return shah_val;
}
#undef elif


//Customised fscanf that retrives any account
int fscan_profile (FILE *fp, long index, acc *pac) {
	dtype *tmp = malloc(sizeof(dtype));
	fseek(fp, 0, SEEK_SET);
	for (int i = 1; i < index; i++) {

		tmp -> p = malloc(10);
		fscanf(fp, "%s", (char *)(tmp -> p));
		free(tmp -> p);
		fscanf(fp, "%llu %llu", &tmp -> llu, &tmp -> llu);

		if (feof(fp)) {
			return 1;	
		}
	}
	fscanf(fp, "%s %llu %llu", pac -> uname, &pac -> password, &pac -> key);
	free(tmp);
	return 0;

}

// Returns a pointer to an acc structure after proper mallocs
acc *init () {
	acc *newAccount = malloc(sizeof(acc));
	newAccount -> uname = malloc(sizeof(*newAccount -> uname));
	return newAccount;
}

// Browses through the account database file and checks validity of username and password
// If valid, returns number of transactions for the user
int browse (FILE *fp, char *uname,  char *pass) {
	int i = 1;
	int flag;
	acc *Acc = init();

	llu password = shah_pass(pass);

	while (1) {
		flag = fscan_profile(fp, i, Acc);
		if (flag) break;
		if (strcmp(Acc -> uname, uname) == 0) {
			break;
		}
		i++;
	}
	if (flag) {
		return -2;
	}
	if (Acc -> password == password) {
		return Acc -> key;
	}
	else return -1;
}

// Adds a new accout to the account database file
int sign_up (FILE *fp, char *uname, char *pass) {
	int already_exists = browse (fp, uname, "decoy");
	if (already_exists != -2) return 1;
	llu password = shah_pass(pass);

	fprintf(fp, "%-11.11s %-20llu %-20llu\n", uname, password, 0LLU);
	return 0;
}

// Used to update the number of transactions for a user
int update_key (char *fname, char *uname, llu new_key) {

	FILE *fp = fopen (fname, "r+b");
	browse(fp, uname, "trojan");
	fseek(fp, -20, SEEK_CUR);
	char edit[21];
	sprintf(edit, "%20llu", new_key);
	fputs(edit, fp);
	fclose(fp);
}

// Used to delete an existing account
// Return 0 if success, 1 if account not found
int delete_acc (char *fname, char *uname) {
	FILE *tmp = fopen("tmp", "w+");
	FILE *fp = fopen(fname, "r");
	acc *Acc = init();
	int i = 1;
	int flag;
	while (1) {
		flag = fscan_profile(fp, i, Acc);
		if (flag) return 1;
		if (strcmp(Acc -> uname, uname) == 0) {
			break;
		}
		i++;
	}
	fseek(fp, 0, SEEK_SET);
	char line[55];
	for (int j = 1; ; j++) {
		if (j == i) {
			fgets(line, 55, fp); 
			continue;
		}
		fgets (line, 55, fp);
		if (!feof(fp)) {
			fputs (line, tmp);
		}
		else break;
	}
	
	fclose(fp);
	fp = fopen(fname, "w");

	rewind(tmp);
	
	while (1) {
		fgets(line, 55, tmp);
		if (!feof(tmp)) {
			fputs(line, fp);
		}
		else break;
	} 

	fclose(fp);
	fclose(tmp);

	return 0;

}


