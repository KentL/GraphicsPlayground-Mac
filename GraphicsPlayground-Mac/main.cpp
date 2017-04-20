// AS2-20170208.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Game.hpp"

int main(int argc, char *argv[])
{
    Game* game = Game::Inst();
    game->Init(argc, argv);
    game->Run();
}

