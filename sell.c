#include "vending.h"
//function returns the no of digits in n
int len(int n){
	int a=1,c=1;
	while(n){
		n=n/10;
		c++;
	}
	return c;
}
//reads the quantity available in vending machine from seller.txt and stores it in an array(categ)
void seller_input()
{
	FILE *fp;
	fp=fopen("seller.txt","r");    //seller.txt is seller's input file which will get updated everytime
	fscanf(fp,"%d",&no_of_categories);    //input number of categories
	for(int i=0;i<no_of_categories;i++)
	{
		fscanf(fp,"%s %d",categ[i].cat_name,&(categ[i].no_of_item));    //input category name and number of items in it
		for(int j=0;j<categ[i].no_of_item;j++)
		{
			fscanf(fp,"%s %d %d",categ[i].cat[j].item_name,&(categ[i].cat[j].price),&(categ[i].cat[j].qty));	//in that category we are taking its items names,price and quantity respectively
		}
	}
	fclose(fp);

}
void update()
{

         FILE *fp;
	fp=fopen("seller.txt","w");    //seller.txt is seller's input file which will get updated everytime
	fprintf(fp,"%d\n",no_of_categories);    //output number of categories
	for(int i=0;i<=no_of_categories;i++)
	{
		fprintf(fp,"%s %d\n",categ[i].cat_name,categ[i].no_of_item);    //output category name and number of items in it
		for(int j=0;j<categ[i].no_of_item;j++)
		{
			fprintf(fp,"%s %d %d\n",categ[i].cat[j].item_name,categ[i].cat[j].price,categ[i].cat[j].qty);//in that category we are printing its items names,price and quantity
		}
	}
	fclose(fp);
 
}

