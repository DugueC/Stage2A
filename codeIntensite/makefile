CC= g++
CFLAGS= -Wall 
DIR= src/
OBJ= main.o position.o rectangle.o initialisation.o calculs.o
NAME= intensite

%.o: $(DIR)%.cpp
	$(CC) $(CFLAGS) -c $(DIR)$*.cpp -g

main : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -g
	rm *.o

clear :
	rm *.o

