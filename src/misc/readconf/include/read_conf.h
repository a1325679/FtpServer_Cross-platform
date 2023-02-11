#ifndef _X_CONF_H_
#define _X_CONF_H_
#include <vector>
#include "global.h"
class Config
{
public:
	~Config();
	static Config *GetInstance()
	{
		if (m_instance == nullptr)
		{

			if (m_instance == nullptr)
			{
				m_instance = new Config();
			}
		}
		return m_instance;
	}
	class CGarhuishou
	{
	public:
		~CGarhuishou()
		{
			if (Config::m_instance)
			{
				delete Config::m_instance;
				Config::m_instance = nullptr;
			}
		}
	};
	bool Load(const char *pconfName);
	const char *GetString(const char *p_itemname);
	int GetIntDefault(const char *p_itemname, const int def);
	std::vector<LPConfItem> m_ConfigItemList;

private:
	Config();
	static Config *m_instance;
};

#endif