void pay(){
    if(cost==0) {printf(UNDERLINE_GREEN "Thank you for visiting\n" RESET);  //when buyer hasn't purchased any item(output in stdout)   
	    FILE *F=fopen("bill.txt","w");
	    fprintf(F,"Empty");
	    fclose(F);
    exit(0);}
	else{	//NEW LINE ADDED
	int n;		
	printf(UNDERLINE_GREEN "Pay Rs.%d\n" RESET,cost);
	FILE *fpbill = fopen("bill.txt", "w");
	if(counter==0) {fprintf(fpbill, "Empty\n");//when buyer hasn't purchased any item(output in bill)
	//printing bill when item has been purchased
	FILE *F=fopen("bill.txt","w");
          fprintf(F,"Empty");
          fclose(F);
	  exit(0);
	}	
	
	else{
		fprintf(fpbill, "ITEM NAME");
		for(int i=0;i<11;i++) fprintf(fpbill, " ");
		fprintf(fpbill, "PRICE QUANTITY COST\n");
	}
	fclose(fpbill);
	FILE *fpbill1 = fopen("bill.txt", "a");
	if (counter != 0){
	for(int i=0;i<counter;i++){
		fprintf(fpbill1, "%s",bill_item_array[i].item_name);
		for(int j=strlen(bill_item_array[i].item_name);j<20;j++) fprintf(fpbill1, " ");
		fprintf(fpbill1, "Rs.%d",bill_item_array[i].price);
		for(int j=len(bill_item_array[i].price);j<5;j++) fprintf(fpbill1, " ");
		fprintf(fpbill1, "%d       Rs.%d\n",bill_item_array[i].qty,bill_item_array[i].item_total_cost); 
	
	/*for (int i = 0; i < counter; i++){
		fprintf(fpbill1, "%s %d %d %d\n", bill_item_array[i].item_name, bill_item_array[i].price, bill_item_array[i].qty, bill_item_array[i].item_total_cost);
	}*/
	}
	fclose(fpbill1);
	

	while(1){
	scanf("%d",&n);//reading amount paid by buyer
    if(isdigit(n)!=0) printf(RED "Please re-enter the amount.\n" RESET);	//when input isn't an integer

    else{	
	 if (n<cost){//when buyer paid less than total cost
		printf(RED "Amount insufficient by Rs.%d\n" RESET,cost-n);		//Entering the amount until sufficient(or more) is entered
		printf(BOLD_GREEN "Please re-enter the amount\n" RESET);
		continue;//Entering the amount until sufficient(or more) is entered
		}
	else if(n>cost){//when buyer paid more than total cost
		printf(BOLD_HIGH_INTENSITY_GREEN "You have paid an excess amount. Returning Rs.%d\n" RESET,n-cost);
		break;
	}
	else{//when buyer paid exact amount
		printf(UNDERLINE_GREEN "Payment successful. Thank you for shopping\n" RESET);		//Finish
		break;
		}
        }   
        }	
	}	
}
}
//function that removes item from cart
int del(){
int c=0,r=0;
while(1){
	printf(YELLOW "Kindly enter the name of the item you want to remove.\n" RESET);
	char del_item[20];
	scanf("%s",del_item);//reading the item to be deleted
	int flg=0;
	for(int i=0;i<counter;i++){//matching input with items in cart
		if(strcasecmp(bill_item_array[i].item_name,del_item)==0){
			c++;//updating flag variable
			counter--;//updating no of items in cart
			cost=cost-bill_item_array[i].item_total_cost;
			for(int j=0;j<no_of_categories;j++){
				for(int k=0;k<categ[j].no_of_item;k++){
					if(strcasecmp(categ[j].cat[k].item_name,del_item)==0){
						categ[j].cat[k].qty=categ[j].cat[k].qty+bill_item_array[i].qty; //updating quantity in vending machine
						flg++;
						r++;
						printf(GREEN "%s has been removed from cart.\n" RESET,bill_item_array[i].item_name);
						for(int l=i;l<counter;l++) bill_item_array[l]=bill_item_array[l+1];;//removing item from cart
						return c;
					}
				}
				if(flg!=0) break;
			}
		}
		if(c!=0) break;
	}
	//when input doesn't match with any bill item
	if(c==0){
		printf(UNDER_LINE_RED "This item doesn't exist. Do you want to remove any item(yes or no).\n" RESET);
		char reply[4];
		while(1){
		scanf("%s",reply);
		if(strcasecmp(reply,"yes")==0) break;
		else if(strcasecmp(reply,"no")==0){
			r++;
			break;
		} 
		else printf(BOLD_HIGH_INTENSITY_RED "Incorrect input. Please input yes(to remove an item) or no(to exit the view option)\n" RESET);
	}
}
	if(r!=0) break;
}
return c;//c==1 if an item is deleted,else c==0
}
//function edits the number of a specific item in cart
int edit(){
	int c=0,r=0;
	while(1){
		printf(CYAN "Kindly enter the item you want to edit the quantity of.\n" RESET);
		char e_item[20];
		scanf("%s",e_item);
		for(int i=0;i<counter;i++){
			if(strcasecmp(e_item,bill_item_array[i].item_name)==0){//matching input item with input from user
				printf(BOLD_GREEN "Kindly enter the quantity you want to change %s to\n" RESET,bill_item_array[i].item_name);
				int quantity;
				scanf("%d",&quantity);//reading updated qty
				while(quantity<=0)//handling the case when input isn't positive
				{
					printf(UNDER_LINE_RED"Please enter a positive quantity\n"RESET);
					scanf("%d",&quantity);
				}
				for(int j=0;j<no_of_categories;j++){
					for(int k=0;k<categ[j].no_of_item;k++){
						if(strcasecmp(categ[j].cat[k].item_name,e_item)==0){//matching input with items in vending machine
							if(quantity>categ[j].cat[k].qty+bill_item_array[i].qty){//if insufficient amount in vending machine
								printf(RED "Sorry we have only %d %s\n" RESET,categ[j].cat[k].qty+bill_item_array[i].qty,categ[j].cat[k].item_name);
							}
							else{
								r++;
								c++;
								categ[j].cat[k].qty=categ[j].cat[k].qty+bill_item_array[i].qty-quantity;//updating qty in vending machine
								cost=cost-(categ[j].cat[k].price)*((bill_item_array[i].qty)-quantity);//updtating total cost
								bill_item_array[i].qty=quantity;//updating qty in cart
								bill_item_array[i].item_total_cost=categ[j].cat[k].price*quantity;
								printf(BOLD_GREEN "%s has been edited to %d items.\n" RESET,bill_item_array[i].item_name,bill_item_array[i].qty);
								break;
							}
						}
					}
					if(c!=0) break;
				}
			}
			if(c!=0) break;
		}//when no such item in cart
		if(c==0){
			printf(BOLD_RED "Invalid input. Do you want to make changes to quantity(yes or no)\n" RESET);
			char rep[4];
			while(1){
			scanf("%s",rep);
			if(strcasecmp(rep,"yes")==0) break;
			else if(strcasecmp(rep,"no")==0){
				r++;
				break;
			}
			else printf(BOLD_HIGH_INTENSITY_RED "Invalid input. Kindly reply in 'yes' or 'no'.\n" RESET);
			}
			if(r!=0) break;
		}
		if(r!=0) break;
	}
	return c;//c==1 if any item edited,else c==0
}

void cart(){
	//printing the cart
    if(counter==0) printf(CYAN "Empty cart\n" RESET);	
	else{	
	printf(CYAN "ITEM NAME" RESET);
	for(int i=0;i<11;i++) printf(" ");
	printf(CYAN "PRICE QUANTITY COST\n" RESET);
	for(int i=0;i<counter;i++){
		printf("%s",bill_item_array[i].item_name);
		for(int j=strlen(bill_item_array[i].item_name);j<20;j++) printf(" ");
		printf("Rs.%d",bill_item_array[i].price);
		for(int j=len(bill_item_array[i].price);j<5;j++) printf(" ");
		printf("%d       Rs.%d\n",bill_item_array[i].qty,bill_item_array[i].item_total_cost); 
	}
	printf("Total:Rs.%d\n",cost );
	char choice[5];
	int count=0;
	while(1){
		printf(UNDERLINE_CYAN "Do you want to remove(del) an item or change quantity(edit) of an item or are you done viewing cart(done)\n" RESET);  
		scanf("%s",choice);    //taking input for the required process
		//function removes an item 
		if(strcasecmp(choice,"del")==0) count=del();
		else if(strcasecmp(choice,"edit")==0) count=edit();
		else if(strcasecmp(choice,"done")==0) return;
		else printf(BOLD_HIGH_INTENSITY_RED "Invalid input. Kindly try again.\n" RESET);
		if(count!=0) break;
	}
    }
}

