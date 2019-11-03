CC = g++
CFLAGS = -g -Wall
SRCS = heap_intf.cpp list_intf.cpp
PROG = heap_intf

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS)

clean:
	rm -rf *o list_intf
