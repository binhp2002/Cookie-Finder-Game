#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

// TODO: Create any necessary structs

/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/

typedef enum {
  START,
  PLAY,
  WIN,
  LOSE,
} gba_state;

typedef struct mouth {
    int row;
    int col;
} Mouth; 

typedef struct cookie {
    int row;
    int col;
} Cookie; 

typedef struct cake {
    int row;
    int col;
} Cake; 

Mouth setmouth(void);
Cookie setCookie(int row, int col);
Cake setCake(void);
void gameStart(gba_state *state);
void Collide (int row, int col, int row2, int col2, int width, int height);

#endif
