#include "game.h"
#include <irrlicht.h>
#include <irrXML.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;
int numberofcases = 3;
int currentcase = 1;
//array< scene::ISceneNode *> tempscenearray;
array< scene::ISceneNode *> tempscenearray;
void Game::createeventtimer(){
u32 timerstart = device->getTimer()->getTime();
 srand ( time(NULL) );
}

void Game::updateeventtimer(){
    //limit the events to MAXEVENTS per tick in order to maintain stable fps
tempscenearray.clear();
    int chancefactor = 1/driver->getFPS()*numberofcases;
    if(currentcase >= numberofcases )
    {
        currentcase=0;
    }
    else
    {
        currentcase++;
    }
    switch(currentcase)
    {
    case 1://growtrees
        smgr->getSceneNodesFromType(ESNT_ANIMATED_MESH,tempscenearray);
        for (u32 i=0; i < tempscenearray.size(); ++i)
        {
            scene::ISceneNode * tempeventnode = tempscenearray[i];
            if(tempeventnode){
            tempeventnode->setScale(tempeventnode->getScale()*1.0001f);
            }
        }
        break;
    case 2:
        printf("case2");
        break;
    default:
        break;
    }
}
/*
void Game::addeventtotimer(){

}


/*

Idea currently not in use but might come in handy later on??

                                    this should be a task ID. use enum?
                                         |
timer event needs to keep track of      \ /
//////  pointer to scenenode    |   task to run |   repeat  |   ms between events
    1   *xkdfajlk               |   sometask()  |   false   |           0
    2   *afdafasf               |   sometask2() |   true    |         40000
    3    *dadfasdfdasd          |   sometask1() |   false   |           0
    4
    5
    6
    7
    8
    9

*/
