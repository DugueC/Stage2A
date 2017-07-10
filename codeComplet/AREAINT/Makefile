CC=g++ 
CFLAGS=-Wno-deprecated -O #-Wall
DIR= ../FGJK/
OBJ= random.o vector.o prior.o pi.o pattern.o sampler.o\
     sbd.o strauss.o matcl.o mh.o amp.o areaint.o disk.o mesevent.o\
     FGJK.o position.o points.o quadrillage.o rectangle.o initialisation.o calculs.o

%.o: %.c
	$(CC) $(CFLAGS) -c $*.c

%.o: $(DIR)%.cpp
	$(CC) $(CFLAGS) -c $(DIR)$*.cpp

all : sim_areaint

sim_areaint : sim_areaint.c $(OBJ)
	$(CC) $(CFLAGS) -o ../EXEC/sim_areaint.exe sim_areaint.c $(OBJ)

clear :
	rm *.o
