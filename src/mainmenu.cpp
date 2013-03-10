#include "game.h"

#include <irrlicht.h>
#include <irrXML.h>

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

bool Game::mainmenu(){
    IArchiveLoader* archiveloaderpointer;
//    IFileArchive* createsavefile = archiveloaderpointer->createArchive("./fail.gsv");
    SetGUIActive(0);
    device->setResizable(false);
    device->setWindowCaption(L"Game - main menu");

    // create a background and make it fit
        ITexture* tex;
        tex = driver->getTexture("textures/spacerocketgames_menu_720.png");
        menubackground = env->addImage(core::rect<s32>(0,0, cfg_settings.WindowSize.Width, cfg_settings.WindowSize.Height));
        printf("width:%i ,height:%i \n",cfg_settings.WindowSize.Width,cfg_settings.WindowSize.Height);
        menubackground->setImage(tex);
        menubackground->setScaleImage(true);

    //create the mainmenu
    SetGUIActive(1);

    //and run
    while(device->run())
    {
        driver->beginScene(true, true, 0);
        env->drawAll();
        driver->endScene();
    }
}

