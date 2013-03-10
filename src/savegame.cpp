
#include "game.h"


bool Game::savegame(){
    array< scene::ISceneNode *> scenearray;
    smgr->getSceneNodesFromType(ESNT_ANIMATED_MESH,scenearray);
    io::IXMLWriter* writer = filesystem->createXMLWriter(L"savefile.sav");
    writer->writeXMLHeader();
    writer->writeElement(L"camera",true,L"x",stringw((float)camera->getPosition().X).c_str(),L"y",stringw((float)camera->getPosition().Y).c_str(),L"z",stringw((float)camera->getPosition().Z).c_str(),L"yrot",stringw((float)camera->getRotation().Y).c_str());
		writer->writeLineBreak();
    writer->writeElement(L"item", false);
    writer->writeLineBreak();
    for (u32 i=0; i < scenearray.size(); ++i)
    {
        scene::ISceneNode * nodetobesaved = scenearray[i];
		writer->writeElement(L"tree",true,L"x",stringw((float)nodetobesaved->getPosition().X).c_str(),L"y",stringw((float)nodetobesaved->getPosition().Y).c_str(),L"z",stringw((float)nodetobesaved->getPosition().Z).c_str(),L"yrot",stringw((float)nodetobesaved->getRotation().Y).c_str());
		writer->writeLineBreak();
    }
    writer->writeClosingTag(L"item");
    writer->drop();
}

bool Game::loadgame(){
     IXMLReader* xml = filesystem->createXMLReader("savefile.sav");
     if(!xml)return false;
     while(xml && xml->read())
   {
      if (core::stringw("camera") == xml->getNodeName())
      {
      camera->setPosition(core::vector3df(xml->getAttributeValueAsInt(L"x"),xml->getAttributeValueAsInt(L"y"),xml->getAttributeValueAsInt(L"z")));
      camera->setRotation(core::vector3df(0,xml->getAttributeValueAsInt(L"yrot"),0));
      }
      if (core::stringw("tree") == xml->getNodeName())
      {
                cfg_settings.WindowSize = core::dimension2d<u32>(xml->getAttributeValueAsInt(L"x"),xml->getAttributeValueAsInt(L"y"));
                node2 = smgr->addAnimatedMeshSceneNode(smgr->getMesh("models/tree_decidious.dae"), 0, IDFlag_IsPickable | IDFlag_IsHighlightable);
                node2->setScale(core::vector3df(50,50,50)); // Put its feet on the floor.
                node2->setPosition(core::vector3df(xml->getAttributeValueAsInt(L"x"),xml->getAttributeValueAsInt(L"y"),xml->getAttributeValueAsInt(L"z")));
                node2->setRotation(core::vector3df(0,xml->getAttributeValueAsInt(L"yrot"),0));
                node2->setMaterialFlag(video::EMF_LIGHTING, false);
                node2->setMaterialTexture(0, driver->getTexture("textures/treetex.png"));
                selector = smgr->createTriangleSelector(node2);
                node2->setTriangleSelector(selector);
                selector->drop();
                //node2->drop();

      }
   }


}
