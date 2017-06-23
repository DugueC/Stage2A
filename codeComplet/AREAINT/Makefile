CC=g++ -Wno-deprecated
CFLAGS=-O
OBJ= random.o vector.o prior.o pi.o pattern.o sampler.o\
     sbd.o strauss.o matcl.o mh.o amp.o areaint.o disk.o mesevent.o

%.o: %.c
	$(CC) $(CFLAGS) -c $*.c

all : sim_areaint

sim_areaint : sim_areaint.c $(OBJ)
	$(CC) $(CFLAGS) -o ../EXEC/sim_areaint.exe sim_areaint.c $(OBJ)

