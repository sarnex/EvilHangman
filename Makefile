CFLAGS = -Wall --std=c99 -g
OBJS   = mystring.o generic_vector.o dictionary.o assocarray.o hangman.o 

hangman : $(OBJS)
	$(CC) -g -o hangman $(OBJS)

dictionaryTest : dictionary.o dictionaryTest.o generic_vector.o mystring.o
	$(CC) -g -o dictionaryTest mystring.o  dictionaryTest.o dictionary.o generic_vector.o 

assocarrayTest : assocarray.o assocarrayTest.o generic_vector.o mystring.o
	$(CC) -g -o  assocarrayTest mystring.o assocarrayTest.o assocarray.o generic_vector.o
clean:
	@rm -f mystring.o generic_vector.o dictionary.o assocarray.o hangman.o assocarrayTest assocarrayTest.o dictionaryTest.o dictionaryTest hangman *gch 
	@echo Clean done

