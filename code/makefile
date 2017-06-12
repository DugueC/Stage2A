CC= g++
CFLAGS= -Wall
DIR= src/
OBJ= main.o points.o rectangle.o initialisation.o calculs.o
NAME= calcul

%.o: $(DIR)%.cpp
	$(CC) $(CFLAGS) -c $(DIR)$*.cpp -g

main : $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -g
	rm *.o
