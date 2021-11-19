/*
 -------------------------------------
 File:    myword.c
 file description
 word type functions
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-02-02
 -------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include "mystring.h"
#include "myword.h"

/*
 -------------------------------------------------------
 Reads the "stop words" from the common-english-words file and
 stores them in the stop word dictionary data structure (in myword.h)
 as an array of 26 strings, each string holds the same stop words that
 start with the same alphabet character, separated by a comma.
 Use: set_stopword(char *filename, char *stopwords[])
 -------------------------------------------------------
 Parameters:
 *filename - file that is being read (val-to-pointer)
 *stopwards[] - empty array to be filled with stop words (pointer of char array)
 Returns:
 None
 -------------------------------------------------------
 */
void set_stopword(char *filename, char *stopwords[]) {
	//open the file with the filename
	FILE *fp = fopen(filename, "r");

	if (fp != NULL) {
		char line[1000];
		const char delimiters[] = ".,\n\t\r"; // sets constants that will determine the start and end of a string
		char *token; //creates a pointer to the token char
		int i;

		while (fgets(line, 1000, fp) != NULL) {
			token = (char*) strtok(line, delimiters); //breaks the string into a series of tokens

			while (token != NULL) {
				i = (int) (*token - 'a'); //converting the token to an int and subtracting the ascii value of 'a' to get location in array???
				strcat(stopwords[i], token);
				strcat(stopwords[i], ",");
				token = (char*) strtok(NULL, delimiters);
			}
		}
	} else {
		printf("The file you tried to open was not found!!!"); // debugging tool
	}

	fclose(fp); //close the file that was opened
	return;
}

/*
 -------------------------------------------------------
 This function checks if word is a word in string str
 Use: contain_word(char *str, char *word)
 -------------------------------------------------------
 Parameters:
 *str - pointer to the string haystack (pointer)
 *word - pointer to the needle (int)
 Returns:
 found - 1 if yes and 0 if no (int)
 -------------------------------------------------------
 */
int contain_word(char *str, char *word) {
	if (str == NULL || word == NULL)
		return 0;

	int found = 0;

	char temp[20] = { 0 };
	strcat(temp, ","); //use , as word seperator
	strcat(temp, word);
	strcat(temp, ",");

	if (strstr(str, temp)) //strstr tries to find the needle in the haystack
		found = 1;
	else
		found = 0;

	return found;
}

/*
 -------------------------------------------------------
 This function check if the word is contained in directory stopwords[]
 Use: is_stopword(char *stopwords[], char *word)
 -------------------------------------------------------
 Parameters:
 *stopwords[] - pointer to the stopwords array (pointer to char array)
 *word - the word to evaluate (char pointer)
 Returns:
 stopword - 1 if yes, 0 otherwise.
 -------------------------------------------------------
 */

// returns 1 if yes, 0 otherwise. It use function contain_word()
int is_stopword(char *stopwords[], char *word) {
	int s_word_found = 0;
	if (word == NULL || *word == '\0')
		s_word_found = 0;
	else
		s_word_found = contain_word(stopwords[*word - 'a'], word);

	return s_word_found;
}

/*
 -------------------------------------------------------
 Opens and reads a text file, checks if each word in that file is
 a stopword. If it isn't, stores the word in WORDSUMMARY word array
 along with its frequency.
 Use: process_word(char *filename, WORDSUMMARY *ws, char *stopwords[])
 -------------------------------------------------------
 Parameters:
 *filename - the name of the file to be opened (char pointer)
 WORDSUMMARY *ws - create a word summary object (data structure)
 *stopwords[] - array full of stopwords (pointer to char array)
 Returns:
 0 - this should be a void function but whatever
 -------------------------------------------------------
 */
int process_word(char *filename, WORDSUMMARY *ws, char *stopwords[]) {
	FILE *fp = fopen(filename, "r");

	if (fp != NULL) {
		char line[1000];
		const char delimiters[] = " .,;:!()&?-\n\t\r\"\'";
		char *token; //creates a pointer to the tokens

		while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
			ws->line_count++; //updating the structure line_count variable

			lower_case(line); //from mystring.c
			trim(line); //from mystring.c

			token = (char*) strtok(line, delimiters); // get the first word
			while (token != NULL) { // traversing all words in a line
				int found_word_temp = 0;
				ws->word_count++;

				if (is_stopword(stopwords, token) == 0) { //if the word isnt a stop word then;

					int i = 0;
					//check to see if that word was seen previously
					while (i < ws->keyword_count) {
						if (strcmp(token, ws->word_array[i].word) == 0) { //if the string is found it'll equal 0
							found_word_temp = 1;
							ws->word_array[i].frequency++;
						}
						i += 1;
					}

					//if the word was not found then put it in the word_array
					if (found_word_temp == 0) {
						int end_location = ws->keyword_count;
						strcpy(ws->word_array[end_location].word, token);
						ws->word_array[end_location].frequency = 1;
						ws->keyword_count++;
					}
				}
				//insert token into data structure words->word_array[]

				token = (char*) strtok(NULL, delimiters); //go to the next word

			}
		}

	} else {
		printf("File was not properly read!!");
		return -1; //quit the function
	}

	fclose(fp); //close the file that was opened

	return 0;
}

/*
 -------------------------------------------------------
 Saves the data of WORDSUMMARY words to file of the name
 passed by filename in a specified format.
 Use: save_to_file(char *filename, WORDSUMMARY *ws)
 -------------------------------------------------------
 Parameters:
 *filename - the name of the file being passed (pointer to char)
 WORDSUMMARY *ws - create a wordsummary object (object)
 Returns:
 0 - shouldnt return anything
 -------------------------------------------------------
 */
int save_to_file(char *filename, WORDSUMMARY *ws) {
	//pulling the 3 variables and calling the keyword array
	FILE *fp = fopen(filename, "w");

	fprintf(fp, "line count:%d\n", ws->line_count);
	fprintf(fp, "word count:%d\n", ws->word_count);
	fprintf(fp, "non-common word count:%d\n", ws->keyword_count);

	int i = 0;
	while (i < ws->keyword_count) {
		fprintf(fp, "%s:%d\n", ws->word_array[i].word, ws->word_array[i].frequency);
		i += 1;
	}

	fclose(fp);
	return 0;
}

