#ifndef _HOME_MANAGER_H_
#define _HOME_MANAGER_H_

#include "manager.h"
#include "config_manager.h"
#include "resources_manager.h"

//房屋管理类
class HomeManager : public Manager<HomeManager>
{
	friend class Manager<HomeManager>;

public:
	double get_current_hp_num();  //获取当前剩余血量
	void decrease_hp(double val); //降低血量

protected:
	HomeManager();
	~HomeManager() = default;

private:
	double num_hp = 0;
};

#endif