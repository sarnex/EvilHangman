CFLAGS = -Wall --std=c99 -g
OBJS   = mystring.o generic_vector.o dictionary.o assocarray.o hangman.o 

hangman : $(OBJS)
	$(CC) -g -o hangman $(OBJS)
clean:
	@rm -f mystring.o generic_vector.o dictionary.o assocarray.o hangman.o hangman *gch 
	@echo Clean done
