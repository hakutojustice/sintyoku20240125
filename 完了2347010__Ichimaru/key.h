#pragma once
#include "DxLib.h"

#define KeyKindMax 256

extern VOID KeyInit(VOID);
extern VOID KeyUpdate(VOID);
extern BOOL KeyDown(int KEY_INPUT_);
extern BOOL KeyClick(int KEY_INPUT_);
extern int  KeyPressFrame(int KEY_INPUT_);