#include "game.h"
using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

 int guiActive = 1;


int Game::GetGUIActive()
{
    return guiActive;
}

void Game::SetGUIActive( s32 command)
{
	bool inputState = false;

    buttonxlocstart = ((cfg_settings.WindowSize.Width/2)-(cfg_settings.WindowSize.Width/10)-50);
    buttonxlocend = ((cfg_settings.WindowSize.Width/2)+(cfg_settings.WindowSize.Width/10)+50);
    buttonylocspace = (cfg_settings.WindowSize.Height/7);


	switch ( command )
	{
		case 0: guiActive = 0; inputState = true;
            dropElement(gui.QuitButton);
            dropElement(gui.SettingsButton);
            dropElement(gui.SinglePlayerButton);
            dropElement(gui.XresField);
            dropElement(gui.YresField);
            break;//nothing
		case 1://main menu
            SetGUIActive(0);//make sure nothing is visible anymore
            guiActive = 1; inputState = false;

            gui.SinglePlayerButton = env->addButton(rect<s32>(buttonxlocstart,buttonylocspace*2,buttonxlocend,buttonylocspace*2 + 48), 0, GUI_ID_SINGLE_PLAYER_BUTTON, L"SinglePlayer");
            gui.SettingsButton = env->addButton(rect<s32>(buttonxlocstart,buttonylocspace*3,buttonxlocend,buttonylocspace*3 + 48), 0, GUI_ID_SETTINGS_BUTTON, L"Settings", L"Edit Settings");
            gui.QuitButton = env->addButton(rect<s32>(buttonxlocstart,buttonylocspace*4,buttonxlocend,buttonylocspace*4 + 48), 0, GUI_ID_QUIT_BUTTON, L"Quit", L"Exits Program");

            break;//end of main ui
		case 2:
            SetGUIActive(0);
            guiActive = 2; inputState = 0;
            gui.XresField = env->addSpinBox(stringw(cfg_settings.WindowSize.Width).c_str(),rect<s32>(
                                                                                    ((581.f/1920.f)*cfg_settings.WindowSize.Width),//x1
                                                                                    ((366.f/1080.f)*cfg_settings.WindowSize.Height),//y1
                                                                                    ((730.f/1920.f)*cfg_settings.WindowSize.Width),//x2
                                                                                    ((396.f/1080.f)*cfg_settings.WindowSize.Height)//y2
                                                                                    ),true);
            gui.XresField->setDecimalPlaces(0);
            gui.XresField->setRange(0,4096);

             gui.YresField = env->addSpinBox(stringw(cfg_settings.WindowSize.Height).c_str(),rect<s32>(
                                                                                    ((581.f/1920.f)*cfg_settings.WindowSize.Width),//x1
                                                                                    ((415.f/1080.f)*cfg_settings.WindowSize.Height),//y1
                                                                                    ((730.f/1920.f)*cfg_settings.WindowSize.Width),//x2
                                                                                    ((445.f/1080.f)*cfg_settings.WindowSize.Height)//y2
                                                                                    ),true);
            gui.YresField->setDecimalPlaces(0);
            gui.YresField->setRange(0,4096);
            gui.FullscreenCheckbox = env->addCheckBox(cfg_settings.Fullscreen, rect<s32>(
                                                                                    ((581.f/1920.f)*cfg_settings.WindowSize.Width),//x1
                                                                                    ((464.f/1080.f)*cfg_settings.WindowSize.Height),//y1
                                                                                    ((611.f/1920.f)*cfg_settings.WindowSize.Width),//x2
                                                                                    ((494.f/1080.f)*cfg_settings.WindowSize.Height)//y2
                                                                                       ),0,GUI_ID_FULLSCREEN_CHECKBOX,L"fullscreen" );
            gui.AntiAliasCheckbox = env->addCheckBox(cfg_settings.AntiAlias, rect<s32>(
                                                                                    ((581.f/1920.f)*cfg_settings.WindowSize.Width),//x1
                                                                                    ((513.f/1080.f)*cfg_settings.WindowSize.Height),//y1
                                                                                    ((611.f/1920.f)*cfg_settings.WindowSize.Width),//x2
                                                                                    ((543.f/1080.f)*cfg_settings.WindowSize.Height)//y2
                                                                                       ),0,GUI_ID_ANTIALIAS_CHECKBOX,L"anti alias" );





/*1920x1080
581 x366
673 x396*/


            break;//settings ui

	}

	if ( camera )
	{
		//camera->setInputReceiverEnabled ( inputState );
		device->getCursorControl()->setVisible( !inputState );
	}


}

void drawinventorybox()
{
   /* driver->draw2DImage(images, core::position2d<s32>(0,cfg_settings.WindowSize.Height),
                                core::rect<s32>(0,0,342,224), 0,
                                video::SColor(255,255,255,255), true);
}*/}
