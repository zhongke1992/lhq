#include "stdafx.h"
#include "Control.h"

 CControl* CControl::m_pControl = NULL;

CControl::CControl(void)
{
}

CControl::~CControl(void)
{
}

const CControl* CControl::getInstance()
	{
	if (NULL == m_pControl)
		m_pControl = new CControl();
	return m_pControl;
	}

