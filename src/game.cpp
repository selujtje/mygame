#include "game.h"
#include <irrlicht.h>
#include <irrXML.h>
#include "RealisticWater.h"
using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

Game::Game(){
irr::SIrrlichtCreationParameters cfg_settings;
}

bool Game::init(){
    gui.XresField=0;
gui.YresField=0;
crate_mesh =0;//should get rid of this bitch

    //create a nulldevice and the xml reader
    LoadSettings();


    //set the eventreceiver
    cfg_settings.EventReceiver=this;
    playing =false;
    //create the device
    device = createDeviceEx(cfg_settings);
    if (device == 0)return 1; // could not create selected driver.

    //settings have been loaded, lets start with creating some pointers
    filesystem = device->getFileSystem();
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    env = device->getGUIEnvironment();

    //some standard stuffs
    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
 //   driver->setFog(video::SColor(0,138,125,81), video::EFT_FOG_LINEAR, 550, 20000, .003f, true, false);
//    driver->setTextureCreationFlag(video::EMF_FOG_ENABLE, true);
	env->getSkin()->setFont(env->getFont("textures/font/benderfont.xml"));
    mainmenu();

};





bool Game::singleplayer(){
    playing =true;
    SetGUIActive(0);//remove any active gui just in case

    //set the keymap
    SKeyMap keyMap[10];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_W;

	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;

	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_A;

	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;

	keyMap[8].Action = EKA_JUMP_UP;
	keyMap[8].KeyCode = KEY_SPACE;

	keyMap[9].Action = EKA_CROUCH;
	keyMap[9].KeyCode = KEY_KEY_C;

    //create a camera
    camera = smgr->addCameraSceneNodeFPS(0,100.0f,1.2f,-1, keyMap,10, false, 20.1f);
	camera->setPosition(core::vector3df(2700,2000,2600));
	camera->setTarget(core::vector3df(2397*2,343*2,2700*2));
	camera->setFarValue(42000.0f);
    smgr->setAmbientLight(video::SColorf(0.5f,0.5f,0.5f,0.1f));

    loadresources();

    u32 then = device->getTimer()->getTime();
    float oxygenleft = 1.f;float msperoxygentank = 50000.f;oxygendecreasefactor=1.f;u32 lastoxygenrefill;

    //RealisticWaterSceneNode*	water =new RealisticWaterSceneNode(smgr, 384,384,driver->getTexture("textures/waterbump.png"),dimension2du(512, 512), smgr->getRootSceneNode(), 666);

    bool do_once =true;

	while(device->run())
	if (device->isWindowActive())
	{
	    if(do_once){
            lastoxygenrefill = device->getTimer()->getTime();
            createeventtimer();
            loadgame();
            do_once=false;
	    }
        updateeventtimer();


        now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;
        oxygenleft=1.f-((device->getTimer()->getTime()-lastoxygenrefill)/msperoxygentank)*oxygendecreasefactor;

		driver->beginScene(true, true, 0 );
		smgr->drawAll();
		env->drawAll();
		driver->endScene();



        if(oxygenleft==0){
        IGUIImage* gameoverbg= env->addImage(core::rect<s32>(0,0, cfg_settings.WindowSize.Width, cfg_settings.WindowSize.Height));
        gameoverbg->setImage(driver->getTexture("textures/gameover_720.png"));
        }
        //update the oxygenbar
        oxygenBar->setVisible(false);
        oxygenBar = env->addImage(rect<int>(cfg_settings.WindowSize.Width-32,cfg_settings.WindowSize.Height-cfg_settings.WindowSize.Height*oxygenleft, cfg_settings.WindowSize.Width-12,cfg_settings.WindowSize.Height-11));
        oxygenBar->setImage(driver->getTexture("textures/bars/oxygenbar_bar.png"));
        oxygenBar->setUseAlphaChannel(true);

        //rotate node with 120degree/s
        node->setRotation(core::vector3df(0,(now/12) % 360 ,0));

        //create a ray from the center of the screen
		core::line3d<f32> ray;
		ray.start = camera->getPosition();
		ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 10000.0f;


		core::triangle3df hitTriangle;		// Used to show with triangle has been hit
        scene::ISceneNode * selectedSceneNode =
			collMan->getSceneNodeAndCollisionPointFromRay(
					ray,
					intersection, // This will be the position of the collision
					hitTriangle, // This will be the triangle hit in the collision
					IDFlag_IsPickable, //only select selectable items
					0); // Check the entire scene

		// If the ray hit anything, move the billboard to the collision position
		// and draw the triangle that was hit.
        bill->setPosition(intersection);
        xloc=((intersection.X/100)+0.5);zloc=((intersection.Z/100)+0.5);yloc=((intersection.Y/100)+0.5);
        node->setPosition(core::vector3df(xloc*100,yloc*100,zloc*100));

		//////PICKUPRAY
        core::line3d<f32> pickupray;
		pickupray.start = camera->getPosition();
		pickupray.end = core::vector3df(camera->getPosition().X,camera->getPosition().Y-500,camera->getPosition().Z);

        scene::ISceneNode * pickupSceneNode =
			collMan->getSceneNodeAndCollisionPointFromRay(
					pickupray,
                    pickupintersection, // This will be the position of the collision
					hitTriangle, // This will be the triangle hit in the collision
					IDFlag_IsPickable | IDFlag_IsHighlightable, //only select pickable items
					0); // Check the entire scene

		// If the ray hits something we will pick it up
        if(pickupSceneNode){
            if((pickupSceneNode->getID() & IDFlag_IsHighlightable) == IDFlag_IsHighlightable){

                                highlightedSceneNode = pickupSceneNode;

                                // Highlighting in this case means turning lighting OFF for this node,
                                // which means that it will be drawn with full brightness.
                                dropElement(highlightedSceneNode);
                lastoxygenrefill=now;
            }
        }
   //
		// display frames per second in window title
		int fps = driver->getFPS();
		if (lastFPS != fps)
		{
			core::stringw str = L"Game - FPS:";
			str += fps;
            savegame();
			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}
	}

	device->drop();

	return 0;

}


