
#include <irrNet.h>
#include <iostream>

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
//playerdata * playerdata = new 


// The client callback.
class ClientNetCallback : public net::INetCallback
{
public:
	// Our handlePacket function.
	virtual void handlePacket(net::SInPacket& packet)
	{	
		std::cout << "\nwutzies\n";
		packet.decryptPacket("hushthisissecret");
		packet.deCompressPacket();
		packet >> numberofplayers;

		std::cout << "\n\nWe currently have: " << numberofplayers << " players";	
		for (u16 i=0; i < numberofplayers; ++i)
		{
		std::cout << "\n check\n";
		packet >> playerdata[i].username;
		packet >> playerdata[i].location;
		packet >> playerdata[i].rotation;
		packet >> playerdata[i].level;/*
		std::cout << "\nUsername: " << playerdata[packet.getPlayerId()].username;
		std::cout << " \tRotation:  " << playerdata[packet.getPlayerId()].rotation;
		std::cout << " \tLevel:     " << playerdata[packet.getPlayerId()].level;
		std::cout << std::endl;*/
		}
	}
};


int main()
{
		std::cout << "Server IP-adress:127.0.0.1";
		ClientNetCallback* clientCallback = new ClientNetCallback();
		net::INetManager* netManager = net::createIrrNetClient(0, "127.0.0.1");
		std::cout << "\nServer IP-adress:\n";
		// Enable debug messages.
		netManager->setVerbose(true);

		// Here comes the fun part, while the client is connected we update the netManager
		// and ask it to wait 1 second (1000 milliseconds) for new packets to arrive before
		// returning. Since the client in this example doesn't actually receive any packets,
		// the only purpose of the update call is to leave a 1 second interval between each
		// packet we send.
		while(netManager->getConnectionStatus() != net::EICS_FAILED)
		{
			netManager->update(1000);
			net::SOutPacket packetout;
			packetout << "luckyluke";
			packetout << core::vector3df(50.0f, 30.0f, 20.0f);
			packetout << 52.2f;
			packetout << 23.2f;
			packetout.compressPacket();
			packetout.encryptPacket("hushthisissecret");
			netManager->sendOutPacket(packetout);

		}
		
		// When the connection disconnects (Or fails), the loop will terminate.
		// Remember to delete the netManager so that all the low level networking
		// stuff is cleaned up properly.
		delete netManager;
		//delete [] playerdata;
	// And we're done, return 0 and make like a tree.
	return 0;
}
