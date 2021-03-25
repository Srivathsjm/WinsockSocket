// Client code

#include<PNet/IncludeMe.h>
#include<iostream>

using namespace PNet;
int main() {
	if (Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;
		Socket socket;
		if (socket.Create() == PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			if (socket.Connect(IPEndpoint("127.0.0.1", 4790)) == PResult::P_Success)
			{
				std::cout << "Successfully connected to server." << std::endl;
				
				/*
				char buffer[256];
				strcpy_s(buffer, "Hello world from client.\0");
				*/
				//int bytesSent = 0;

				//Send 4 byte unsigned integer containing buffer size
				//Send Buffer

				//We end up sending 4+1 Bytes

				//std::string buffer = "Hello world from client.";

				//int result = PResult::P_Success;
				
				//while (result == PResult::P_Success)

				uint32_t a = 4, b = 6, c = 9;
				std::string x = "Hello.";
				Packet packet;
				packet << a << b << c;		//Insert the integers into the packet
				packet << x;				//Insert the string into the packet
				while (true)
				{
					//result = socket.Send(buffer, 256, bytesSent);

					/*
					uint32_t bufferSize = buffer.size();
					bufferSize = htonl(bufferSize);
					int result = socket.SendAll(&bufferSize, sizeof(uint32_t));
					if (result != PResult::P_Success)
						break;

					result = socket.SendAll(buffer.data(), buffer.size());
					if (result != PResult::P_Success)
						break;
					
					*/

					PResult result = socket.Send(packet);
					if (result != PResult::P_Success)
					{
						break;
					}

					std::cout << "Attempting to send chunk of data..." << std::endl;
					Sleep(500);
				}
			}

			else
			{
				std::cerr << "Failed to connect to server." << std::endl;
			}
			socket.Close();
		}
		else
		{
			std::cerr << "Socket failed to create." << std::endl;
		}
	}
	Network::Shutdown();
	system("pause");
	return 0;
}