/*
 * STUDENT NUMBER: 40338732
 * STUDENT NAME:   Anthony Wright
 * NAPIER UNIVERSITY
 * APRIL 2020
 * CONNECT 4
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread_time.h>
#include <ctype.h>
#include <inttypes.h>

#define MAX 64
#define ARRMAX 8

// define and init array with numbers > 300
int playersShots[MAX] = {301, 302, 303, 304, 305, 306, 307, 308,
                         309, 310, 311, 312, 313, 314, 315, 316,
                         317, 318, 319, 320, 321, 322, 323, 324,
                         325, 326, 327, 328, 329, 330, 331, 332,
                         333, 334, 335, 336, 337, 338, 339, 340,
                         341, 342, 343, 344, 345, 346, 347, 348,
                         349, 350, 351, 352, 353, 354, 355, 356,
                         357, 358, 359, 360, 361, 362, 363, 364};

/// Used to store the value from the peek method
int peekValue = 0;

/// BASE STRUCT (Struct, Init, Push, Pop, Peek, Size, Is Empty)
struct stack;

void init_Stack(struct stack *s);

void push(struct stack *s, int item);

int pop(struct stack *s);

int peek(struct stack *s);

int isEmptyStack(struct stack *s);

int changePlayer(int players);

void displayGrid(struct stack *s, int player, char column);

int findInArray(struct stack *s, int checkNumber);

void print_current_time_with_ms(void);

void checkPlayerMove(struct stack *s, int playerShot);

void displayGridOnce();

void displayGrid2(struct stack *s, int removeNum);

int main();


/******************************************************************************
 ******************************************************************************
 */


// DEBUGGING TIME STAMP
void print_current_time_with_ms(void) {
    long ms; // Milliseconds
    time_t s;  // Seconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);
    s = spec.tv_sec;
    ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
    if ( ms > 999 ) {
        s++;
        ms = 0;
    }
    //printf("Current time: %"PRIdMAX".%03ld seconds\n",
    // (intmax_t) s, ms);
}

// Create the stack
struct stack {
    int playersMoves[MAX];
    int top;
};

// stack is full when top is equal to the last index
int isFull(struct stack *stack) {
    return stack->top == MAX - 1;
}

// Push the player/MoveID to the stack
// four steps - 1, is stack full, 2, show error and quit
// 3, if not full increment Top
// 4, add data element to the stack

void push(struct stack *s, int item) {
    if ( s->top == MAX - 1 ) {
        printf(" Stack is full . Couldn’t push ’%d’ onto stack \n", item);
        return;
    }
    s->top++;
    s->playersMoves[s->top] = item;
}

// Pop (remove) the last push from the stack

int pop(struct stack *s) {
    int data;
    if ( s->top == -1 ) {
        printf("Stack is Empty\n");
        return NULL;
    }
    data = &s->playersMoves[s->top];
    s->top--;
    return data;
}

// initialization The stack
void init_Stack(struct stack *s) {
    int i;
    for ( i = 0; i < MAX; i++ ) {
        s->playersMoves[i] = 999;
    }

    s->top = -1;
}

// Checks to see if the stack is Empty
int isEmptyStack(struct stack *s) {
    return s->top == -1;
}

// Returns the last value but doesn't remove it from the stack
int peek(struct stack *s) {
    if ( !isEmptyStack(s)) {
        return s->playersMoves[s->top];
    }
    return -1;
}

// Used after each move to switch the players ID
int changePlayer(int players) {
    int newPlayer = 0;
    if ( players == 1 ) {
        newPlayer = 2;
    } else {
        newPlayer = 1;
    }
    return newPlayer;
}

// passes in a value and a pointer to a stack
// return a true or false if its present in the array.
int valueinarray(int val, struct stack *s) {
    int i;
    for ( i = 0; i < sizeof(s->playersMoves) / sizeof(s->playersMoves[0]); i++ ) {
        if ( s->playersMoves[i] == val )
            return 1;
    }
    return 0;
}

