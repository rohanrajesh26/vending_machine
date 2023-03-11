#include "vending.h"
//#include "profile.c"

int cost = 0;
int counter = 0;

int main()
{   

    // Logging in th user
    char password[11];
    char username[15];
    int sign_check = 0;
    char cust_type[15];
    while(1){
    printf("Are you a new user(new) or existing user(old)?\n");
    scanf("%s", cust_type);
    if (strcasecmp(cust_type, "new") == 0){// For a new user
        FILE *fpkushal = fopen("accdbase", "a+");
re_sign_up:
        printf("Type your username\n");
        scanf("%s", username);
        printf("Type your password,Max length is 10 characters\n");
        scanf("%s", password);
        int already_exists = sign_up(fpkushal, username, password);// This functions adds the account to the file "accdbase"
	if (already_exists) {// If the username already exists, request a new username
		printf("Username %s is already taken! Try a new username\n", username);
		goto re_sign_up;
	}
        fclose(fpkushal);
        sign_check++;
        break;
    }
    else if (strcasecmp(cust_type, "old") == 0){// For an existing user
        FILE *fpkushal1 = fopen("accdbase", "a+");
        int no_of_transactions;
        while(1){
        printf("Type your username\n");
        scanf("%s", username);
        printf("Type your password\n");
        scanf("%s", password);
        no_of_transactions = browse(fpkushal1, username, password);// Check for the validity of the username and password
        if (no_of_transactions == -2){
            printf("Please enter correct username\n");
        }
        if (no_of_transactions == -1){
            printf("Please enter correct password\n");
        }
        if (no_of_transactions >= 0) break;
        }
        fclose(fpkushal1);
        sign_check++;
        break;
    }
    else {
      printf("Please enter either old or new\n");
    }
    }

  for (int i = 0; i < 100; i++){     //RESOURCE CONSUMING STEP, initialises all elements in the "bill" array of strings to "empty"
	strcpy(bill_item_array[i].item_name, "empty");
  }
  seller_input();
  char r[10];//holds the input for yes,no,view
  while(1){			//Loop for taking input of items.
	printf(BOLD_YELLOW "Do you want to add to cart(yes or no)? Do you want to view cart(view)? \n" RESET);
  	scanf("%s",r);	//Reply for continuing shopping

	if (strcasecmp(r, "yes") == 0)	buyer_input();    //Fixing issue of category being shown after invalid
	else if(strcasecmp(r,"no")==0){//if no shopping is done
		break;
	}
	else if(strcasecmp(r,"yes")==0){//if yes continue shopping
		continue;
	}
	else if(strcasecmp(r,"view")==0){//for viewing
		cart();
	}
	else {//invalid input
		printf(BOLD_HIGH_INTENSITY_RED "Invalid input. Kindly input 'yes' or 'no' or 'view'\n" RESET);
	}
  }
  char p[7];//for input of pay,cancel,view
  while(1){//loop for payment
  printf(UNDERLINE_CYAN "Proceed to payment(pay) or cancel(cancel) or view cart(view) \n" RESET);  //Cancel the payment or pay
  scanf("%s",p);		//Reply
  if(strcasecmp(p,"pay")==0){
  	update();//inventory is updated and pay function is called
  pay();
  FILE *fpbill3 = fopen("bill.txt", "w");
	if(counter==0) {fprintf(fpbill3, "Empty\n");}
	else{fprintf(fpbill3, "ITEM NAME");
                for(int i=0;i<11;i++) fprintf(fpbill3, " ");
                fprintf(fpbill3, "PRICE QUANTITY COST\n");

		}
  fclose(fpbill3);
  FILE *fpbill4=fopen("bill.txt","a");
  if (counter != 0){
          for(int i=0;i<counter;i++){
                  fprintf(fpbill4, "%s",bill_item_array[i].item_name);
                  for(int j=strlen(bill_item_array[i].item_name);j<20;j++) fprintf(fpbill4, " ");
                  fprintf(fpbill4, "Rs.%d",bill_item_array[i].price);
                  for(int j=len(bill_item_array[i].price);j<5;j++) fprintf(fpbill4, " ");
                  fprintf(fpbill4, "%d       Rs.%d\n",bill_item_array[i].qty,bill_item_array[i].item_total_cost);
 
          }

  fclose(fpbill4);
  break;
  }}
  else if(strcasecmp(p,"cancel")==0){//cancellation
	printf("Cancelled\n");
	FILE *f=fopen("bill.txt","w");
	fprintf(f,"empty");
	fclose(f);
	exit(0);
  }
  else if(strcasecmp(p,"view")==0){//cart() is called if user wants to view
	cart();
  }
  else printf(BOLD_RED "Invalid input. Kindly input 'pay' , 'cancel' or 'view'\n" RESET);//invalid input
  }
  FILE *fpkushal2 = fopen("accdbase", "a+");
    if (sign_check > 0){
    int no_of_transactions = browse(fpkushal2, username, password);  // Retrieve the number of times the user has transacted in past
    fclose(fpkushal2);
    if (no_of_transactions >= 0){
            update_key("accdbase", username, no_of_transactions + counter);// If the account exists, update the number of transactions
        }
    }

  return 0;  
}
