#include "game.h"

#include <irrlicht.h>
#include <irrXML.h>
//#include

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

void Game::createProgressBar() {

        ITexture* tex;
        tex = driver->getTexture("textures/spacerocketgames_splash_720.png");


        // Give to addImage() the XY coords of 2 points :
        background = env->addImage(core::rect<s32>(0,0, cfg_settings.WindowSize.Width, cfg_settings.WindowSize.Height));
        background->setImage(tex);
        background->setScaleImage(true);


        progBar = env->addImage(rect<int>(0, (cfg_settings.WindowSize.Height-68), cfg_settings.WindowSize.Width, (cfg_settings.WindowSize.Height-20)));
        progBar->setImage(driver->getTexture("textures/bars/progressbar_bar_720.png"));
        progBox = env->addImage(rect<int>(0, (cfg_settings.WindowSize.Height-68), cfg_settings.WindowSize.Width, (cfg_settings.WindowSize.Height-20)));
        progBox->setImage(driver->getTexture("textures/bars/progressbar_box_720.png"));
        progBox->setUseAlphaChannel(true);
        progBar->setUseAlphaChannel(true);
        progText = env->addStaticText(L"loading...", rect<int>((cfg_settings.WindowSize.Width/30), (cfg_settings.WindowSize.Height)-90, (cfg_settings.WindowSize.Width/2)+100, (cfg_settings.WindowSize.Height)-60), false, false);
        progText->enableOverrideColor(true);
        progText->setOverrideColor(SColor(255,95,209,4));

     }

void Game::displayProgressBar(bool val) {
    progBar->setVisible(val);
    progBox->setVisible(val);
    progText->setVisible(val);
    background->setVisible(val);
}

void Game::updateProgressBar(int newValue, stringw msg) {
    progBar->setVisible(false);
    progBar = env->addImage(rect<int>(0, (cfg_settings.WindowSize.Height-68), (cfg_settings.WindowSize.Width*newValue)/100, (cfg_settings.WindowSize.Height-20)));
    progBar->setImage(driver->getTexture("textures/bars/progressbar_bar_720.png"));
        progBar->setUseAlphaChannel(true);
    progText->setText(msg.c_str());
    driver->beginScene(true, true, SColor(0, 0, 0, 0));
    env->drawAll();
    driver->endScene();

    }


bool Game::loadresources(){

        device->getCursorControl()->setVisible(false);
        createProgressBar();
        updateProgressBar(4,"loading heightmap...");
        //create the terrain
        collisionscenenode =0;
        scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
		"textures/medium-heightmap.png",
		collisionscenenode,					    // parent node
		IDFlag_IsPickable,					    // node id
		core::vector3df(0.f, 0.f, 0.f),		    // position
		core::vector3df(0.f, 0.f, 0.f),		    // rotation
		core::vector3df(60.f, 60.f, 60.f),  	// scale
		video::SColor ( 255, 255, 255, 255 ),	// vertexColor
		5,					// maxLOD
		scene::ETPS_17,		// patchSize
		8					// smoothFactor
		);
		updateProgressBar(40,"loading textures...");
        terrain->setMaterialFlag(video::EMF_LIGHTING, true);
        terrain->setMaterialTexture(0,driver->getTexture("textures/Grass_tiled.jpg"));
        terrain->getMaterial(0).getTextureMatrix(0).setTextureScaleCenter(10,10);
        terrain->scaleTexture(1.0f, 20.0f);
       // terrain->setMaterialFlag(video::EMF_FOG_ENABLE, true);
        //terrain->setDebugDataVisible ( true );
        updateProgressBar(50, "loading lava...");
