#include "pch.h"
#include "CEventMgr.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}



void CEventMgr::update()
{
	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Excute(m_vecEvent[i]);
	}
}

void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:


		break;
	case EVENT_TYPE::DELETE_OBJECT:

		break;
	case EVENT_TYPE::SCENE_CHANGE:

		break;
	default:
		break;
	}
}
