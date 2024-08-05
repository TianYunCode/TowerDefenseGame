#ifndef _COIN_MANAGER_H_
#define _COIN_MANAGER_H_

#include "coin_prop.h"
#include "manager.h"
#include "config_manager.h"

#include <vector>

//金币管理类
class CoinManager : public Manager<CoinManager>
{
	friend class Manager<CoinManager>;

public:
	typedef vector<CoinProp*> CoinPropList;

public:
	void increase_coin(double val); //增加金币
	void decrease_coin(double val);	//减少金币

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

	double get_current_coin_num();		//获取当前硬币数字
	CoinPropList& get_coin_prop_list(); //获取硬币道具列表

	void spawn_coin_prop(const TwoVector& position);

protected:
	CoinManager();
	~CoinManager();

private:
	double num_coin = 0; //金币数

	CoinPropList coin_prop_list;
};

#endif