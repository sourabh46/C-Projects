/***** Declaration of Header(Library) Files ****/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


/***** Declaration of functions **********/
void startGame();
int characterActivity();
void characterOutputStatus();
int characterEncounterActivity();
void characterChoiceActivity();
char * getRoomText();
void healCharacter();
int checkIfSnakeAttacks();
int snakeEncounterActivity();
char * getAvailableDirections();
int characterCombatChoiceActivity();
void escapeAttempt(int *combatEnded);
void attackAttempt(int *combatEnded);
int getCharacterChoice();
void save();
void load();

//Initial coordinates
int xCoordinate = 1;
int yCoordinate = 0;

//Initial character health
int characterHealth = 100;

//Data-type for character
struct Character
{
    int xPosition;
    int yPosition;
    int health;
};

static struct Character character;
static int turns = 0;

//Room text description
static char roomTexts[4][4][200] =
{
    {
        {"You see a gaping canyon before you blocking your path to the left.\nYou can go:\n"},
        {"You Can go:\n"},
        {"You Can go:\n"},
        {"You Can go:\n"},
    },
    {
        {"You enter the forest of a thousand truths. You Can go:\n"},
        {"You Can go:\n"},
        {"You Can go:\n"},
        {"You Can go:\n"},
    },
    {
        {"You enter the forest of a thousand truths. You Can go:\n"},
        {"You Can go:\n"},
        {"You Can go:\n"},
        {"You Can go:\n"},
    },{
        {"You Can go:\n"},
        {"You Can go:\n"},
        {"You Can go:\n"},
        {"You enter a holy place. You Can go:\n "},
    }
};

//X Y direction for 4x4 room
static int availableDirections[4][4][4]  =
{
    //Definition for a room's available directions: Up, Right, Down, Left. 0 - blocked, 1 - available
    {
        //x=0
        { 1, 1, 0, 0}, //y=0
        { 1,1, 1, 0},  //y=1
        { 1, 1, 1, 0}, //y=2
        { 0, 1, 1, 0}, //y=3
    },{ //x=1
        { 1, 1, 0, 1}, //y=0
        { 1, 1, 1, 1}, //y=1
        { 1, 1, 1, 1}, //y=2
        { 0, 1, 1, 1}, //y=3
    },{ //x=2
        { 1, 1, 0, 1}, //y=0
        { 1, 1, 1, 1}, //y=1
        { 1, 1, 1, 1}, //y=2
        { 0, 1, 1, 1}, //y=3
    },{ //x=3
        { 1, 0, 0, 1}, //y=0
        { 1, 0, 1, 1}, //y=1
        { 1, 0, 1, 1}, //y=2
        { 0, 0, 1, 1}, //y=3
    }
};

static int turnsNeededForHealing = 0;
static int snakeHealth = 200;

// All 4 direction names - up, right, down, left
static char directionNames[4][10]  =
{
    "(u)p",
    "(r)ight",
    "(d)own",
    "(l)eft"
};

/***** Main Function *********/
int main()
{
    //Initialize character position
    character.xPosition = xCoordinate;
    character.yPosition = yCoordinate;
    character.health = characterHealth;

    //Start the game
    startGame();
    return 0;
}

/**** Basic game function that runs endlessly until game is over ****/
void startGame()
{
    int gameOverStatus = 0;
    while(1)
    {
        gameOverStatus = characterActivity();
        if(gameOverStatus == 1)
        {
            break;
        }
    }
}

/**** Function that handles character activity, e.g. number of turns, calls output status etc ****/
int characterActivity()
{
    int gameOverStatus;
    //Increment turn counter
    turns++;
    //Decrement of amount of turns until next healing is available
    if(turnsNeededForHealing > 0)
    {
        turnsNeededForHealing--;
    }
    //Output details about Character's status: health, location, etc.
    characterOutputStatus();
    //Handle a random encounter, and check whether it caused the game to end
    gameOverStatus = characterEncounterActivity();
    if(gameOverStatus > 0)
    {
        return 1;
    }
    //Give Character a choice for further exploration
    characterChoiceActivity();
    return 0;
}

