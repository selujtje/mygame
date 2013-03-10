/* 
 * File:   main.cpp
 * Author: jules
 *
 * Created on February 23, 2013, 9:58 PM
 */
#include <irrNet.h>
#include <iostream>
#include <unistd.h>
using namespace std;
using namespace irr;
using namespace core;

struct playerdata
{
	core::stringc username;
	core::vector3df location;
	f32 rotation;
	f32 level;
}playerdata[12];
int numberofplayers =0;


class MyNetCallback : public net::INetCallback
{
public:
	virtual void handlePacket(net::SInPacket& packet)
	{	
		
		packet.decryptPacket("hushthisissecret");
		packet.deCompressPacket();
		u16 playerId = packet.getPlayerId();
		std::cout << "\nYay! I've got mail from player n0: "<< playerId <<endl;
		packet >> datapointer[packet.getPlayerId()].username;
		packet >> datapointer[packet.getPlayerId()].location;
		sleep(1);
		packet >> datapointer[packet.getPlayerId()].rotation;
		packet >> datapointer[packet.getPlayerId()].level;
		std::cout << "success!!!" << endl;

	}
	
	virtual void onConnect(const u16 playerId)
	{
			numberofplayers++;	
	}
	
	// Similar to the onConnect function, except it happens when a
	// player disconnects. When this happens we will just report
	// which player has disconnected.
	virtual void onDisconnect(const u16 playerId)
	{
		numberofplayers--;
	}
	
};

// Ok, lets go from the start, int main()
int main()
{
	
	// Ask the user whether they want to be the server or a client.
	std::cout << "Starting server...";
	
	// If they typed 's' they are the server else they are the client.
		// Create a server and pass in a new instance of our callback class. The default
		// port that clients can connect to is set to 45000.
		MyNetCallback* netCallback = new MyNetCallback();
		net::INetManager* netManager = net::createIrrNetServer(netCallback);

		// Setting verbose to true makes irrNetLite spit out debug information to the console.
		netManager->setVerbose(true);
		
		// While the connection is active (Not failed), we update the netManager.
		// Note that since this is a server the connection will pretty much always
		// be flagged as active, unless some error occured whilst creating the server.
		// A value of 1000 is passed to update to make it hang for a second and wait for
		// packets to arrive. (Recommended for servers, so you don't busy-loop).
		while(netManager->getConnectionStatus() != net::EICS_FAILED)
		{
			netManager->update(1000);
			net::SOutPacket packetout;
			packetout << numberofplayers;
			std::cout << "current number of players: " << numberofplayers <<std::endl;
			for (u16 i=0; i < numberofplayers; ++i)
			{
				packetout << datapointer[i].username;
				packetout << datapointer[i].location;
				sleep(1);
				packetout << datapointer[i].rotation;
				packetout << datapointer[i].level;
				std::cout << "\nplayerdata added\n";
			}
			netManager->sendOutPacket(packetout);
				
		}	
		// Don't forget to clean up!
		delete netManager;
		delete netCallback;
	//	delete [] datapointer;

	// And we're done, return 0 and make like a tree.
	return 0;
}