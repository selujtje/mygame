#include "game.h"

#include <irrlicht.h>
#include <irrXML.h>

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;


bool Game::settingsmenu(){
    playing=false;
    //still quite A LOT to do here ;)
    //device->setResizable(false);
    device->setWindowCaption(L"Game - main menu");
        ITexture* tex;
        tex = driver->getTexture("textures/settingsmenubg.png");


        // Give to addImage() the XY coords of 2 points :
        menubackground = env->addImage(core::rect<s32>(0,0, cfg_settings.WindowSize.Width, cfg_settings.WindowSize.Height));
        menubackground->setImage(tex);
        menubackground->setScaleImage(true);


    SetGUIActive(2);

   while(device && device->run())
    {

        driver->beginScene(true, true, 0);
        //smgr->drawAll();
        env->drawAll();
        driver->endScene();
    }
}