// USED TO CHECK THE PLAYERS MOVE SO PLAYER ONE ISN'T OVERWRITTING THE PREVIOUS PLAYS MOVE
int findInArray(struct stack *s, int checkNumber) {

    int i;
    for ( i = 0; i < MAX; i++ ) {
        if ( s->playersMoves[i] == checkNumber ) {
            return 1;
        }
    }
    return 2;
}

// used to check the players move to find out IF a 4 in a line has be created.
void checkPlayerMove(struct stack *s, int playerShot) {
    // TODO - SET THE BOUNDARY
    int leftends[ARRMAX] = {0, 8, 16, 24, 32, 40, 48, 56};
    int topends[ARRMAX] = {0, 1, 2, 3, 4, 5, 6, 7};
    int bottomends[ARRMAX] = {56, 57, 58, 59, 60, 61, 62, 63};
    int rightends[ARRMAX] = {7, 15, 23, 31, 39, 47, 55, 63};

    int arr[MAX];
    // Declare INT Variables
    int n, c, d, t, flag = 0;
    // Get Size of the playersShot Array
    n = sizeof(s->playersMoves) / sizeof(s->playersMoves[0]);

    /// Sorted list in ascending order
    /// https://www.programmingsimplified.com/c/source-code/c-program-insertion-sort
    /// INSERTION SORT
    /// Best case complexity of insertion sort is O(n), average and the worst case complexity is O(n2)
    for ( c = 1; c <= n - 1; c++ ) {
        t = s->playersMoves[c];

        for ( d = c - 1; d >= 0; d-- ) {
            if ( s->playersMoves[d] > t ) {
                s->playersMoves[d + 1] = s->playersMoves[d];
                flag = 1;
            } else
                break;
        }
        if ( flag )
            s->playersMoves[d + 1] = t;
    }

    /// duplicated sorted array
    for ( c = 0; c <= n; c++ ) {
        arr[c] = s->playersMoves[c];
    }

    // DECLARE INT
    int s1, m, dd, e;
    int counter = 0;

    ///**************************************************************************
    ///**************************************************************************
    ///****************************** LINE RIGHT CHECK **************************

    for ( s1 = 0; s1 < n; s1++ ) {
        if ( arr[s1] == playerShot ) {
            counter++;
            int row = ((playerShot % 100) / 8 + 1);
            for ( m = 0; m < n; m++ ) {
                if ( arr[m] == (playerShot + 1)) {
                    counter++;
                    int row1 = (((playerShot + 1) % 100) / 8 + 1);
                    if ( row == row1 ) {
                        for ( dd = 0; dd < n; dd++ ) {
                            if ( arr[dd] == (playerShot + 2)) {
                                counter++;
                                int row2 = (((playerShot + 2) % 100) / 8 + 1);
                                if ( row == row2 ) {
                                    for ( e = 0; e < n; e++ ) {
                                        if ( arr[e] == (playerShot + 3)) {
                                            int row3 = (((playerShot + 3) % 100) / 8 + 1);
                                            if ( row == row3 ) {
                                                counter++;
                                                break;
                                            } else { break; }
                                        }
                                    }
                                } else { break; }
                            }
                        }
                    } else { break; }
                }

            }
        }
    }

    /// CHECK LEFT
    if ( counter != 4 ) {

        for ( s1 = 0; s1 < n; s1++ ) {
            if ( arr[s1] == playerShot ) {
                int row = ((playerShot % 100) / 8 + 1);
                for ( m = 0; m < n; m++ ) {
                    if ( arr[m] == (playerShot - 1)) {
                        counter++;
                        int row1 = (((playerShot - 1) % 100) / 8 + 1);
                        if ( row == row1 ) {
                            for ( dd = 0; dd < n; dd++ ) {
                                if ( arr[dd] == (playerShot - 2)) {
                                    counter++;
                                    int row2 = (((playerShot - 2) % 100) / 8 + 1);
                                    if ( row == row2 ) {
                                        for ( e = 0; e < n; e++ ) {
                                            if ( arr[e] == (playerShot - 3)) {
                                                int row3 = (((playerShot - 3) % 100) / 8 + 1);
                                                if ( row == row3 ) {
                                                    counter++;
                                                    break;
                                                } else { break; }
                                            }
                                        }
                                    } else { break; }
                                }
                            }
                        } else { break; }
                    }
                }
            }
        }
    }

    if ( counter == 5 ) {
        printf("Connect **4 in a line**\n\n");
    }
    ///**************************************************************************
    ///**************************************************************************
    ///****************************** LINE LEFT CHECK ***************************
    /// print_current_time_with_ms(); // checking how long it takes

    if ( counter != 4 ) {
        counter = 0;
        for ( s1 = 0; s1 < n; s1++ ) {
            if ( arr[s1] == playerShot ) {
                counter++;
                int row = ((playerShot % 100) / 8 + 1);
                for ( m = 0; m < n; m++ ) {
                    if ( arr[m] == (playerShot - 1)) {
                        counter++;
                        int row1 = (((playerShot - 1) % 100) / 8 + 1);
                        if ( row == row1 ) {
                            for ( dd = 0; dd < n; dd++ ) {
                                if ( arr[dd] == (playerShot - 2)) {
                                    counter++;
                                    int row2 = (((playerShot - 2) % 100) / 8 + 1);
                                    if ( row == row2 ) {
                                        for ( e = 0; e < n; e++ ) {
                                            if ( arr[e] == (playerShot - 3)) {
                                                int row3 = (((playerShot - 3) % 100) / 8 + 1);
                                                if ( row == row3 ) {
                                                    counter++;
                                                    break;
                                                } else { break; }
                                            }
                                        }
                                    } else { break; }
                                }
                            }
                        } else { break; }
                    }
                }
            }
        }
    }

    ///**************************************************************************
    ///**************************************************************************
    ///****************************** COLUMN UPWARD CHECK WORKING***********************
    ///print_current_time_with_ms(); // checking how long it takes

    if ( counter != 4 ) {
        counter = 0;
        for ( s1 = 0; s1 < n; s1++ ) {
            if ( arr[s1] == playerShot ) {
                counter++;
                for ( m = 0; m < n; m++ ) {
                    if ( arr[m] == (playerShot - 8)) {
                        counter++;
                        for ( dd = 0; dd < n; dd++ ) {
                            if ( arr[dd] == (playerShot - 16)) {
                                counter++;
                                for ( e = 0; e < n; e++ ) {
                                    if ( arr[e] == (playerShot - 24)) {
                                        counter++;
                                        break;
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ///**************************************************************************
    ///**************************************************************************
    ///*************************** COLUMN DOWNWARD CHECK ************************
    ///print_current_time_with_ms(); // checking how long it takes

    if ( counter != 4 ) {
        //  printf("Start down\n");
        counter = 0;
        for ( s1 = 0; s1 < n; s1++ ) {
            if ( arr[s1] == playerShot ) {
                counter++;
                for ( m = 0; m < n; m++ ) {
                    if ( arr[m] == (playerShot + 8)) {
                        counter++;
                        for ( dd = 0; dd < n; dd++ ) {
                            if ( arr[dd] == (playerShot + 16)) {
                                counter++;
                                for ( e = 0; e < n; e++ ) {
                                    if ( arr[e] == (playerShot + 24)) {
                                        counter++;
                                        //                                printf("Downward counter : %d\n", counter);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ///**************************************************************************
    ///**************************************************************************
    ///****************************** DIA BOTTOM LEFT ***************************
    ///print_current_time_with_ms(); // checking how long it takes

    if ( counter != 4 ) {
        //   printf("Start down Left\n");
        counter = 0;
        for ( s1 = 0; s1 < n; s1++ ) {
            if ( arr[s1] == playerShot ) {
                counter++;
                for ( m = 0; m < n; m++ ) {
                    if ( arr[m] == (playerShot + 7)) {
                        counter++;
                        for ( dd = 0; dd < n; dd++ ) {
                            if ( arr[dd] == (playerShot + 14)) {
                                counter++;
                                for ( e = 0; e < n; e++ ) {
                                    if ( arr[e] == (playerShot + 21)) {
                                        counter++;
                                        //                                 printf("DIAG DOWNWARD LEFT  : %d", counter);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ///**************************************************************************
    ///**************************************************************************
    ///****************************** DIA BOTTOM RIGHT ***************************
    /// print_current_time_with_ms(); // checking how long it takes

    if ( counter != 4 ) {
        //   printf("Start down Left\n");
        counter = 0;
        for ( s1 = 0; s1 < n; s1++ ) {
            if ( arr[s1] == playerShot ) {
                counter++;
                for ( m = 0; m < n; m++ ) {
                    if ( arr[m] == (playerShot + 9)) {
                        counter++;
                        for ( dd = 0; dd < n; dd++ ) {
                            if ( arr[dd] == (playerShot + 18)) {
                                counter++;
                                for ( e = 0; e < n; e++ ) {
                                    if ( arr[e] == (playerShot + 27)) {
                                        counter++;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ///**************************************************************************
    ///**************************************************************************
    ///****************************** DIA TOP LEFT ***************************
    ///  print_current_time_with_ms(); // checking how long it takes

    if ( counter != 4 ) {
        //  printf("DIA TOP LEFT\n");
        counter = 0;
        for ( s1 = 0; s1 < n; s1++ ) {
            if ( arr[s1] == playerShot ) {
                counter++;
                for ( m = 0; m < n; m++ ) {
                    if ( arr[m] == (playerShot - 9)) {
                        counter++;
                        for ( dd = 0; dd < n; dd++ ) {
                            if ( arr[dd] == (playerShot - 18)) {
                                counter++;
                                for ( e = 0; e < n; e++ ) {
                                    if ( arr[e] == (playerShot - 27)) {
                                        counter++;
                                        //                                printf("DIAG TOP RIGHT  : %d", counter);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ///**************************************************************************
    ///**************************************************************************
    ///****************************** DIA TOP RIGHT ***************************
    ///print_current_time_with_ms(); // checking how long it takes

    if ( counter != 4 ) {
        //  printf("DIA TOP RIGHT\n");
        counter = 0;
        for ( s1 = 0; s1 < n; s1++ ) {
            if ( arr[s1] == playerShot ) {
                counter++;
                for ( m = 0; m < n; m++ ) {
                    if ( arr[m] == (playerShot - 7)) {
                        counter++;
                        for ( dd = 0; dd < n; dd++ ) {
                            if ( arr[dd] == (playerShot - 14)) {
                                counter++;
                                for ( e = 0; e < n; e++ ) {
                                    if ( arr[e] == (playerShot - 21)) {
                                        counter++;
                                        //                                printf("DIAG TOP RIGHT  : %d", counter);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if ( counter >= 4 ) {
        printf("Connect **4 in a line**\n\n");
    } else {
        int spareCell = 0;
        int i;
        for ( i = 0; i < MAX; i++ ) {
            if ( arr[i] = 999 ) {
                spareCell = 1;
                break;
            } else {
                spareCell = 0;
            }
        }
        if ( spareCell == 0 ) {
            printf("No move cells left");
        }
    }

}

// CREATES AND DISPLAYS AN EMPTY GRID USED AT THE BEGINNING OF THE GAME
void displayGridOnce() {
    printf("CONNECT 4 GRID\n\n");
    printf("|   A\t|   B\t|   C\t|   D\t|   E\t|   F\t|   G\t|   H\t|\n");
    int i;
    for ( i = 0; i < 8; i++ ) {
        printf("|    \t|    \t|   \t|    \t|    \t|    \t|    \t|    \t|\n");
    }
    printf("\n");
}

// USED TO DISPLAY THE GRID (BOARD) AFTER EACH MOVE
void displayGrid(struct stack *s, int player, char columnid) {

    // loop over &s->playersMoves[x] array
    // from each element get the first int i.e. 156 get 1
    // then save it as 'X' and save it to the playerShots array in the right element
    // i.e. 156 = save 'X' in array element 56

    // Used to display the players shots in the grid
    //int playersShots[MAX] = {301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 232, 333, 334, 335,336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353,354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364};
    print_current_time_with_ms(); // checking how long it takes
    int ix;
    for ( ix = 0; ix < MAX; ix++ ) {
        int numbers = s->playersMoves[ix];
        int arrayNumber = numbers % 100;
        int playerNumber = (numbers - arrayNumber) / 100;
        if ( playerNumber == 1 ) {
            playersShots[arrayNumber] = 1;
        } else if ( playerNumber == 2 ) {
            playersShots[arrayNumber] = 2;
        } else {
            playersShots[arrayNumber] = 0;
        }
    }


    int newLine[8] = {7, 15, 23, 31, 39, 47, 55, 63};

    printf("\n|   A\t|   B\t|   C\t|   D\t|   E\t|   F\t|   G\t|   H\t|\n");
    int ia;
    for ( ia = 0; ia < MAX; ia++ ) {
        // End of line needs a "new Line" else its a tab
        //get array number
        int arrayNumber = playersShots[ia];
        int isEndOfRow = 0;
        int i;
        for ( i = 0; i < 8; i++ ) {
            if ( newLine[i] == ia ) {
                isEndOfRow = 1;
            }
        }

        if ( isEndOfRow == 1 ) {
            if ( playersShots[ia] == 1 ) {
                printf("|   X\n");
            } else if ( playersShots[ia] == 2 ) {
                printf("|   O\n");
            } else {
                printf("|    \n");
            }

        } else {
            if ( playersShots[ia] == 1 ) {
                printf("|   X\t");
            } else if ( playersShots[ia] == 2 ) {
                printf("|   O\t");
            } else {
                printf("|    \t");
            }
        }
        isEndOfRow = 0;
    }


    return;
}

// USED WHEN THE UNDO AND REDO MOVE HAS HAPPEN
void displayGrid2(struct stack *s, int removeNum) {

    // loop over &s->playersMoves[x] array
    // from each element get the first int i.e. 156 get 1
    // then save it as 'X' and save it to the playerShots array in the right element
    // i.e. 156 = save 'X' in array element 56

    // Used to display the players shots in the grid
    //int playersShots[MAX] = {301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 232, 333, 334, 335,336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353,354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364};

    int ix;
    for ( ix = 0; ix < MAX; ix++ ) {
        int numbers = s->playersMoves[ix];
        if ( numbers == removeNum ) {
            int arrayNumber = numbers % 100;
            playersShots[arrayNumber] = 0;
        } else {
            int arrayNumber = numbers % 100;
            int playerNumber = (numbers - arrayNumber) / 100;
            if ( playerNumber == 1 ) {
                playersShots[arrayNumber] = 1;
            } else if ( playerNumber == 2 ) {
                playersShots[arrayNumber] = 2;
            } else {
                playersShots[arrayNumber] = 0;
            }
        }
    }


    int newLine[8] = {7, 15, 23, 31, 39, 47, 55, 63};

    printf("\n|  A \t|  B \t|  C\t|  D \t|  E \t|  F \t|  G \t|  H \t| \n");
    int ia;
    for ( ia = 0; ia < MAX; ia++ ) {
        // End of line needs a "new Line" else its a tab
        //get array number
        int arrayNumber = playersShots[ia];
        int isEndOfRow = 0;
        int i;
        for ( i = 0; i < 8; i++ ) {
            if ( newLine[i] == ia ) {
                isEndOfRow = 1;
            }
        }

        if ( isEndOfRow == 1 ) {
            if ( playersShots[ia] == 1 ) {
                printf("|   X\n");
            } else if ( playersShots[ia] == 2 ) {
                printf("|   O\n");
            } else {
                printf("|    \n");
            }

        } else {
            if ( playersShots[ia] == 1 ) {
                printf("|   X\t");
            } else if ( playersShots[ia] == 2 ) {
                printf("|   O\t");
            } else {
                printf("|    \t");
            }
        }
        isEndOfRow = 0;
    }


    return;
}


/// MAIN METHOD
int main() {

    // Declare and init Stack
    struct stack s;
    init_Stack(&s);
    s.top = -1;

    // Declare varibles
    int player;
    int move = 'z';
    int isPresent;
    int choice;
    // Print on screen
    printf("\n ********************************** \n");
    printf("\n *** Start the game of Connect 4*** \n");
    printf("\n ********************************** \n");

    printf("\nPlease select The player 1 or 2: ");

    scanf("%d", &player);

    int showboard = 0; // set the show board to 0 so it only shows once
    do {

        printf("\n Play (Press 1)"); // push
        printf("\n Undo (Press 2)"); // peek - pop
        printf("\n Redo (Press 3)"); // peek - push
        printf("\n Exit (Press 4)"); // exit

        printf("\n Enter your option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Show the board once when first starting
                // once showboard = 1 we no longer show it
                if ( showboard == 0 ) {
                    showboard = 1;
                    displayGridOnce();
                }

                //user select column
                printf("\n Please select a column (a-h): ");
                getchar();
                scanf("%c", &move);

                // check and convert to lowercase
                if ( !islower(move)) { move = _tolower(move); }
                // check only inputs of a - h is used
                if ((move == 'a') || (move == 'b') || (move == 'c') || (move == 'd') || (move == 'e') ||
                    (move == 'f') || (move == 'g') || (move == 'h')) {
                    // START
                    // Array of number of the value of Each Column
                    int columnAArray[8] = {56, 48, 40, 32, 24, 16, 8, 00};
                    int columnBArray[8] = {57, 49, 41, 33, 25, 17, 9, 01};
                    int columnCArray[8] = {58, 50, 42, 34, 26, 18, 10, 02};
                    int columnDArray[8] = {59, 51, 43, 35, 27, 19, 11, 03};
                    int columnEArray[8] = {60, 52, 44, 36, 28, 20, 12, 04};
                    int columnFArray[8] = {61, 53, 45, 37, 29, 21, 13, 05};
                    int columnGArray[8] = {62, 54, 46, 38, 30, 22, 14, 06};
                    int columnHArray[8] = {63, 55, 47, 39, 31, 23, 15, 07};

                    // declare Variables
                    int check;
                    int arrayNum;
                    int playerOne;
                    int playerTwo;
                    int item;

                    // Switch for each "Column" selected
                    // defines the array of number (Column) for each move
                    for ( check = 0; check < 8; check++ ) {
                        // check both players
                        if ( move == 'a' ) { arrayNum = columnAArray[check]; }
                        else if ( move == 'b' ) { arrayNum = columnBArray[check]; }
                        else if ( move == 'c' ) { arrayNum = columnCArray[check]; }
                        else if ( move == 'd' ) { arrayNum = columnDArray[check]; }
                        else if ( move == 'e' ) { arrayNum = columnEArray[check]; }
                        else if ( move == 'f' ) { arrayNum = columnFArray[check]; }
                        else if ( move == 'g' ) { arrayNum = columnGArray[check]; }
                        else if ( move == 'h' ) { arrayNum = columnHArray[check]; }

                        // set the players moves to allow checking if that 'Slot' is already occupied
                        playerOne = arrayNum + 100;
                        playerTwo = arrayNum + 200;

                        if ( player == 1 ) { item = playerOne; }
                        else { item = playerTwo; }

                        // is the selected slot filled
                        isPresent = findInArray(&s, playerTwo);

                        if ( isPresent == 2 ) // not present in first row for player two
                        {
                            isPresent = findInArray(&s, playerOne);
                            if ( isPresent == 2 ) // not present in first row for player two
                            {
                                push(&s, item); // push to the stack
                                break;
                                //TODO - if they get to end of column and its full
                            }
                        }
                    }

                    displayGrid(&s, player, move);
                    checkPlayerMove(&s, item);
                    player = changePlayer(player);
                    printf("\nplayer %d move:   (player 1 = X, Player 2 = O)", player);
                    break;
                } else {
                    printf("INCORRECT VALUE ENTERED: Please try again");
                    break;
                }

            case 2: // Undo = peek then pop (remove)
                //first "PEEK" the value and store it then pop it
                peekValue = peek(&s); // set the peek value incase you need to redo
                int arrayNumber = peekValue % 100;
                int playerNumber = (peekValue - arrayNumber) / 100;

                int returnedData = pop(&s);
                //pop(&s);
                playersShots[arrayNumber] = 300 + arrayNumber;

                displayGrid2(&s, peekValue);
                break;
            case 3: // Redo = peek then push (add)
                if ( peekValue == 0 ) {
                    printf("Connect 4 message Sorry nothing to redo");
                }
                push(&s, peekValue);
                displayGrid2(&s, 0);

                break;
        }
    } while (choice != 4); // 4 = quit

    return 0;
}