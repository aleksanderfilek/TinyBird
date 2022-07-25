#include"Button.h"
#include"../Graphics/Spritebatch.h"

#include<stdlib.h>

Button* ButtonCreate(Int2 position, Int2 size)
{
    Button* button = (Button*)malloc(sizeof(Button));

    button->position = position;
    button->size = size;
    button->collider = (BoxCollision2D){ &button->position, &button->size };
    button->text = NULL;
    button->background = NULL;

    button->clickEvent = EventCreate();

    return button;
}

void ButtonDestroy(Button* button)
{
    EventDestroy(button->clickEvent);
    free(button);
}

void ButtonUpdate(Button* button, Int2 mousePosition)
{
    if(PointBoxIntersection(mousePosition, button->collider))
    {
        EventInvoke(button->clickEvent, NULL, NULL, 0);
    }
}

void ButtonDraw(Button* button, Spritebatch* spritebatch)
{
    if(button->text)
    {
        SpritebatchRenderText(spritebatch, button->font, button->text, button->position, button->scale);
    }
}

void ButtonClickSet(Button* button, EventFunction function)
{
    EventAdd(button->clickEvent, function);
}

void ButtonTextSet(Button* button, const char* text, Font* font, float scale)
{
    button->font = font;
    button->text = text;
    button->scale = scale;
}

void ButtonBackgroundSet(Button* button, Texture* texture)
{
    button->background = texture;
}