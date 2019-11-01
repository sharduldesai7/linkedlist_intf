CC = g++
CFLAGS = -g -Wall
SRCS = list_intf.cpp
PROG = list_intf

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS)

clean:
	rm -rf *o list_intf
