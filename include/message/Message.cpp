#include "StdAfx.h"
#include "Message.h"

CMessage::CMessage(void)
{
}

CMessage::~CMessage(void)
{
}

void CMessage::Serialize(CArchive& ar)
{
if (ar.IsStoring())
{
ar<<m_type;
ar << m_from;
ar << m_to;
ar << m_text;
}
else
{
ar >> m_type;
ar >> m_from;
ar >> m_to;
ar >> m_text;
}
}

void CMessage::Reset()
{
m_type = -1;
m_text = "";
}
