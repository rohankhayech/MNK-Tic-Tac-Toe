EXEC = tictactoe
CC = gcc
CFLAGS = -Wall -ansi -pedantic -Werror -std=c89 -g
OBJ = ui.o fileio.o game.o LinkedList.o log.o
PFLAGS =  

ifdef SECRET 
PFLAGS += -DSECRET=1
secret : clean $(EXEC)
endif

ifdef EDITOR 
PFLAGS += -DEDITOR=1
editor : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)
	

LinkedList.o : LinkedList.c LinkedList.h
	$(CC) -c LinkedList.c $(CFLAGS)

ui.o : ui.c ui.h game.h fileio.h log.h settings.h
	$(CC) -c ui.c $(CFLAGS) $(PFLAGS)
	
log.o : log.c log.h settings.h LinkedList.h 
	$(CC) -c log.c $(CFLAGS)
	
game.o : game.c game.h settings.h log.h LinkedList.h 
	$(CC) -c game.c $(CFLAGS)
	
fileio.o : fileio.c fileio.h settings.h log.h LinkedList.h 
	$(CC) -c fileio.c $(CFLAGS)
	
clean :
	rm -f $(OBJ) $(EXEC)