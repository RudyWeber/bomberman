#ifndef __MENU_H__
#define __MENU_H__

#include "game.h"

#define MAX_ENTRIES 5

enum orientation
{
  HORIZONTAL,
  VERTICAL
};

struct menuEntry
{
  char selectable;
  enum states destinationState;
  char *label;
  SDL_Point position;
  char *fontFace;
  unsigned short fontSize;
  SDL_Color fontColor;
};

struct menu
{
  enum orientation orientation;
  unsigned short length;
  unsigned short selectedEntryIndex;
  struct menuEntry entries[MAX_ENTRIES];
};

static struct menu MainMenu = {
    .orientation = VERTICAL,
    .length = 4,
    .selectedEntryIndex = 1,
    .entries = {
        {.selectable = 0,
         .fontFace = "/Library/Fonts/Arial.ttf",
         .fontSize = 25,
         .fontColor = {0, 0, 0, 0},
         .label = "Bomberman",
         .position = {.x = 200, .y = 50}},
        {.selectable = 1,
         .fontFace = "/Library/Fonts/Arial.ttf",
         .fontSize = 25,
         .fontColor = {0, 0, 0, 0},
         .label = "Host Game",
         .destinationState = HOST_GAME,
         .position = {.x = 100, .y = 100}},
        {.selectable = 1,
         .fontFace = "/Library/Fonts/Arial.ttf",
         .fontSize = 25,
         .fontColor = {0, 0, 0, 0},
         .label = "Join Game",
         .destinationState = JOIN_GAME,
         .position = {.x = 100, .y = 200}},
        {.selectable = 1,
         .fontFace = "/Library/Fonts/Arial.ttf",
         .fontSize = 25,
         .fontColor = {0, 0, 0, 0},
         .label = "Quit",
         .destinationState = CONFIRM_EXIT,
         .position = {.x = 100, .y = 300}}}};

static struct menu ConfirmExitMenu = {
    .orientation = HORIZONTAL,
    .length = 3,
    .selectedEntryIndex = 2,
    .entries = {
        {.selectable = 0,
         .fontFace = "/Library/Fonts/Arial.ttf",
         .fontSize = 25,
         .fontColor = {0, 0, 0, 0},
         .label = "Do you want to quit?",
         .position = {.x = 200, .y = 50}},
        {.selectable = 1,
         .fontFace = "/Library/Fonts/Arial.ttf",
         .fontSize = 25,
         .fontColor = {0, 0, 0, 0},
         .label = "Yes",
         .destinationState = EXIT,
         .position = {.x = 100, .y = 100}},
        {.selectable = 1,
         .fontFace = "/Library/Fonts/Arial.ttf",
         .fontSize = 25,
         .fontColor = {0, 0, 0, 0},
         .label = "No",
         .destinationState = MAIN_MENU,
         .position = {.x = 300, .y = 100}}}};

void handleMenuEvents(struct menu *, struct game *);
void drawMenu(struct menu, struct game *);

#endif