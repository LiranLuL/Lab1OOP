#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "Cardatch.h"


int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Cardatch deck;
    deck.Console();
}

