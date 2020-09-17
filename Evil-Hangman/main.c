	#include <stdio.h>
	#include <stdlib.h>
	#include <ctype.h>
	#include "my_string.h"
	#include "generic_vector.h"
	#include "tree.h"

	#define SIZE 30
	void clear_keyboard_buffer(void);
	void play_game(GENERIC_VECTOR* arr, int wordSize,  int numTries);
	int main(int argc, char* argv[])
	{
		int i;
		GENERIC_VECTOR arr[SIZE];
		FILE* fp;
		MY_STRING hMy_string;
		int wordSize = 0;
		int numTries = 0;
		char ans;

		fp = fopen("dictionary.txt", "r");
		if(fp==NULL)
		{
			printf("Failed to open file!\n");
			exit(1);
		}

		hMy_string = my_string_init_default();
		for(i=0; i<SIZE; i++)
		{
			arr[i] = generic_vector_init_default();
		}

		//extract, take in the words from the dictionay file and save to array based on size
		while(my_string_extraction(hMy_string, fp))
		{
			if(my_string_get_size(hMy_string)>=0 && my_string_get_size(hMy_string)<30)
			{
				generic_vector_push_back(arr[my_string_get_size(hMy_string)],hMy_string);
			}
		}

		my_string_destroy(&hMy_string);
		do
		{
			//user input word size
			printf("How many letter do you want (2-29)? ");
			scanf("%d", &wordSize);
			clear_keyboard_buffer();
			while(wordSize<=1 || wordSize>=30)
			{
				printf("Please enter a valid number: ");
				scanf("%d", &wordSize);
				clear_keyboard_buffer();
			}
			printf("\nHow many tries do you want?\n");
			scanf("%d", &numTries);
			clear_keyboard_buffer();
            if(numTries <=0){
                printf("\nIt appears you do not want to play this game.\n");
                printf("Good Bye!\n");
                break;
            }

			play_game(arr,wordSize,numTries);

			printf("Do you want to continue playing? (y/n)\n");
			scanf("%c", &ans);
		}while(ans=='y');

		// destory array with all wordsw
		for(i=0; i<SIZE; i++)
		{
			generic_vector_destroy(&arr[i]);

		}
		fclose(fp);
		return 0;
	}
	void play_game(GENERIC_VECTOR* arr, int wordSize,  int numTries)
	{
		int i;
		GENERIC_VECTOR temp;
		MY_STRING key;
		MY_STRING new_key;
		TREE hRoot;
		int numOfSameKey = 0;
		int count = 0;
		int sizeOfVector = 0;
		char guess;
		MY_STRING guessed = my_string_init_default();

		//key
		key = my_string_init_default();
		new_key = my_string_init_default();
		for(i = 0; i<wordSize; i++)
		{
			my_string_push_back(key,'-');
			my_string_push_back(new_key,'-');
		}

		//copy everything to temp with same key
		temp = generic_vector_copy_key(arr[wordSize],key);
		sizeOfVector = generic_vector_get_size(temp);
		printf("initial size of vector = %d\n", sizeOfVector);
		printf("initial key = ");
		my_string_insertion(key,stdout);
		printf("\n\n");
		printf("start game\n");
		while(my_string_contains_dash(key) && count<numTries && sizeOfVector!=0)
		{
			printf("You have %d tries left!\n\n",numTries-count);
			if(count<numTries)
			{
				printf("Used letters: ");
				for(int i = 0; i<my_string_get_size(guessed); i++)
				{
					printf("%c, ", *my_string_at(guessed, i));
				}
				printf("\n");
			}
			printf("Please enter your guess: ");
			scanf("%c",&guess);
			clear_keyboard_buffer();
			while(!isalpha(guess) || my_string_contains(guessed, guess))
			{
					printf("You already guessed this letter or you entered an incorrect char!\n");
					printf("Please enter a different letter!\n");
					scanf("%c",&guess);
					clear_keyboard_buffer();
			}
			my_string_push_back(guessed,(char)tolower(guess));


			hRoot = tree_init_default();

			for(i=0; i<sizeOfVector; i++)
			{
				my_string_assignment(&new_key,key);
				get_word_key_value(key, new_key, *generic_vector_at(temp,i), guess);
				hRoot = tree_insert(hRoot, new_key, *generic_vector_at(temp,i));
			}

//			printf("Print in order: \n");
//			print_in_order(hRoot);
//			printf("\n");
			numOfSameKey = 0;

			my_string_assignment(&new_key, key);
			printf("size of temp before = %d\n", generic_vector_get_size(temp));
			swap_vector(hRoot, &numOfSameKey, &new_key, &temp);
			printf("size of temp after= %d\n", generic_vector_get_size(temp));
			sizeOfVector = generic_vector_get_size(temp);
			if(my_string_compare(new_key,key)==0)
			{
				printf("Sorry, the letter you entered is not in the word!\n");
			}else{
				printf("Congrats, the letter you entered is in the word!\n");
				my_string_assignment(&key, new_key);
				printf("The new key is:   ");
				my_string_insertion(key,stdout);
				printf("\n");
			}

			tree_destroy(&hRoot);

			count++;

			printf("After %d tries: The key is ", count);
			my_string_insertion(key, stdout);
			printf("\n\n");

			if(count>= numTries && my_string_contains_dash(key))
			{
				printf("Sorry, You failed!\n");
				printf("The word is: ");
				my_string_insertion(*generic_vector_at(temp, 0),stdout);
				printf("\n\n");
			}else if(!my_string_contains_dash(key)){
				printf("Congratualtion! You got it!\n");
			  printf("The word is: ");
				my_string_insertion(key,stdout);
				printf("\n\n\n");
			}
		}
		my_string_destroy(&guessed);
		my_string_destroy(&key);
		my_string_destroy(&new_key);
		generic_vector_destroy(&temp);
	}

	void clear_keyboard_buffer(void)
	{
		char c;
		scanf("%c", &c);
		while(c!='\n')
		{
			scanf("%c", &c);
		}
	}
