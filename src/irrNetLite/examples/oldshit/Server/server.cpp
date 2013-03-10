#include <irrNet.h>
#include <iostream>
#include <unistd.h>
using namespace std;
using namespace irr;
using namespace core;
 
int numberofplayers =0;

class MyNetCallback : public net::INetCallback
{
public:
	virtual void handlePacket(net::SInPacket& packet)
	{	
		
		packet.decryptPacket("hushthisissecret");
		packet.deCompressPacket();
		f32 height;
		packet >> height;
	}
	
};

// Ok, lets go from the start, int main()
int main()
{
	
	// Ask the user whether they want to be the server or a client.
	std::cout << "\nStarting server...appelflap\n";

		MyNetCallback* netCallback = new MyNetCallback();
		net::INetManager* netManager = net::createIrrNetServer(netCallback);


		netManager->setVerbose(true);
	
		while(netManager->getConnectionStatus() != net::EICS_FAILED)
		{
			netManager->update(1000);
		
				
		}	
		// Don't forget to clean up!
		delete netManager;
		delete netCallback;
		//delete [] playerdata;

	// And we're done, return 0 and make like a tree.
	return 0;
}
