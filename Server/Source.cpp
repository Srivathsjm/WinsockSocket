// Server code
#include<PNet/IncludeMe.h>
#include<iostream>

using namespace PNet;
int main() {
	if (Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;
// **************************Printing IP details**********************************
		/*
		IPEndpoint test("192.168.0.2", 8080);
		if (test.GetIPVersion() == IPVersion::IPv4)
		{
			std::cout << "Hostname: " << test.GetHostname() << std::endl;
			std::cout << "IP: " << test.GetIPString() << std::endl;
			std::cout << "Port: " << test.GetPort() << std::endl;
			std::cout << "IP Bytes..." << std::endl;
			for (auto & digit : test.GetIPBytes())
			{
				std::cout << (int)digit << std::endl;
			}
		}

		else
		{
			std::cerr << "This is not an IPv4 address." << std::endl;
		}
		*/
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		Socket socket;

	
		if (socket.Create() == PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;

// **************************Binding socket to a port**********************************
			/*
			if (socket.Bind(IPEndpoint("127.0.0.1", 4790)) == PResult::P_Success)
			{
				std::cout << "Socket successfully bound to port 4790." << std::endl;
			}
			else
			{
				std::cerr << "Failed to bind socket to port 4790." << std::endl;

			}

			*/

// **************************Socket listening to a port********************************
			if (socket.Listen(IPEndpoint("127.0.0.1", 4790)) == PResult::P_Success)		//Backlog argument in listen() defaults to 5 if not given
			{
				std::cout<<"Socket successfully listening to port 4790."<<std::endl;
				Socket newConnection;
				if (socket.Accept(newConnection) == PResult::P_Success)
				{
					std::cout << "New connection accepted." << std::endl;

					//char buffer[256];

					std::string buffer = "";
					
					//int bytesReceived = 0;
					//int result = PResult::P_Success;

					uint32_t a = 0, b = 0, c = 0;
					std::string x = "";

					Packet packet;
					while (true)
					{
						/*
						//result = newConnection.Recv(buffer, 256, bytesReceived);

						uint32_t bufferSize = 0;
						int result = newConnection.RecvAll(&bufferSize, sizeof(uint32_t));
						if (result != PResult::P_Success)
							break;
						bufferSize = ntohl(bufferSize);

						if (bufferSize > PNet::g_MaxPacketSize)
						{
							break;
						}

						buffer.resize(bufferSize);

						result = newConnection.RecvAll(&buffer[0], bufferSize);
						if (result != PResult::P_Success)
							break;
						
						*/

						PResult result = newConnection.Recv(packet);
						if (result != PResult::P_Success)
						{
							break;
						}

						packet >> a >> b >> c;  // Extract the integer from the packet to a,b and c
						packet >> x;			// Extract the string from the packet to x

						std::cout << a << "," << b << "," << c << std::endl;
						std::cout << x << std::endl;

						//std::cout <<"["<< bufferSize <<"] - "<< buffer <<std::endl;

					}

					newConnection.Close();
				}
				else
				{
					std::cout << "Failed to accept new connection." << std::endl;

				}
			}
			else
			{
				std::cerr << "Failed to listen on port 4790." << std::endl;
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