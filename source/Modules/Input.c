#include"Input.h"

#include<stdio.h>
#include<stdlib.h>

Input* InputCreate()
{
    Input* input = (Input*)calloc(1, sizeof(Input));

    input->currentKeyboardState = SDL_GetKeyboardState(&input->keyboardStateNumber);

    input->previousKeyboardState = (uint8_t*)calloc(input->keyboardStateNumber, sizeof(uint8_t));

    #ifdef DEBUG
    printf("[Input] Created\n");
    #endif

    return input;
}

void InputUpdate(void* ptr, double elapsedTime)
{
    Input* input = (Input*)ptr;

    //update mouse
    input->previousMouseState = input->currentMouseState;
    input->previousMousePosition = input->currentMousePosition;

    if(input->relativeMode == false)
    {
        input->currentMouseState = SDL_GetMouseState(&input->currentMousePosition.x, &input->currentMousePosition.y);
    }
    else
    {
        input->currentMouseState = SDL_GetRelativeMouseState(&input->currentMousePosition.x, &input->currentMousePosition.y);
    }

    //update keyboard
    SDL_memcpy(input->previousKeyboardState, input->currentKeyboardState, input->keyboardStateNumber * sizeof(uint8_t));
}

void InputDestroy(void* ptr)
{
    Input* input = (Input*)ptr;

    free(input->previousKeyboardState);
    free(input);

    #ifdef DEBUG
    printf("[Input] Destroyed\n");
    #endif
}

bool InputKeyPressed(Input* input, EKeyCode key)
{ 
    return input->currentKeyboardState[key] && input->previousKeyboardState[key]; 
}

bool InputKeyDown(Input* input, EKeyCode key)
{
    return input->currentKeyboardState[key] && !input->previousKeyboardState[key]; 
}

bool InputKeyUp(Input* input, EKeyCode key)
{
    return !input->currentKeyboardState[key] && input->previousKeyboardState[key]; 
}

void InputSetMousePosition(Input* input, Int2 position)
{
    input->currentMousePosition = position;
}

bool InputMouseButtonPressed(Input* input, EKeyCode button)
{
    return input->currentMouseState&SDL_BUTTON(button) && input->previousMouseState&SDL_BUTTON(button); 
}

bool InputMouseButtonDown(Input* input, EMouse button)
{
    return input->currentMouseState&SDL_BUTTON(button) && !input->previousMouseState&SDL_BUTTON(button); 
}

bool InputMouseButtonUp(Input* input, EMouse button)
{
    return !input->currentMouseState&SDL_BUTTON(button) && input->previousMouseState&SDL_BUTTON(button); 
}

Int2 InputGetMousePosition(Input* input) 
{
    return input->currentMousePosition;
}  

uint8_t InputGetMouseState(Input* input, EMouse button)
{
    uint8_t state = MOUSESTATE_NONE;
    if(InputMouseButtonDown(input, button)) state = MOUSESTATE_DOWN;
    else if(InputMouseButtonPressed(input, button)) state = MOUSESTATE_PRESSED;
    else if(InputMouseButtonUp(input, button)) state = MOUSESTATE_UP;

    return state;
}

Int2 InputGetMouseDeltaPosition(Input* input)
{
    if(input->relativeMode == false)
    {
        return (Int2){ input->currentMousePosition.x - input->previousMousePosition.x,
            input->currentMousePosition.y - input->previousMousePosition.y }; 
    }

    return input->currentMousePosition;
}

void InputSetRelativeMode(Input* input, bool enable)
{
    input->relativeMode = enable;
    SDL_SetRelativeMouseMode((enable == true)? SDL_TRUE : SDL_FALSE);
}