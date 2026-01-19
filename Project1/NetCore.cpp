#include "NetCore.h"
#include "Connect.h"
#include "Plug.h"
NetCore::NetCore()
{
}

NetCore::~NetCore()
{

}

void NetCore::start() {
	while (1) {
	
		Connect::GetInstance()->ResetConnect();

		Conn* conn = Connect::GetInstance()->NewConnect();

		if (conn)
		{
			Work(conn, CMD_MAIN_CONN, 0);
			delete conn;
		}

		//SleepTime();
	}
}

void NetCore::Work(Conn* con, int type, DWORD connid)
{
	int error = 0;

	PACKET_HEADER pkt = { 0 };

	pkt.cmd = type;
	pkt.length = sizeof(DWORD);

	if (con->SendAll((char*)&pkt, sizeof(PACKET_HEADER)))
	{
		return;
	}

	if (con->SendAll((char*)&connid, pkt.length))
	{
		return;
	}

	while (error == 0)
	{
		if (error = con->RecvAll((char*)&pkt, sizeof(pkt), 1000 * 60 * 60))
		{
			break;
		}

		if (CMD_SUB_CONN == pkt.cmd)
		{
			//error = SubConn(con, &pkt);
		}
		else
		{
			error = Plug::GetInstance()->OnRecv(con, &pkt);
		}
	}
}
