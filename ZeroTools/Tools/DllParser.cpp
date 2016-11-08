#include "stdafx.h"
#include "DllParser.h"

DllParser::DllParser()
{

}

DllParser::~DllParser()
{
}

bool DllParser::Load(const std::string& path)
{
	m_hModule = ::LoadLibrary((LPCWSTR)path.data());

	return NULL != m_hModule;
}

bool DllParser::UnLoad()
{
	bool bVal = !!FreeLibrary(m_hModule);
	m_hModule = NULL;

	return bVal;
}

