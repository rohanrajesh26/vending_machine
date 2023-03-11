#include"vending.h"

void f(int i)    //Part of buyer_input. Function to display item name and price after category has been chosen
{
      char item_input[20];			//Item_input is temporary variable to take buyers' item input
      int x;					//x stores item's quantity
      printf(BOLD_HIGH_INTENSITY_GREEN "Choose item and give quantity\n" RESET);
	  int flag=0;		//This is the flag to mark the existance of an item.
	  					//Increment it after item is found.
	  
	  //Loop for displaying the menu of items with proper allignment.
      for(int j=0;j<categ[i].no_of_item;j++)
      {
		printf("%d. %s ",j+1,categ[i].cat[j].item_name);
		for(int k=strlen(categ[i].cat[j].item_name);k<20;k++) printf(" ");	//aligning output
		printf("Rs.%d\n",categ[i].cat[j].price);
      }
      scanf("%s %d",item_input,&x);    //Taking buyers' item input and that items quantity
	  //Checking the input quantity.
      while(x<=0)
      {
		
	    printf(UNDER_LINE_RED "Enter a positive quantity\n"RESET);
	    scanf("%d",&x);
      }

	  while(1){
      for(int j=0;j<categ[i].no_of_item;j++)
      {
        if(strcasecmp(item_input,categ[i].cat[j].item_name)==0)    //Matching items with buyer's input
	  	{
	  	flag++;		//Item successfully found.
	    	if(categ[i].cat[j].qty>=x)
	    	{
		  categ[i].cat[j].qty=categ[i].cat[j].qty-x;    //Updating the quantity of that item
	  	  cost=cost + categ[i].cat[j].price*x;
		  printf(BOLD_GREEN "%d %s have been added to cart\n" RESET,x,categ[i].cat[j].item_name);

		  //Updating the bill.
		  bill_item_array[counter].price = categ[i].cat[j].price;
		  bill_item_array[counter].qty = x;
		  bill_item_array[counter].item_total_cost = categ[i].cat[j].price*x;
		  strcpy(bill_item_array[counter].item_name, categ[i].cat[j].item_name);
	    	}
	    	else
	    	{
		  //If buyer demands more quantiy than available
		  printf(BOLD_YELLOW "Sorry, the number of %s left are %d\n" RESET,categ[i].cat[j].item_name,categ[i].cat[j].qty);
	    	}
	  	}
      }
	if (flag==0){ //Check for the exitence of the item.
		printf(UNDER_LINE_RED "This item does not exist. Please enter valid name\n" RESET);
		scanf("%s %d",item_input,&x);
	}
	else break;
	}
}
void buyer_input()
{
  printf(UNDERLINE_YELLOW "Choose category:\n" RESET);
  for(int i=0;i<no_of_categories;i++)	//Display the menu of categories.
  { 
    printf("%d. %s\n",i+1,categ[i].cat_name);
  }
  char cat_input[20];												//cat_input is temporary variable to take buyer's category input 
  scanf("%s",cat_input);
  while(1){
  int flag=0;		//Check for the existence of the catrgory. If does not exits, then use to 
					//display error message.
  for(int i=0;i<no_of_categories;i++)
  {
    if(strcasecmp(cat_input,categ[i].cat_name)==0)						//Matching category with buyer's input
    {
      f(i);															//Calling f and passing i to it
	  counter++;
	  flag++;
    }
  }
	if(flag==0){	//If category does not exists, display an error message.
		printf(UNDER_LINE_RED "This category does not exist.Please enter valid name from the above list.\n" RESET);
		scanf("%s",cat_input);
	}
	else
		break;
  }
}
