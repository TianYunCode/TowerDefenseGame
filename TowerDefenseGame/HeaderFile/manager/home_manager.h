#ifndef _HOME_MANAGER_H_
#define _HOME_MANAGER_H_

#include "manager.h"
#include "config_manager.h"
#include "resources_manager.h"

//���ݹ�����
class HomeManager : public Manager<HomeManager>
{
	friend class Manager<HomeManager>;

public:
	double get_current_hp_num();  //��ȡ��ǰʣ��Ѫ��
	void decrease_hp(double val); //����Ѫ��

protected:
	HomeManager();
	~HomeManager() = default;

private:
	double num_hp = 0;
};

#endif