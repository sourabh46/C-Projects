/***** Declaration of Header(Library) Files ****/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/***** Declaration of Constants ****/
#define LENGTH 30
#define MAX_CHAR 256

/***** Data Structure of Alphabetic Order Node ****/
struct OrderNode
{
    char letter;
    bool isLowerCase;
    int count;
};

struct OrderNode* orderNodeTable[LENGTH] = { NULL };

/***** Declaration of used functions prototypes **********/
bool checkLetter(char letter);
bool checkLowerCase(char letter);
bool prepareAlphabeticOrder(char* alphabeticOrder, int length);
int parseInputToAlphabeticOrder(char* input, int length);
void printAlphabeticOrder();
void clearAllocatedMemoryOfAlphabeticOrder();

/***** Declaration of main function **********/
int main ()
{
    char alphabeticOrder[LENGTH], input[MAX_CHAR];
    bool isAlphabeticOrderPrepared = false;
    int result = 0;

    printf("Enter the alphabetic order: ");
    scanf("%s", alphabeticOrder);

    /* Prepare the Alphabetic Order */
    isAlphabeticOrderPrepared = prepareAlphabeticOrder(alphabeticOrder, strlen(alphabeticOrder));

    if (isAlphabeticOrderPrepared == false)
    {
        printf("FUNC %s - Error occurred to prepare alphabetic order!\n", __func__);
        return -1;
    }

    printf("Enter the input string: ");
    scanf("%s", input);

    /* Parse the Input String into Alphabetic Order */
    result = parseInputToAlphabeticOrder(input, strlen(input));

    if (result == -1)
    {
        printf("FUNC %s - Error occurred to parse input string!\n", __func__);
        return -1;
    }

    /* Print the result into Alphabetic Order */
    printAlphabeticOrder();

    /* Free occupied heap memory */
    clearAllocatedMemoryOfAlphabeticOrder();

    return 0;
}

/*
* Check if input character is a valid letter or not.
*/
bool checkLetter(char letter)
{
    if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
* Check if input character is a lower-case or not.
*/
bool checkLowerCase(char letter)
{
    if (letter >= 'a' && letter <= 'z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
* Prepare alphabetic order by constructing table.
*/
bool prepareAlphabeticOrder(char* alphabeticOrder, int length)
{
    int index;
    for(index = 0; index < length; index++)
    {
        struct OrderNode* orderNode = (struct OrderNode*)malloc(sizeof(struct OrderNode));
        if (orderNode == NULL)
        {
            printf("FUNC %s - Unable to allocate memory for alphabetic order!\n", __func__);
            return false;
        }
        if (checkLetter(alphabeticOrder[index]))
        {
            orderNode->letter = toupper(alphabeticOrder[index]);
            orderNode->isLowerCase = false;
            orderNode->count = 0;
            orderNodeTable[index] = orderNode;
        }
        else
        {
            printf("FUNC %s - Alphabetic order contains unexpected character!\n", __func__);
            return false;
        }
    }
    return true;
}

/*
* Parse input string to alphabetic order with required information (case, count).
*/
int parseInputToAlphabeticOrder(char* input, int length)
{
    int index, position, result = 0;
    for(index = 0; index < length; index++)
    {
        if (checkLetter(input[index]) == false)
        {
            printf("FUNC %s - Input string contains unexpected character!\n", __func__);
            return -1;
        }
        position = 0;
        while(orderNodeTable[position] != NULL)
        {
            if((orderNodeTable[position]->letter == input[index]) ||
                (orderNodeTable[position]->letter == toupper(input[index])))
            {
                if(checkLowerCase(input[index]))
                {
                    orderNodeTable[position]->isLowerCase = true;
                }
                else
                {
                    orderNodeTable[position]->isLowerCase = false;
                }
                orderNodeTable[position]->count++;
                result++;
            }
            position++;
        }
    }
    return result;
}

/*
* Print result in Alphabetic Order.
*/
void printAlphabeticOrder()
{
    int position, index;

    position = 0;
    while(orderNodeTable[position] != NULL)
    {
        for(index = 0; index < orderNodeTable[position]->count; index++)
        {
            if(orderNodeTable[position]->isLowerCase)
            {
                printf("%c", tolower(orderNodeTable[position]->letter));
            }
            else
            {
                printf("%c", orderNodeTable[position]->letter);
            }
        }
        position++;
    }
    return;
}

/*
* Free occupied heap memory.
*/
void clearAllocatedMemoryOfAlphabeticOrder()
{
    int position = 0;
    while(position < LENGTH)
    {
        if(orderNodeTable[position] != NULL)
        {
            free(orderNodeTable[position]);
            orderNodeTable[position] = NULL;
        }
        position++;
    }
    return;
}
