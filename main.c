#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"

#include "images/mouth.h"
#include "images/cookie.h"
#include "images/start.h"
#include "images/win.h"
#include "images/end.h"
#include "images/cake.h"

/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.

/* enum gba_state
{
  START,
  PLAY,
  WIN,
  LOSE,
} STATE; */

Mouth b;
Cookie c;
Cookie c2;
Cake d;
int score;

/* The Game Code */
int main(void)
{
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //

  REG_DISPCNT = MODE3 | BG2_ENABLE;
  videoBuffer[1208] = 0x7fff;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  gba_state state = START;

  while (1)
  {
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw
    waitForVBlank();

    switch (state)
    {
    case START:
      drawFullScreenImageDMA(start);
      if (KEY_DOWN(BUTTON_START, currentButtons))
      {
        fillScreenDMA(BLACK);
        state = PLAY;
      }
      break;
    case PLAY:
      gameStart(&state);
      break;
    case WIN:
      drawFullScreenImageDMA(win);
      char buffer[500];
      sprintf(buffer, "Score:%d", score);
      drawRectDMA(150, 180, 50, 20, WHITE);
      drawString(150, 180, buffer, RED);      
      if (KEY_DOWN(BUTTON_SELECT, currentButtons))
      {
        state = START;
      }
      break;
    case LOSE:
      drawFullScreenImageDMA(end);
      if (KEY_DOWN(BUTTON_SELECT, currentButtons))
      {
        state = START;
      }
      break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(previousButtons); // You can remove this once previousButtons is used
  return 0;
}

Mouth setMouth(void)
{ // make mouth and draw
  Mouth b;
  b.row = 99;
  b.col = 118;
  drawImageDMA(b.row, b.col, 25, 25, mouth);
  return b;
}

Cookie setCookie(int row, int col)
{ // make cookie and draw
  Cookie c;
  c.row = row;
  c.col = col;
  drawImageDMA(c.row, c.col, 25, 25, cookie);
  return c;
}

Cake setCake(void)
{ // make cake and draw
  Cake d;
  d.row = 90;
  d.col = 170;
  drawImageDMA(90, 170, 25, 25, cake);
  return d;
}

/* Check if mouth collide/touch cookie or not,
  if yes then increase score */
void Collide(int row, int col, int row2, int col2, int width, int height)
{
  // mouth and cookie touch (mouth and cookie have same dim)
  // undraw cookie
  // score++

  // c.row = row;
  // c.col = col;
  // b.row = row2;
  // b.col = col2;


  if (row < row2 + height && row + height > row2 &&
      col < col2 + width && col + width > col2)
  {

    // waitForVBlank();
    drawRectDMA(row, col, 25, 25, BLACK);
    waitForVBlank();
    //score++

    if (row == c.row && col == c.col) {
      c.row = -100;
      c.col = -100;
      score++;
      char buffer[500];
      sprintf(buffer, "Score:%d", score);
      drawRectDMA(150, 180, 50, 20, WHITE);
      drawString(150, 180, buffer, RED);
    } else if (row == c2.row && col == c2.col) {
      c2.row = -100;
      c2.col = -100;
      score++;
      char buffer[500];
      sprintf(buffer, "Score:%d", score);
      drawRectDMA(150, 180, 50, 20, WHITE);
      drawString(150, 180, buffer, RED);
    }
  }
}

/* Check if mouth collide/touch with cake, if yes then you lose */
void collideLose(int row, int col, int row2, int col2, int width, int height, gba_state *state)
{

  if (row < row2 + height && row + height > row2 &&
      col < col2 + width && col + width > col2)
  {

    *state = LOSE;
  }
}

/* code for when the game start */
void gameStart(gba_state *state)
{
  b = setMouth();
  c = setCookie(50, 50);
  c2 = setCookie(90, 45);
  d = setCake();
  u32 current;
  score = 0;
  char buffer[500];
  sprintf(buffer, "Score:%d", score);
  drawRectDMA(150, 180, 50, 20, WHITE);
  drawString(150, 180, buffer, RED);
  while (*state == PLAY)
  {
    current = BUTTONS;
    if (KEY_DOWN(BUTTON_RIGHT, current))
    { // move right
      waitForVBlank();
      // undrawImageDMA(b.row, b.col, 15, 15, garbage);
      drawRectDMA(b.row, b.col, 25, 25, BLACK);
      if (b.col < 190 && b.col > 2)
      {
        b.col++;
      }
      else if (b.col == 190)
      {
        b.col = b.col - 3;
      }
      drawImageDMA(b.row, b.col, 25, 25, mouth);
    }

    if (KEY_DOWN(BUTTON_LEFT, current))
    { // move left
      waitForVBlank();
      // undrawImageDMA(b.row, b.col, 15, 15, garbage);
      drawRectDMA(b.row, b.col, 25, 25, BLACK);
      if (b.col < 190 && b.col > 2)
      {
        b.col--;
      }
      else if (b.col == 2)
      {
        b.col = b.col + 3;
      }
      drawImageDMA(b.row, b.col, 25, 25, mouth);
    }

    if (KEY_DOWN(BUTTON_UP, current))
    { // move up
      waitForVBlank();
      // undrawImageDMA(b.row, b.col, 15, 15, garbage);
      drawRectDMA(b.row, b.col, 25, 25, BLACK);
      if (b.row < 125 && b.row > 2)
      {
        b.row--;
      }
      else if (b.row == 2)
      {
        b.row = b.row + 2;
      }
      drawImageDMA(b.row, b.col, 25, 25, mouth);
    }

    if (KEY_DOWN(BUTTON_DOWN, current))
    { // move down
      waitForVBlank();
      // undrawImageDMA(b.row, b.col, 15, 15, garbage);
      drawRectDMA(b.row, b.col, 25, 25, BLACK);
      if (b.row < 125 && b.row > 2)
      {
        b.row++;
      }
      else if (b.row == 125)
      {
        b.row = b.row - 2;
      }
      drawImageDMA(b.row, b.col, 25, 25, mouth);
    }

    Collide(c.row, c.col, b.row, b.col, 25, 25);
    Collide(c2.row, c2.col, b.row, b.col, 25, 25);

    collideLose(d.row, d.col, b.row, b.col, 25, 25, state);

    if (KEY_DOWN(BUTTON_SELECT, current)) //reset to start screen if press delete
    { // reset
      *state = START;
    }

    if (score == 2) { //win if score = 2
      *state = WIN;
    }
  }
}
