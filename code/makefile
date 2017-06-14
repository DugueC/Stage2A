CC= g++
CFLAGS= -Wall
DIR= src/
OBJ= main.o position.o points.o quadrillage.o rectangle.o initialisation.o calculs.o
NAME= calcul

%.o: $(DIR)%.cpp
	$(CC) $(CFLAGS) -c $(DIR)$*.cpp -g

main : $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -g
	rm *.o

clear :
	rm *.o
