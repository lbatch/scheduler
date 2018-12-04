CC = g++
CFLAGS = -g -std=c++11

INCLUDES = -I./coin-Rehearse/include/coin/
LFLAGS = -L./coin-Rehearse/lib/

LIBS = -lrehearse -lCbc -lCbcSolver -lCgl -lClp -lClpSolver -lCoinUtils -lOsi -lOsiCbc -lOsiClp -lOsiCommonTests

SRCS = Employee.cpp Schedule.cpp Scheduler.cpp Slot.cpp main.cpp
MAIN = employeeScheduler

.PHONY: clean

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

clean:
	$(RM) *.o *~ $(MAIN)