/**** Function that displays output status ****/
void characterOutputStatus()
{
    char* roomText;
    //Get room description text
    roomText = getRoomText();
    printf("\n\n\n\n");
    printf("\nCharacter location: X: %d Y: %d",character.xPosition,character.yPosition);
    printf("\nCharacter health: %d",character.health);
    printf("\nCurrent turn: %d \n",turns);
    printf("\n%s",roomText);
    printf("\n\n");
}

/**** Function that determines if character needs to heal or face encounter with snake ****/
int characterEncounterActivity()
{
    switch(character.xPosition)
    {
    case 0:
        switch(character.yPosition)
        {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        }
        break;
    case 1:
        switch(character.yPosition)
        {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        }
        break;
    case 2:
        switch(character.yPosition)
        {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        }
        break;
    case 3:
        switch(character.yPosition)
        {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            //Healing place in X:3 Y:3
            healCharacter();
            break;
        }
        break;
    }
    if(checkIfSnakeAttacks())
    {
        return snakeEncounterActivity();
    }
    return 0;
}

/**** Function that handles character's choice and also prompts for save/load game ****/
void characterChoiceActivity()
{
    printf("(s)ave\nl(o)ad");
    int choice = getCharacterChoice();
    switch(choice)
    {
    //u refers to up, ASCII value of u is equal to 117
    case 117:
        if(availableDirections[character.xPosition][character.yPosition][0])
        {
            printf("\nYou chose to go up.\n\n");
            character.yPosition++;
        }
        else
        {
            printf("\nYou cannot go there");
        }
        break;
    //r refers to right, ASCII value of r is equal to 114
    case 114:
        if(availableDirections[character.xPosition][character.yPosition][1])
        {
            printf("\nYou chose to go right.\n\n");
            character.xPosition++;
        }
        else
        {
            printf("\nYou cannot go there");
        }
        break;
    //d refers to down, ASCII value of d is equal to 100
    case 100:
        if(availableDirections[character.xPosition][character.yPosition][2])
        {
            printf("\nYou chose to go down.\n\n");
            character.yPosition--;
        }
        else
        {
            printf("\nYou cannot go there");
        }
        break;
    //l refers to left, ASCII value of l is equal to 108
    case 108:
        if(availableDirections[character.xPosition][character.yPosition][3])
        {
            printf("\nYou chose to go left.\n\n");
            character.xPosition--;
        }
        else
        {
            printf("\nYou cannot go there");
        }
        break;
    //s refers to save option, ASCII value of s is equal to 115
    case 115:
        save();
        break;
    //o refers to load option, ASCII value of o is equal to 111
    case 111:
        load();
        break;
    default:
        printf("Unknown choice %d", choice);
    }
    getchar();
}

/**** Function that returns room-text for character's current position ****/
char * getRoomText()
{
    static char fullString[240];
    strcpy(fullString,"");
    strcat(fullString, roomTexts[character.xPosition][character.yPosition]);
    return fullString;
}

/**** Function that determines if character needs healing or not ****/
void healCharacter()
{
    if(turnsNeededForHealing == 0)
    {
        printf("Congratulations, you received +20 health bonus.\n");
        character.health += 20;
        turnsNeededForHealing += 5;
    }
    else
    {
        printf("Sorry, you have to wait for %d turns to get health bonus.\n",turnsNeededForHealing);
    }
}