//        IGeometryCreator* planemesh = createPlaneMesh(dimension2d(400,400),dimension2d(40,40),driver->getTexture("textures/spacerocketgames_splash_720.png"),dimension2df(40,40));

        updateProgressBar(60, "setting up physics...");
        // create triangle selector for the terrain
        selector = smgr->createTerrainTriangleSelector(terrain, 0);
        metaselector = smgr->createMetaTriangleSelector();
        metaselector->addTriangleSelector(selector);
        //scene::IMetaTriangleSelector* global_triangleselector = smgr->createMetaTriangleSelector();
        //global_triangleselector->addTriangleSelector(selector);
        terrain->setTriangleSelector(metaselector);

        // create collision response animator and attach it to the camera
        anim1 = smgr->createCollisionResponseAnimator(
		metaselector, camera, core::vector3df(30,180,30),
		core::vector3df(0,-9.81,0),
		core::vector3df(0,0,0),0.1f);
	selector->drop();
	camera->addAnimator(anim1);
	anim1->drop();
    updateProgressBar(75,"loading skybox...");
	// create skybox
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);
	scene::ISceneNode* skybox=smgr->addSkyBoxSceneNode(
		driver->getTexture("textures/irrlicht2_up.jpg"),
		driver->getTexture("textures/irrlicht2_dn.jpg"),
		driver->getTexture("textures/irrlicht2_lf.jpg"),
		driver->getTexture("textures/irrlicht2_rt.jpg"),
		driver->getTexture("textures/irrlicht2_ft.jpg"),
		driver->getTexture("textures/irrlicht2_bk.jpg"));
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

    updateProgressBar(90, "Loading almost complete...");
	// Add the billboard.
	bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	bill->setMaterialTexture(0, driver->getTexture("textures/particle.bmp"));
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
	bill->setID(ID_IsNotPickable); // This ensures that we don't accidentally ray-pick it
    crate_mesh = smgr->getMesh("models/oxygentank.dae");
    printf("cratemesh loaded");
    node = 0;
    node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("models/oxygentank.dae"), 0, 1 | 2);
    node->setScale(core::vector3df(50,50,50)); // Put its feet on the floor.
    node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setMaterialTexture(0, driver->getTexture("textures/oxygen_texture.png"));
	//node->setMaterialTexture(1, driver->getTexture("textures/shade.png"));
	//node->setMaterialType(video::EMT_DETAIL_MAP);
    node->setMaterialFlag(video::EMF_WIREFRAME,true);

	collMan = smgr->getSceneCollisionManager();
	//declare some variables
    lastFPS=-1;


    //load the oxygenbar
    updateProgressBar(95, "Loading bars...");
    oxygenBar = env->addImage(rect<int>(cfg_settings.WindowSize.Width-32,0 , cfg_settings.WindowSize.Width-8,cfg_settings.WindowSize.Height));
    oxygenBar->setImage(driver->getTexture("textures/bars/oxygenbar_bar.png"));
    oxygenBar->setUseAlphaChannel(true);
    oxygenBar->setColor(SColor(120,255,255,255));
    oxygenBox = env->addImage(rect<int>(cfg_settings.WindowSize.Width-32,0 , cfg_settings.WindowSize.Width-8,cfg_settings.WindowSize.Height));
    oxygenBox->setImage(driver->getTexture("textures/bars/oxygenbar_box.png"));
    oxygenBox->setUseAlphaChannel(true);
    oxygenBar->setColor(SColor(50,255,255,255));
    oxygenBox->setVisible(false);
    oxygenBar->setVisible(false);
    inventoryBox = env->addImage(rect<int>(0,cfg_settings.WindowSize.Height-53, 413,cfg_settings.WindowSize.Height));
    inventoryBox->setImage(driver->getTexture("textures/ui/inventory_bar.png"));
    inventoryBox->setUseAlphaChannel(true);
    inventoryBox->setVisible(false);
    if(inventoryBox)//set up the inventory
    {
//        inventoryselected = env->addImage(rect<int>(6*49,cfg_settings.WindowSize.Height-53, 7*49,cfg_settings.WindowSize.Height));
    //    inventoryselected->setImage(driver->getTexture("textures/ui/inventory/selected.png"));
        inventory1 = env->addImage(rect<int>(0*49,cfg_settings.WindowSize.Height-53, 1*49,cfg_settings.WindowSize.Height));
        inventory2 = env->addImage(rect<int>(1*49,cfg_settings.WindowSize.Height-53, 2*49,cfg_settings.WindowSize.Height));
        inventory3 = env->addImage(rect<int>(2*49,cfg_settings.WindowSize.Height-53, 3*49,cfg_settings.WindowSize.Height));
        inventory4 = env->addImage(rect<int>(3*49,cfg_settings.WindowSize.Height-53, 4*49,cfg_settings.WindowSize.Height));
        inventory5 = env->addImage(rect<int>(4*49,cfg_settings.WindowSize.Height-53, 5*49,cfg_settings.WindowSize.Height));
        inventory6 = env->addImage(rect<int>(5*49,cfg_settings.WindowSize.Height-53, 6*49,cfg_settings.WindowSize.Height));
        inventory7 = env->addImage(rect<int>(6*49,cfg_settings.WindowSize.Height-53, 7*49,cfg_settings.WindowSize.Height));

    }
  //  inventoryselected = env->addImage(rect<int>(6*49,cfg_settings.WindowSize.Height-53, 7*49,cfg_settings.WindowSize.Height));
//    inventoryselected->drop();

 //    inventoryselected = env->addImage(rect<int>(5*49,cfg_settings.WindowSize.Height-53, 6*49,cfg_settings.WindowSize.Height) );
 //    inventoryselected->setImage(driver->getTexture("textures/ui/inventory/selected.png"));
 //    inventoryselected->setUseAlphaChannel(true);
    inventory1->setImage(driver->getTexture("textures/ui/inventory/tree_sapling.png"));
    inventory1->setUseAlphaChannel(true);
    inventory6->setImage(driver->getTexture("textures/ui/inventory/tree_sapling.png"));
    inventory6->setUseAlphaChannel(true);
    updateProgressBar(100, "Loading Complete...");
    //splash screen
    oxygenBox->setVisible(true);
    oxygenBar->setVisible(true);
    inventoryBox->setVisible(true);

	scene::IBillboardSceneNode * bill1 = smgr->addBillboardSceneNode();
	bill1->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	bill1->setMaterialTexture(0, driver->getTexture("textures/particle.bmp"));
	bill1->setMaterialFlag(video::EMF_LIGHTING, false);
	bill1->setMaterialFlag(video::EMF_ZBUFFER, false);
	bill1->setSize(core::dimension2d<f32>(2000.0f, 2000.0f));
	bill1->setPosition(core::vector3df(0,20000,0));
    scene::ISceneNode* lightnode = smgr->addLightSceneNode(0, core::vector3df(0,20000,0),
                video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 8000.0f);
    int numberofsplashframes = 0;



    displayProgressBar(false);
}

bool Game::takescreenshot(){
                        // screenshot are taken without gamma!
    IImage* image = device->getVideoDriver()->createScreenShot();
    if (image)
    {
        device->getVideoDriver()->writeImageToFile(image, "screenshot.png", 100 );
        image->drop();
    }

}
