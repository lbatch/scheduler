CC = g++
CFLAGS = -g -std=c++11
TARGET = scheduler

INCLUDES = -I./coin-Rehearse/include/coin
LFLAGS = -L./coin-Rehearse/lib

LIBS = -lrehearse -lCbc -lCbcSolver -lCgl -lClp -lClpSolver -lCoinUtils -lOsi -lOsiCbc -lOsiClp -lOsiCommonTests

SRCS = Employee.cpp Schedule.cpp Scheduler.cpp Slot.cpp testMain.cpp
MAIN = testMain

.PHONY: depend clean

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

clean:
	$(RM) *.0 *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

