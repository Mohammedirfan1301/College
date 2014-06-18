CFLAGS = -Wall --std=c99 -g
HANGMAN_OBJECTS 	= mystring.o dictionary.o generic_vector.o assocarray.o hangman.o
DICTIONARY_OBJECTS 	= mystring.o dictionary.o generic_vector.o dictionaryTest.o
ASSOCARRAY_OBJECTS 	= mystring.o dictionary.o generic_vector.o assocarray.o assocarrayTest.o

# Used for making ALL three at once
all: hangman dictionaryTest assocarrayTest

hangman : $(HANGMAN_OBJECTS)
	$(CC) -g -o hangman $(HANGMAN_OBJECTS)

dictionaryTest : $(DICTIONARY_OBJECTS)
	$(CC) -g -o dictionaryTest $(DICTIONARY_OBJECTS)

assocarrayTest : $(ASSOCARRAY_OBJECTS)
	$(CC) -g -o assocarrayTest $(ASSOCARRAY_OBJECTS)

# Clean up all the object files
clean:
	rm -rf *o
