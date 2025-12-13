#define SDL_MAIN_HANDLED

#include "GameManager.h"

int main(int argc, char** argv)
{
	return GameManager::instance()->run(argc, argv);
}