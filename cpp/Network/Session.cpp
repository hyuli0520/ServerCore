#include "pch.h"
#include "Network/Session.h"

Session::Session()
{
}

Session::~Session()
{
}

void Session::Run(shared_ptr<cppx::socket> sock)
{
	m_sock = sock;

	m_recvContext.completed_callback = std::bind(&Session::OnRecvCompleted, this, placeholders::_1, placeholders::_2);
	m_recvContext._buffer = m_buffer;
	m_sendContext.completed_callback = std::bind(&Session::OnSendCompleted, this, placeholders::_1, placeholders::_2);
	
	m_sock->recv(&m_recvContext);
}

cppx::socket Session::GetSocket()
{
	return *m_sock;
}

void Session::OnRecvCompleted(context* context, bool success)
{
	if (success)
	{
		OnRecv(reinterpret_cast<byte*>(&context->_buffer), sizeof(context->_buffer));
		m_sock->recv(context);
	}
}

void Session::OnSendCompleted(context* context, bool success)
{
	if (success)
		cout << "OnSendCompleted" << endl;
}

void Session::Send(Packet* packet, bool sendContext)
{
	if (sendContext)
		SendContext(packet->GetData());
	else
		SendChar(packet->GetData());
}

void Session::SendChar(vector<char> buffer)
{
	m_sock->send(buffer);
}

void Session::SendContext(vector<char> buffer)
{
	m_sendContext._buffer = buffer;
	m_sock->send(&m_sendContext);
}

void Session::Disconnect()
{
	if (m_connected.exchange(false) == false)
		return;

	OnDisconnected();
}
 