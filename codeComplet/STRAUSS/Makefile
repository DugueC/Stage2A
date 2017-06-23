CC=g++ -Wno-deprecated
CFLAGS=-O
OBJ= random.o vector.o prior.o pi.o pattern.o sampler.o\
     sbd.o strauss.o matcl.o mh.o amp.o areaint.o disk.o mesevent.o

%.o: %.c
	$(CC) $(CFLAGS) -c $*.c

sim_mcestim : sim_cftp.c $(OBJ)
	$(CC) $(CFLAGS) -o ../EXEC/sim_cftp.exe sim_cftp.c $(OBJ)
