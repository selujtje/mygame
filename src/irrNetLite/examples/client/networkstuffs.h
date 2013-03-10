#ifndef NETWORKSTUFFS_H_INCLUDED
#define NETWORKSTUFFS_H_INCLUDED
#include "irrlicht.h"
#include <irrNet.h>
using namespace std;
using namespace irr;
using namespace core;

struct playerdata
{
    u16 PlayerId;
	stringc username;
	vector3df location;
	f32 rotation;
	f32 level;
};
extern char myusername[20];
extern scene::IAnimatedMeshSceneNode* globalnode;
class ClientNetCallback : public net::INetCallback
{
public:
    virtual void handlePacket(net::SInPacket& packet);
};


#endif
