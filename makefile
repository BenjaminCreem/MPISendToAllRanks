FCC = mpicc
LDC = mpicc
LD_FLAGS= -fopenmp
FLAGS= -Wall -fopenmp
PROG = passValues
RM = /bin/rm
OBJS = testmpi.o

#all rule
all: $(PROG)

$(PROG): $(OBJS)
	$(LDC) $(LD_FLAGS) $(OBJS) -o $(PROG)

%.o: %.c
	$(FCC) $(FLAGS) -c $<

#clean rule
clean:
	$(RM) -rf *.o $(PROG) *.mod
