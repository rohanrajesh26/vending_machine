This program uses the following libraries:
1.ctype
2.stdlib
3.stdio
4.string
5.strings

This program uses the following functions:
1.len(n):-Sreyas Janamanchi
	Used to calculate the number of digits in n.
	Helps in aligning output

2.seller_input():-Pradyumna G,Rohan Rajesh
	Reads from seller.txt to form an array of struct category. This array holds all the information
	about the items available in the vending machine.

3.buyer_input():-Pradyumna G,Rohan Rajesh
	Reads input from terminal, matches input with the different category names.
	
4.f(i):-Pradyumna G,Rohan Rajesh, Shashank Devarmani, Abhinav Deshpande
	Called in buyer_input(), to loop inside the category inputted. This is used to find the item.
	
5.update():-Rohan Rajesh
	This function updates seller.txt, once buyer makes his/her purchase. To keep track of the items
	left in the vending machine.
	
6.pay():-Sreyas Janamanchi, Abhinav Deshpande
	This function is called when the buyer chooses to pay. It takes care of cases when the buyer 
	pays lesser or more than required.
	
7.cart():-Sreyas Janamanchi, Shashank Devarmani
	Keeps track of the items, the buyer has added to cart.
	This function provides the buyer with features following features:
		Delete an item from the cart.
		Edit quantity of any specific item.
		
8.del():-Sreyas Janamanchi
	This function is called inside cart.
	Provides the feature of deleting an item from the cart.

9.edit():-Sreyas Janamanchi
	This function is called inside cart.
	Provides the feature of editing the number of a specific item in cart.

10.profile.c:- Kushal
	Maintains user profiles
	It is basically a library that defines functions for following actions-
	fscanf_profile( FILE *, long, struct acc *): Construct a struct acc from the ith account in the database
	browse (FILE *, char *, char *): Find and return number of transaction for a specific account
	sign_up (FILE *, char *, char *): Create a new account in the database
	update_key (char *, char *, unsigned long long): Update the number of transactions for an account
	delete_acc (char *, char *): Delete an account
	--Internal Implementations-- 
	shah_pass (char *): Uniquely encodes the string that is passed in. Used to encrypt passwords.
	init (): Returns a pointer to newly allocated struct acc
	
	
11.main():-Shashank Devarmani
	Fills the categ array from seller.txt using seller_input().
	Keeps looping in buyer_input(),cart(), until buyer chooses to exit this loop.
	Provides the buyer with the option to cancel purchase,review cart(using cart() function) or make
	payment(using pay function)
	
For further information refer to the comments in the code.

Extra credits:-
Colour Graphics: Abhinav Deshpande
Makefile: Kushal 
Debugging: Shashank Devarmani, Abhinav Deshpande, Pradyumna G
Bill.txt: Shashank Devarmani
