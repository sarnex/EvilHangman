#include <stdio.h>
#include "generic_vector.h"
#include "mystring.h"
#include "assocarray.h"
#include "dictionary.h"
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
int getGuesses(void);
int getLetters(void);
char getLetter(void);
int getSee(void);
int getPlay(void);
void playGame(void);
GENERIC_VECTOR generateDashes(MYSTRING s, char d, GENERIC_VECTOR dictionary,MYSTRING* largestkey);
int main(int argc, char* argv[])
{
	playGame();	
	return 0;
}
void playGame(void)
{
	int i = 0;
	char c = '\0';
	int letters = 0;
	int contains = 0;
	GENERIC_VECTOR vector = generateVector();
	int playagain = 1;
	int guesses = 0;
	int see = 0;
	srand(time(0));
	do{
		MYSTRING already = mystring_init_c_string(" ");

		GENERIC_VECTOR v2 = NULL;
		GENERIC_VECTOR t = NULL, temp = NULL;
		GENERIC_VECTOR* temp2;
		MYSTRING s = NULL, t2 = NULL;
		MYSTRING* word = NULL;
		MYSTRING largestkey = NULL;
		int gotit = 0;
		int everinword = 0;
		int firstrun = 1;
		see = getSee();
		s = mystring_init_default();
		guesses = getGuesses();
		letters = getLetters();
		temp2 = (GENERIC_VECTOR*) generic_vector_at(vector,letters-1);
		if(temp2 != NULL)
		{
			vector_assignment((void**)&v2,(void*)*temp2);
		}

		if(s == NULL || vector == NULL || already == NULL )
		{
			printf("Out of memory\n");
			mystring_destroy(&already);
			generic_vector_destroy(&vector);
			mystring_destroy(&s);
			exit(1);
		}
		while(temp2 == NULL || v2 == NULL || generic_vector_size(v2) < 1 )
		{
			generic_vector_destroy(&v2);
			printf("There are no words of this length. ");
			letters = getLetters();
			temp2 = (GENERIC_VECTOR*) generic_vector_at(vector,letters-1);
			if(temp2 != NULL)
			{
				vector_assignment((void**)&v2,(void*)*temp2);
			}
		}
		for(i = 0; i < letters ; i++)
		{
			mystring_push(s,'-');
		}
		while(guesses > 0)
		{
			printf("Guess a letter: ");
			c = getLetter();
			while(mystring_contains_at_all(already,c))
			{
				printf("Already guessed, please guess again: ");
				c = getLetter();
			}
			mystring_push(already,c);
			printf("You have guessed: ");
			mystring_sort(already);
			mystring_output(already,stdout);
			if(firstrun)
			{
				t2 = largestkey;
				t = generateDashes(s,c,v2,&largestkey);
				mystring_destroy(&t2);
			}
			else
			{
				temp = t;
				t2 = largestkey;
				t = generateDashes(s,c,t,&largestkey);
				generic_vector_destroy(&temp);
				mystring_destroy(&t2);
			}
			if(see)
			{
				printf("Words remaining: %d\n",generic_vector_size(t));
			}
			for(i = 0; i < letters; i++)
			{
				contains = 0;
				if(largestkey == NULL)
				{
					break;
				}
				contains = mystring_contains(largestkey,c,i);
				if(contains) 
				{
					everinword = 1;
					mystring_put(s,i,c);
				}
			}
			if(!everinword)
			{
				printf("Sorry, %c was not in the word\n\n",c);
				guesses--;
			}
			everinword = 0;
			mystring_output(s,stdout);
			printf("\n");
			if(!mystring_contains_at_all(s,'-' ))
			{
				gotit = 1;
				printf("You win!\n");
				break;	
			}
			printf("%d guesses remaining\n",guesses);
			printf("\n\n");
			firstrun = 0;
		}
		if(!gotit)
		{
			printf("You lose!\n");
			printf("The word was ");
			if(t != NULL)
			{
				word = (MYSTRING*) generic_vector_at(t,rand() % generic_vector_size(t));
			}
			if(word != NULL)
			{
				mystring_output(*word,stdout);
			}
		}
		playagain = getPlay();
		mystring_destroy(&s);
		mystring_destroy(&already);
		mystring_destroy(word);
		mystring_destroy(&t2);
		generic_vector_destroy(&v2);
		generic_vector_destroy(&t);
		generic_vector_destroy(&temp);

		mystring_destroy(&largestkey);
	}
	while(playagain != 0);
	generic_vector_destroy(&vector);
	return;
}
int getSee(void)
{
	char see;
	printf("Do you want to see the words remaining? Enter yes or no: ");
	fscanf(stdin,"%c",&see);
	while(tolower(see) != 'y' && tolower(see) != 'n')
	{
		while ( getchar() != '\n' );	
		printf("Please enter yes or no: ");
		fscanf(stdin,"%c",&see);
	}
	while ( getchar() != '\n' );	
	if(tolower(see) == 'y')
	{
		return 1;
	}
	return 0;
}
int getPlay(void)
{
	char play;
	printf("Do you want to play again?  Enter yes or no: ");
	fscanf(stdin,"%c", &play);
	while(tolower(play) != 'y' && tolower(play) != 'n')
	{
		while ( getchar() != '\n' );	
		printf("Please enter yes or no: ");
		fscanf(stdin,"%c",&play);
	}
	while ( getchar() != '\n' );	
	if(tolower(play) == 'y')
	{
		return 1;
	}
	return 0;
}
int getGuesses(void)
{
	int guesses = -1;
	printf("How many guesses? : ");
	fscanf(stdin,"%d",&guesses);
	while(guesses <= 0)
	{
		while ( getchar() != '\n' );	
		printf("Please enter a valid number of guesses: ");
		fscanf(stdin,"%d",&guesses);
	}
	while ( getchar() != '\n' );	
	return guesses;
}
int getLetters(void)
{
	int letters = -1;
	printf("How many letters should the word have? : ");
	fscanf(stdin,"%d",&letters);
	while(letters < 1 || letters > 29)
	{
		while ( getchar() != '\n' );
		printf("Please enter a valid number of letters: ");
		fscanf(stdin,"%d",&letters);
	}
	while ( getchar() != '\n' );	
	return letters;
}
char getLetter(void)
{
	char c = '\0';
	fscanf(stdin," %c",&c);
	while(!isalpha(c) )
	{
		while ( getchar() != '\n' );
		printf("Please enter a valid letter: ");
		fscanf(stdin," %c",&c);
	}	
	while ( getchar() != '\n' );	
	return tolower(c);
}
GENERIC_VECTOR generateDashes(MYSTRING s, char d, GENERIC_VECTOR dictionary, MYSTRING* largestkey)
{
	int i, j;
	char c;
	MY_SET set = my_set_init_default();
	GENERIC_VECTOR h = NULL;
	MYSTRING* temp = NULL;
	MYSTRING new = NULL;
	if(set == NULL)
	{
		return NULL;
	}
	for(i = 0; i < generic_vector_size(dictionary); i++)
	{
		temp = (MYSTRING*) generic_vector_at(dictionary,i);
		new = mystring_init_default();	
		if(new == NULL)
		{
			my_set_destroy(&set);
			mystring_destroy(&new);
			return NULL;
		}
		if(temp != NULL)
		{
			for(j = 0; j < mystring_size(s); j++)
			{
				mystring_push(new,'-');
			}
			for(j = 0; j < mystring_size(*temp); j++)
			{
				c = tolower(mystring_get(*temp,j));
				d = tolower(d);
				if(c == d)
				{
					mystring_put(new,j,c);
				}
			}
			my_set_add(set,new,*temp);
		}
		mystring_destroy(&new);

	}
	my_set_largest_vector(set,&new);
	h = my_set_assignment_at(set,new);
	if(largestkey != NULL)
	{
		*largestkey = new;
	}
	my_set_destroy(&set);
	return h;
} 

