
#include "game.h"

bool Game::OnEvent(const SEvent& event)
{

        if (event.EventType == EET_GUI_EVENT)
                {
                        s32 id = event.GUIEvent.Caller->getID();
                        IGUIEnvironment* env = device->getGUIEnvironment();

                        switch(event.GUIEvent.EventType)
                        {
                            case EGET_BUTTON_CLICKED:
                                switch(id)
                                {
                                case GUI_ID_QUIT_BUTTON:
                                        device->closeDevice();
                                        return false;

                                case GUI_ID_SINGLE_PLAYER_BUTTON:
                                        menubackground->setVisible(false);
                                        singleplayer();
                                        return true;
                                case GUI_ID_SETTINGS_BUTTON:
                                        settingsmenu();
                                        return true;
                                }
                        }
                }
	    if (event.EventType == EET_MOUSE_INPUT_EVENT && event.MouseInput.Event == EMIE_RMOUSE_LEFT_UP)
	    {
	        printf("\nleft mouse clicked\n");
	    }

        if (event.EventType == EET_MOUSE_INPUT_EVENT && event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP && playing)
	    {
            if(crate_mesh){
                node2 = smgr->addAnimatedMeshSceneNode(smgr->getMesh("models/crystal.dae"), 0, IDFlag_IsPickable | IDFlag_IsHighlightable);

                node2->setScale(core::vector3df(50,50,50)); // Put its feet on the floor.
                node2->setPosition(core::vector3df(xloc*100,intersection.Y,zloc*100));
                node2->setRotation(core::vector3df(0,(now/12) % 360 ,0));
                node2->setMaterialFlag(video::EMF_LIGHTING, false);
                if((now) % 2 ==1){
                node2->setMaterialTexture(0, driver->getTexture("textures/treetex.png"));
                }else{
                node2->setMaterialTexture(0, driver->getTexture("textures/mushroom/mushroom.png"));
                }
                selector = smgr->createTriangleSelector(node2);
                node2->setTriangleSelector(selector);
                selector->drop();
            }

	    }



		if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown && playing)
		{
			switch (event.KeyInput.Key)
			{
            case irr::KEY_KEY_G:
                  anim1->setGravity(core::vector3df(0,anim1->getGravity().Y != 0 ? 0 : -98.1,0));//switch between 0 and
                  device->setWindowCaption(L"Game - mai1n menu");
                //  if(collisionscenenode){collisionscenenode->setScale(core::vector3df(1,1,1));}
                return true;
            case irr::KEY_KEY_1:
                current_inventory_mesh = smgr->getMesh("models/plants.dae");
                node->setMesh(current_inventory_mesh);

                return true;
			case irr::KEY_F11:
                takescreenshot();
				return true;
			case irr::KEY_KEY_2:
                savegame();

				return true;
			case irr::KEY_KEY_3:
                smgr->loadScene("save1.irr");
				return true;
			default:
				break;
			}
		}

		//always
		if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown )
		{
			switch (event.KeyInput.Key)
			{
            case irr::KEY_ESCAPE:
              if(GetGUIActive()==2){
                  SaveSettings();
   if (device)
   {
      device->closeDevice();
      device->run();
      device->drop();
      device = 0;
   }
init();
              }else{
              device->closeDevice();
              }
                return true;
			default:
				break;
			}
		}


    return false;
};
