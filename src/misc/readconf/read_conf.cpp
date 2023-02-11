#include "read_conf.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <string.h>
#include "func.h"
using namespace std;

#ifdef _WIN32
#define strcasecmp _stricmp
#define strncasecmp _strnicmp 
#endif

Config *Config::m_instance = nullptr;

Config::Config()
{
}
Config::~Config()
{
	std::vector<LPConfItem>::iterator pos;
	for (pos = m_ConfigItemList.begin(); pos != m_ConfigItemList.end(); pos++)
	{
		delete (*pos);
	}
	m_ConfigItemList.clear();
}
bool Config::Load(const char *pconfName)
{
	FILE *fp;
	fp = fopen(pconfName, "r");
	assert(fp);
	char linebuf[501];
	while (!feof(fp))
	{
		if (fgets(linebuf, 500, fp) == nullptr)
		{
			continue;
		}
		if (linebuf[0] == 0)
		{
			continue;
		}
		if (*linebuf == ';' || *linebuf == ' ' || *linebuf == 't' || *linebuf == '\n')
		{
			continue;
		}
	lblprocstring:
		if (strlen(linebuf) > 0)
		{
			if (linebuf[strlen(linebuf) - 1] == 13 || linebuf[strlen(linebuf) - 1] == 10 || linebuf[strlen(linebuf) - 1] == 32)
			{
				linebuf[strlen(linebuf) - 1] = 0;
				goto lblprocstring;
			}
		}
		if (linebuf[0] == 0)
		{
			continue;
		}
		if (*linebuf == '[')
			continue;
		char *ptmp = strchr(linebuf, '=');
		if (ptmp != nullptr)
		{
			LPConfItem p_confitem = new ConfItem;
			memset(p_confitem, 0, sizeof(ConfItem));
			strncpy(p_confitem->ItemName, linebuf, (int)(ptmp - linebuf));
			strcpy(p_confitem->ItemContent, ptmp + 1);
			Rtrim(p_confitem->ItemName);
			Ltrim(p_confitem->ItemName);
			Rtrim(p_confitem->ItemContent);
			Ltrim(p_confitem->ItemContent);
			m_ConfigItemList.push_back(p_confitem); // 内存要释放，因为这里是new出来的
		}
	}
	fclose(fp);
	return true;
}
const char *Config::GetString(const char *p_itemname)
{
	std::vector<LPConfItem>::iterator pos;
	for (pos = m_ConfigItemList.begin(); pos != m_ConfigItemList.end(); pos++)
	{
		if (strcasecmp((*pos)->ItemName, p_itemname) == 0)
		{
			return (*pos)->ItemContent;
		}
	}
	return nullptr;
}
int Config::GetIntDefault(const char *p_itemname, const int def)
{
	std::vector<LPConfItem>::iterator pos;
	for (pos = m_ConfigItemList.begin(); pos != m_ConfigItemList.end(); pos++)
	{
		if (strcasecmp((*pos)->ItemName, p_itemname) == 0)
		{
			return atoi((*pos)->ItemContent);
		}
	}
	return def;
}