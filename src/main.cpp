/** Game... damn need a better projectname

a quite serious attempt to make a good game template for Irrlicht
**/

#include <string>
#include <irrlicht.h>
#include <irrXML.h>
#include "game.h"
#include <iostream>
#define dropElement(x)	if (x) { x->remove(); x = 0; }

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

int main()
{


    //create the game class with the params and run the mainmenu
    Game Game;
Game.init();
}
