
vend: main.o buy.o sell.o profile.o 
	gcc main.o buy.o sell.o profile.o -o vend

main.o: main.c vending.h
	gcc -c main.c 

buy.o: buy.c vending.h
	gcc -c buy.c 

sell.o: sell.c vending.h
	gcc -c sell.c 

profile.o: profile.c vending.h
	gcc -c profile.c

g: main.c buy.c sell.c profile.c
	gcc main.c buy.c sell.c profile.c -g -o vend
