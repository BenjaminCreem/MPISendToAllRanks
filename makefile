FCC = mpicc
LDC = mpicc
LD_FLAGS= -fopenmp
FLAGS= -Wall -fopenmp
PROG = tokenRing
RM = /bin/rm
OBJS = ring.o 
PROG2 = pingPong
OBJS2 = pong.o

#all rule
all: $(PROG) $(PROG2)

$(PROG): $(OBJS)
	$(LDC) $(LD_FLAGS) $(OBJS) -o $(PROG)

$(PROG2): $(OBJS2)
	$(LDC) $(LD_FLAGS) $(OBJS2) -o $(PROG2)

%.o: %.c
	$(FCC) $(FLAGS) -c $<


#clean rule
clean:
	$(RM) -rf *.o $(PROG) *.mod
	$(RM) -rf *.o $(PROG2) *.mod
