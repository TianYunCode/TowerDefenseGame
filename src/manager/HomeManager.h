#pragma once

#include "Manager.h"
#include "ConfigManager.h"
#include "ResourcesManager.h"

class HomeManager : public Manager<HomeManager>
{
	friend class Manager<HomeManager>;

public:
	double getCurrentHpNum();
	void decreaseHp(double val);

protected:
	HomeManager();
	~HomeManager() = default;

private:
	double m_numHp = 0;
};
