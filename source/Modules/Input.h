#ifndef TB_INPUT_H_
#define TB_INPUT_H_

#include"InputKeys.h"
#include"../Math.h"
#include"../ThirdParty/SDL2/SDL.h"

#include<stdint.h>
#include<stdbool.h>

typedef struct Input
{
    int keyboardStateNumber;
    const uint8_t *currentKeyboardState;
    uint8_t *previousKeyboardState;
    uint32_t currentMouseState;
    uint32_t previousMouseState;
    Int2 currentMousePosition;
    Int2 previousMousePosition;
    bool relativeMode;
} Input;

Input* InputCreate();
void InputUpdate(void* ptr, double elapsedTime);
void InputDestroy(void* ptr);

bool InputKeyPressed(Input* input, EKeyCode key);
bool InputKeyDown(Input* input, EKeyCode key);
bool InputKeyUp(Input* input, EKeyCode key);
bool InputMouseButtonPressed(Input* input, EKeyCode button);
bool InputMouseButtonDown(Input* input, EMouse button);
bool InputMouseButtonUp(Input* input, EMouse button);
Int2 InputGetMousePosition(Input* input);
void InputSetMousePosition(Input* input, Int2 position);
uint8_t InputGetMouseState(Input* input, EMouse button);
Int2 InputGetMouseDeltaPosition(Input* input);
void InputSetRelativeMode(Input* input, bool enable);

#endif