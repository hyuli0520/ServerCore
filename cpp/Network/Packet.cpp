#include "pch.h"
#include "Network/Packet.h"

Packet::~Packet()
{
}

vector<char> Packet::GetData()
{
	return m_buffer;
}
