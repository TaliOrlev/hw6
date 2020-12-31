CC=gcc
CCLINK=$(CC) # Read variable CC using $(CC)
CFLAGS=-g -Wall -std=c99
OBJS=ransom.o
EXEC=prog
RM=rm -rf *.o *.exe

$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC).exe

ransom.o: ransom.c
	$(CC) $(CFLAGS) -c ransom.c

clean:
	$(RM)
