#include "menu.h"

void selecteNextEntry(struct menu *menu)
{
  do
  {
    menu->selectedEntryIndex = (menu->selectedEntryIndex + 1) % menu->length;
  } while (menu->entries[menu->selectedEntryIndex].selectable == 0);
}

void selectPreviousEntry(struct menu *menu)
{
  do
  {
    menu->selectedEntryIndex = menu->selectedEntryIndex == 0 ? (menu->length - 1) : (menu->selectedEntryIndex - 1);
  } while (menu->entries[menu->selectedEntryIndex].selectable == 0);
}

void handleMenuEvents(struct menu *menu, struct game *game)
{
  switch (game->event.type)
  {
  case SDL_KEYDOWN:
    if (game->inMenuKeyPressed == SDL_FALSE)
    {
      switch (game->event.key.keysym.sym)
      {
      case SDLK_DOWN:
        if (menu->orientation == VERTICAL)
          selecteNextEntry(menu);
        break;
      case SDLK_UP:
        if (menu->orientation == VERTICAL)
          selectPreviousEntry(menu);
        break;
      case SDLK_RIGHT:
        if (menu->orientation == HORIZONTAL)
          selecteNextEntry(menu);
        break;
      case SDLK_LEFT:
        if (menu->orientation == HORIZONTAL)
          selectPreviousEntry(menu);
        break;
      case SDLK_RETURN:
        game->state = menu->entries[menu->selectedEntryIndex].destinationState;
        break;
      default:
        break;
      }
      game->inMenuKeyPressed = SDL_TRUE;
    }
    break;
  case SDL_KEYUP:
    game->inMenuKeyPressed = SDL_FALSE;
    break;
  default:
    break;
  }
}

void drawMenu(struct game *game, struct menu menu)
{
  SDL_Color red = {255, 0, 0, 1};
  for (int i = 0; i < menu.length; i++)
  {
    SDL_Surface *surface = TTF_RenderText_Solid(game->font,
                                                menu.entries[i].label, menu.selectedEntryIndex == i ? red : menu.entries[i].fontColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    int textW = 0;
    int textH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
    SDL_Rect dstrect = {menu.entries[i].position.x, menu.entries[i].position.y, textW, textH};
    SDL_RenderCopy(game->renderer, texture, NULL, &dstrect);
  }
}
