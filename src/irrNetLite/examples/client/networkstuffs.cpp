#include "networkstuffs.h"
#include <irrNet.h>
#include <iostream>

using namespace std;
using namespace irr;
using namespace core;
playerdata playerdataholder[64];
 int numberofplayers;
u32 myplayerid;
	// Our handlePacket function.
void ClientNetCallback::handlePacket(net::SInPacket& packet)
	{
		std::cout << "\nserver sent me a message:\n";
		packet.decryptPacket("hushthisissecret");
		packet.deCompressPacket();
		cout << "decrypted..." <<endl;
		int messagetype;
		packet >> messagetype;
		core::stringc denymessage;
		switch(messagetype)
		{
		    case 1://access to server denied

                packet >> denymessage;//reason why
                cout << denymessage.c_str();
                break;
           case 2://welcome to the server
                //load/resync all data known of each player
                break;
            case 3://send all objects you need to see
                break;
            case 4:// a regular update message
                packet >> numberofplayers;
                std::cout << "\n\nWe currently have: " << numberofplayers << " players" <<endl;
                for (u16 i=1; i < numberofplayers+1; ++i)
                {
                    u16 playerid;
                    packet >> playerid;
                    packet >> playerdataholder[playerid].username;
                    packet >> playerdataholder[playerid].location;
                    packet >> playerdataholder[playerid].rotation;
                    packet >> playerdataholder[playerid].level;
                    std::cout << "\nUsername: " << playerdataholder[i].username.c_str();
                    std::cout << " \tRotation: " << playerdataholder[i].rotation;
                    std::cout << " \tLevel: " << playerdataholder[i].level;
                    std::cout << std::endl;
                    if(globalnode &&playerdataholder[playerid].username !=myusername ){
                    globalnode->setPosition(playerdataholder[playerid].location);
                    }
                }
                break;
            case 5://someone sent a message
                break;
            case 6:
                break;
            default:
                cout << "\n\nWAAAAAAAAAAAAAAAhhhh unknown message(type)";
		}
	}

