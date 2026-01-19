#include "Plug.h"
#include "other.h"

Plug::Plug()
{
	memset(m_plug, 0, sizeof(PLGINFO) * MAX_PLUG_COUNT);
}

Plug::~Plug()
{

}

int Plug::PlugLoad(HMODULE hmodule, int id, FPlgRecvPkt OnRecv, const char* name)
{
	if (id >= MAX_PLUG_COUNT)
	{
		return (ERROR_NOT_ENOUGH_QUOTA);
	}

	m_cs.Enter();

	if (m_plug[id].h)
	{
		m_cs.Leave();

		return (ERROR_ALREADY_EXISTS);
	}

	m_plug[id].ref = 1;
	m_plug[id].h = hmodule;
	m_plug[id].OnRecv = OnRecv;
	wsprintfA(m_plug[id].name, name);

	m_cs.Leave();
	return 0;
}

void Plug::start()
{
	WCHAR name[32] = { 0 };

	wsprintfW(name, PLUG_MAP_NAME, GetCurrentProcessId());

	HANDLE hmap;

	if (NULL == (hmap = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(PLGFUNC), name)))
	{
		return;
	}

	PLGFUNC* pi = NULL;

	if (NULL == (pi = (PLGFUNC*)MapViewOfFile(hmap, FILE_MAP_WRITE, 0, 0, 0)))
	{
		return;
	}

	pi->PlgLoad = PlgLoad;

	DWORD op;

	VirtualProtect(pi, sizeof(PLGFUNC), PAGE_READONLY, &op);

	CPlgOhter::GetInstance()->Load(HMODULE(-1));
}

Plug* Plug::GetInstance() {

	static Plug* lp = NULL;

	if (lp == NULL)
	{
		lp = new Plug;
	}

	return lp;
}

int Plug::OnRecv(HANDLE con, PACKET_HEADER* pkt)
{
	for (int i = 0; i < MAX_PLUG_COUNT; i++)
	{
		BOOL caller;

		m_cs.Enter();

		if (m_plug[i].h)
		{
			caller = TRUE; m_plug[i].ref++;
		}
		else
		{
			caller = FALSE;
		}

		m_cs.Leave();

		if (!caller)
		{
			continue;
		}

		int ercode = m_plug[i].OnRecv(con, pkt);

		m_cs.Enter();

		if (m_plug[i].h)
		{
			m_plug[i].ref--;
		}

		m_cs.Leave();

		if (ercode != (-1))
		{
			return (ercode);
		}
	}

	return 0;
}
