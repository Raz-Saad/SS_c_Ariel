#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD 30 //max length of word
#define LINE 256 //max length of line
#define MAXTEXTLENGTH 64000 // 256*250

//functions declarations
int getLine(char s[LINE]);
int getWord(char w[WORD]);
int substring(char *str1, char *str2);
int similar(char *s, char *t);

int main()
{
    // initializing the input text
    char *textInput = (char *)calloc(MAXTEXTLENGTH, sizeof(char));//memory allocating
    if (textInput == NULL)
    {//checking if the memory was really allocated
        return 1; // error
    }

    int i = 0;
    while (scanf("%c", textInput + i) != EOF)
    {//loading the input file
        i++;
    }

    int textlen = strlen(textInput);//the length of the text
    //for saving memory space we allocate space for the exact length of the text,
    //then we free the textInput array space
    char *p_text = (char *)calloc((textlen + 1), sizeof(char));

    if (p_text == NULL)
    {//checking if the memory was really allocated
        return 1; // error
    }

    memcpy(p_text, textInput, (textlen + 1));//copying the text from the textInput array into the new allocated space
    free(textInput);//freeing the textInput array from memory

    // getting the word
    int wordlength = getWord(p_text);//using getWord function in order to get the first word's length
    char *p_word = (char *)calloc((wordlength + 1), sizeof(char));//allocating memory space for the first word of the file to be saved separately
    if (p_word == NULL)
    {//checking if the memory was really allocated
        return 1; // error
    }

    memcpy(p_word, p_text, wordlength);//copying the first word of the input text to the allocated space
    char *p2_text = (p_text + wordlength + 4); //points to the lines in the text

    //the first line of the input is the first word then ' ' then 'a'/'b',
    //we will check which option the user chose
    if (*(p_text + wordlength + 1) == 'a') 
    {
        // option a was chosen

        int currLineLength = 0;//stores the line's length
        char *p_iterator = p2_text;//iterator for the while loop

        // iterate through all the lines
        while (*p_iterator != '\0') 
        {
            /*
            in every iteration, we will calculate the current line's length, 
            put it in a new array and send it to a substring method with the 
            input word to check if the word is a substring of the the line
            */

            currLineLength = getLine(p_iterator);//getting the length of the line
            char *currLinePointer = (char *)calloc(currLineLength, sizeof(char));//allocating memory space for storing the line
            if (currLinePointer == NULL)
            {//checking if the memory was really allocated
                return 1; // error
            }

            memcpy(currLinePointer, p_iterator, currLineLength);//copying the line's content into the memory allocated space
            if (substring(p_word, currLinePointer))
            {//checking if the input word is a substring of the line
                printf("%s\n", currLinePointer);
            }

            p_iterator = p_iterator + currLineLength + 1;// moving the pointer to the next line
            free(currLinePointer);//freeing the allocated memory for the line the we already used
        }
    }
    else if (*(p_text + wordlength + 1) == 'b')
    {
        // option b was chosen

        int currWordLength = 0;//stores the word's length
        char *p_iterator = p2_text;//iterator for the while loop
        while (*p_iterator != '\0') // iterate through all the words
        {
            /*
            in every iteration, we will calculate the current word's length, 
            put it in a new array and send it to the similar method with the 
            input word to check if the words are similar
            */

            currWordLength = getWord(p_iterator);//getting the word's length

            char *currWordPointer = (char *)calloc(currWordLength, sizeof(char));//allocating memory space for storing the word
            if (currWordPointer == NULL)
            {//checking if the memory was really allocated
                return 1; // error
            }
            memcpy(currWordPointer, p_iterator, currWordLength);//copying the word's content into the memory allocated space
            if (similar(currWordPointer, p_word))
            {//checking if the words are similar
                printf("%s\n", currWordPointer);
            }
            p_iterator = p_iterator + currWordLength; //moving the pointer past the current word

            while (((*(p_iterator) == '\n' || *(p_iterator) == '\t' || *(p_iterator) == ' '|| *(p_iterator) == '\r')) && (*p_iterator != '\0'))
            {//while the pointer isn't pointing on a letter we keep moving it forward
                p_iterator++;
            }

            /*
            after it moved we will check we did'nt reach the end of text, 
            if we did then free the allocated space for the word and exit the while loop
            */
            if (*p_iterator == '\0')
            {
                free(currWordPointer);
                break;
            }
            
            free(currWordPointer);//freeing the allocated memory for the word the we already used
            
        }
    }

    free(p_text);//freeing the allocated memory for the text
    free(p_word);//freeing the allocated memory for the input word

    return 0;
}
/*
this function checks if it's possible to get from string s to string t by removing at most 1 character from s
*/
int similar(char *s, char *t)
{
    if (strlen(s) == strlen(t))
    {
        char *p_s = s;
        for (int i = 0; i < strlen(t); i++)
        { //checks if every letter match
            if (*(p_s + i) != *(t + i))
            {
                return 0;
            }
        }
        return 1;
    }
    else if(strlen(s) == strlen(t) + 1)
    {
        char *p_s = s;
        int flag = 0; // flag for the first mistake
        for (int i = 0; i < strlen(t); i++)
        {
            if (*(p_s + i) != *(t + i))
            {
                p_s++;//if a mistake was detected we push the pointer one spot ahead and increment flag by 1
                
                if (flag>0 || *(p_s + i) != *(t + i))
                {//if a second mistake was detected then we return false
                    return 0;
                }

                flag++;
            }
        }
        return 1;
    }
    return 0;
}

//gets the length of the line relatively to the pointer s
int getLine(char s[LINE])
{
    int i = 0;
    char *p_s = s;
    while (*(p_s + i) != '\r' && *(p_s + i) != '\n' && i < LINE && *(p_s + i) != '\0')
    {//we count all the letters until we reach a new line type character 
        i++;
    }
    return i;
}

//gets the length of the word relatively to the pointer w
int getWord(char w[WORD])
{
    int i = 0;
    char *p_w = w;

    while (*(p_w + i) != '\n' && *(p_w + i) != '\t' && *(p_w + i) != ' ' && *(p_w + i) != '\0' && *(p_w + i) != '\r')
    {//we count all the letters until we reach end word type character 
        i++;
    }

    return i;
}

//checks if a string str1 is a substring of str2
int substring(char *str1, char *str2)
{
    if (strlen(str1) > strlen(str2))
        return 0;

    if (strstr(str2, str1) != NULL)
    {//checks if str1 is a substring of str2, if true so we get a pointer which isnt null
        return 1;
    }

    return 0;
}
