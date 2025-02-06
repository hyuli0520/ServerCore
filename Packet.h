#pragma once

// [size(2)][id(2)][data...]
struct PacketHeader
{
	unsigned short size; // Packet Size
	unsigned short id; // Protocol ID
};

struct PacketInfo
{
	unsigned int clientIndex = 0;
	PacketHeader packetHeader;
	char* data = nullptr;
};

class Packet
{
	Packet() = default;
	virtual ~Packet();
};

