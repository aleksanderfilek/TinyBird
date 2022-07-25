#ifndef BUTTON_H_
#define BUTTON_H_

#include"../Defaults.h"
#include"../Math.h"
#include"../Event.h"
#include"../Physics.h"

STRUCT(Texture);
STRUCT(Spritebatch);
STRUCT(Font);

typedef struct Button
{
    Int2 position;
    Int2 size;
    BoxCollision2D collider;

    Font* font;
    const char* text;
    float scale;
    Texture* background;

    Event* clickEvent;
} Button;

Button* ButtonCreate(Int2 position, Int2 size);
void ButtonDestroy(Button* button);
void ButtonUpdate(Button* button, Int2 mousePosition);
void ButtonDraw(Button* button, Spritebatch* spritebatch);
void ButtonClickSet(Button* button, EventFunction function);
void ButtonTextSet(Button* button, const char* text, Font* font, float scale);
void ButtonBackgroundSet(Button* button, Texture* texture);

#endif