/**** Function that calculates if there is a possibility of snake-attack depending on the result (random number modulus 10) ****/
int checkIfSnakeAttacks()
{
    int randomResult;
    time_t t;
    srand((unsigned) time(&t));
    randomResult = rand() % 10;
    // Value 9 will only produce a snake attack, otherwise no attack. Less possibility of snake attack.
    if(randomResult > 8)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**** Function that prints snake activity and triggers for character's choice of combat ****/
int snakeEncounterActivity()
{
    printf("A dangerous snake appears in front of you.\n");
    printf("It has %d health left\n", snakeHealth);
    printf("If you choose to run, you will always be successful. \n");
    printf("If you choose to attack, you have a 2-out-of-6 chance to do 20 damage. \n");
    return characterCombatChoiceActivity();
}

/**** Function that takes input (char data) from user and returns its ASCII value in integer ****/
int getCharacterChoice()
{
    char selected;
    char* availableDirections;
    availableDirections  = getAvailableDirections();
    printf("\n%s\nWhere will you go? Choose wisely:  ",availableDirections);
    scanf(" %c", &selected);
    return (int)selected;
}

/**** Function that checks the matrix "availableDirections" and returns the direction string that is accessible by character ****/
char * getAvailableDirections()
{
    static char availableDirectionString[40];
    strcpy(availableDirectionString,"");
    //Iterate through all directions, and if the value is 1, add to the Character output
    for(int i = 0; i < 4; i++)
    {
        if(availableDirections[character.xPosition][character.yPosition][i])
        {
            strcat(availableDirectionString, directionNames[i]);
            strcat(availableDirectionString,"\n");
        }
    }
    return availableDirectionString;
}

/**** Function that takes input (char data) from user and switch-case the option for either Escape or Encounter the snake and also checks the health of character ****/
int characterCombatChoiceActivity()
{
    char selected;
    int combatEnded;
    combatEnded = 0;
    printf("\n\nDo you: (r)un or (a)ttack\n");
    //Pass the MEMORY ADDRESS of the selected value to the scanf function
    scanf(" %c", &selected);
    switch(selected)
    {
    case 'r':
        //Pass the reference to the Combat ended variable
        escapeAttempt(&combatEnded);
        break;
    case 'a':
        attackAttempt(&combatEnded);
        break;
    default:
        printf("Invalid option.\n");
        combatEnded = 0;
    }
    if(character.health <= 0)
    {
        printf("You died!\nGame over\n");
        return 1;
    }
    if(snakeHealth <= 0)
    {
        printf("You killed the snake!\nGame over\n");
        return 1;
    }
    if(!combatEnded)
    {
        return characterCombatChoiceActivity();
    }
    return 0;
}

/**** Function to escape the encounter with snake. Always successful to escape. ****/
void escapeAttempt(int *combatEnded)
{
    printf("You have succeeded in escaping the snake without harm!\n");
    *combatEnded = 1;
}

/**** Function to face the encounter with snake. Big possibility of health damage. ****/
void attackAttempt(int *combatEnded)
{
    int randomResult;
    time_t t;
    srand((unsigned) time(&t));
    randomResult = rand() % 6;
    if(randomResult > 3)
    {
        printf("You have succeeded in hitting the snake without harm!\n");
        snakeHealth -= 20;
        *combatEnded = 0;
    }
    else
    {
        printf("You try to hit, but fail miserably.\nYou lose 20 health\n");
        character.health -= 20;
        *combatEnded = 0;
    }
    printf("Snake health %d\n", snakeHealth);
    printf("Character health %d\n\n\n",character.health);
}

/**** Function to save the current status of the game (character x-y coordinates, health, turns left for healing, number of turns, snake's health) to the file ****/
void save()
{
    FILE *fp;
    fp = fopen("adventure_game.txt", "w+");
    fprintf(fp,"%d %d %d %d %d %d", character.xPosition, character.yPosition, character.health, turnsNeededForHealing, turns, snakeHealth);
    fclose(fp);
    turns -=1;
}

/**** Function to load the last-saved status of the game (character x-y coordinates, health, turns left for healing, number of turns, snake's health) from the file ****/
void load()
{
    FILE *fp;
    fp = fopen("adventure_game.txt", "r");
    fscanf(fp,"%d %d %d %d %d %d", &character.xPosition, &character.yPosition, &character.health, &turnsNeededForHealing, &turns, &snakeHealth);
    fclose(fp);
    turns -=1;
}
