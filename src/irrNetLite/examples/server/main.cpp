#include <irrNet.h>
#include <iostream>
#define SECRET_KEY "hushthisissecret"
using namespace std;
using namespace irr;
using namespace core;


const int maxplayers =64;

struct playerdata
{
    bool connected;
    u16 PlayerId;
	stringc username;
	vector3df location;
	f32 rotation;
	f32 level;
}playerdata[maxplayers];




class MyNetCallback : public net::INetCallback
{
public:
	virtual void handlePacket(net::SInPacket& packet)
	{

		packet.decryptPacket(SECRET_KEY);
		packet.deCompressPacket();
		playerdata[packet.getPlayerId()].PlayerId = packet.getPlayerId();
		cout << "decrypted..." <<endl;
		unsigned int messagetype;
		packet >> messagetype;
		stringc username;
		switch(messagetype)
		{
		    case 1://client trying to connect
                packet >> username;
                break;
            case 2://password given
                break;
            case 3://regular update message
                std::cout << "\nYay! I've got mail from player n0: "<< packet.getPlayerId() <<endl;
                packet >> playerdata[packet.getPlayerId()].username;
                packet >> playerdata[packet.getPlayerId()].location;
                packet >> playerdata[packet.getPlayerId()].rotation;
                packet >> playerdata[packet.getPlayerId()].level;
                std::cout << "success!!!" << endl;
                break;
        }
	}

	virtual void onConnect(const u16 playerId)
	{
        playerdata[playerId].connected = true;
	}

	// Similar to the onConnect function, except it happens when a
	// player disconnects. When this happens we will just report
	// which player has disconnected.
	virtual void onDisconnect(const u16 playerId)
	{
		playerdata[playerId].connected = false;
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
       // 			numberofplayers = netManager->getPeerCount();
		// While the connection is active (Not failed), we update the netManager.
		// Note that since this is a server the connection will pretty much always
		// be flagged as active, unless some error occured whilst creating the server.
		// A value of 1000 is passed to update to make it hang for a second and wait for
		// packets to arrive. (Recommended for servers, so you don't busy-loop).
		while(netManager->getConnectionStatus() != net::EICS_FAILED)
		{
			netManager->update(1000);
			net::SOutPacket packetout;

			packetout << 4; //we're sending a regular update message
			int playernumber =0;
			for (u16 i=1; i < maxplayers+1; ++i)
			{
			    if(playerdata[i].connected==true){
			        playernumber++;}
			}
			cout <<"number of players: "<<playernumber<<endl;
			packetout << playernumber;
			for (u16 i=1; i < maxplayers+1; ++i)
			{
			    if(playerdata[i].connected)
			    {
                    cout << "username: "<< playerdata[i].username.c_str()<<endl;
                    packetout << playerdata[i].PlayerId;
                    packetout << playerdata[i].username;
                    packetout << playerdata[i].location;
                    packetout << playerdata[i].rotation;
                    packetout << playerdata[i].level;
                    std::cout << "\nplayerdata added\n";
			    }
			}
			packetout.compressPacket();
			packetout.encryptPacket("hushthisissecret");
			netManager->sendOutPacket(packetout);

		}
		// Don't forget to clean up!
		delete netManager;
		delete netCallback;
	//	delete [] playerdata;

	// And we're done, return 0 and make like a tree.
	return 0;
}
