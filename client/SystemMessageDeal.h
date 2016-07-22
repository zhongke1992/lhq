#pragma once
#include "messagechain.h"

class CSystemMessageDeal :
	public CMessageChain
{
public:
	CSystemMessageDeal(unsigned int min, unsigned int max);
	virtual ~CSystemMessageDeal(void);

		};

