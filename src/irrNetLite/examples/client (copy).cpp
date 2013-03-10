#include <irrArray.h>
#include <irrNet.h>
#include <iostream>

using namespace irr;
		core::array<core::stringc> username;
		core::array<core::vector3df> vec;
		core::array<f32> rotation;
		core::array<f32> level;


/*class MyNetCallback : public net::INetCallback
{
public:
	virtual void handlePacket(net::SInPacket& packet)
	{
		packet.decryptPacket("hushthisissecret");
		packet.deCompressPacket();
		short int numberofplayers;
		packet >> numberofplayers;

		std::cout << "\n\nWe currently have: " << numberofplayers << " players";	
		for (u16 i=0; i < numberofplayers; ++i)
		{
		packet >> username[i];
		packet >> vec[i];
		packet >> rotation[i];
		packet >> level[i];
		
		std::cout << "\nUsername: " << username[i].c_str();
		std::cout << " \nPosition:  " << vec[i].X << " " << vec[i].Y << " " << vec[i].Z;
		std::cout << " \nRotation:  " << rotation[i];
		std::cout << " \nLevel:     " << level[i];
		std::cout << std::endl;
		}
		
	}
};*/

// The client callback.
class ClientNetCallback : public net::INetCallback
{
public:
	// Our handlePacket function.
	virtual void handlePacket(net::SInPacket& packet)
	{
		packet.decryptPacket("hushthisissecret");
		packet.deCompressPacket();
		short int numberofplayers;
		packet >> numberofplayers;

		std::cout << "\n\nWe currently have: " << numberofplayers << " players";	
		for (u16 i=0; i < numberofplayers; ++i)
		{
		std::cout << "\n check\n";
		packet >> username[i];
		packet >> vec[i];
		packet >> rotation[i];
		packet >> level[i];
		
		std::cout << "\nUsername: " << username[i].c_str();
		std::cout << " \tPosition:  " << vec[i].X << " " << vec[i].Y << " " << vec[i].Z;
		std::cout << " \tRotation:  " << rotation[i];
		std::cout << " \tLevel:     " << level[i];
		std::cout << std::endl;
		}
	}
};


int main()
{



		std::cout << "Server IP-adress:127.0.0.1";
		ClientNetCallback* clientCallback = new ClientNetCallback();
		net::INetManager* netManager = net::createIrrNetClient(clientCallback, "127.0.0.1");
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
			netManager->update(100);

		}
		
		// When the connection disconnects (Or fails), the loop will terminate.
		// Remember to delete the netManager so that all the low level networking
		// stuff is cleaned up properly.
		delete netManager;
	
	// And we're done, return 0 and make like a tree.
	return 0;
}
