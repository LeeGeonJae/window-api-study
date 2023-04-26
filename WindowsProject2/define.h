#pragma once

#define SINGLE(type) public:\
					 static type* GetInst()\
					{\
						static type mgr;\
						return &mgr;\
					}\
					 private:\
						type(); \
						~type();

#define DT CTimeMgr::GetInst()->GetDT()
#define fDT CTimeMgr::GetInst()->GetfDT()