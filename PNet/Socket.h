#pragma once
#include"SocketHandle.h"
#include"PResult.h"
#include"IPVersion.h"
#include"SocketOption.h"
#include"IPEndpoint.h"
#include<iostream>
#include"Constants.h"
#include"Packet.h"


namespace PNet
{
	class Socket 
	{
	public:
		Socket( IPVersion ipversion = IPVersion::IPv4,
				SocketHandle handle = INVALID_SOCKET);
		
		PResult Create();
		PResult Close();
		PResult Bind(IPEndpoint endpoint);
		PResult Listen(IPEndpoint endpoint, int backlog = 5);
		SocketHandle GetHandle();
		IPVersion GetIPVersion();
		PResult Accept(Socket & outsocket);
		PResult Connect(IPEndpoint endpoint);
		PResult Send(const void* data, int numberOfBytes, int& bytesSent);
		PResult SendAll(const void* data, int numberOfBytes);
	
		PResult Recv(void* destination, int numberOfBytes, int& bytesReceived);
		PResult RecvAll(void* data, int numberOfBytes);

		PResult Send(Packet& packet);
		PResult Recv(Packet& packet);

	private:
		PResult	SetSocketOption(SocketOption option, BOOL value);
		IPVersion ipversion = IPVersion::IPv4;
		SocketHandle handle = INVALID_SOCKET;
	};
}