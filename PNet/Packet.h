#pragma once
#define WIN32_LEAN_AND_MEAN
#include<vector>
#include<winsock.h>
#include<iostream>

namespace PNet
{
	class Packet
	{
	public:
		void Clear();
		void Append(const void* data, uint32_t size);

		Packet& operator << (uint32_t data);			//Overload << and >> operator to insert and extract integers into and out of the packets
		Packet& operator >> (uint32_t& data);

		Packet& operator << (const std::string & data);			//Overload << and >> operator to insert and extract strings into and out of the packets
		Packet& operator >> (std::string & data);

		uint32_t extractionOffset = 0;
		std::vector<char> buffer;

	};
}