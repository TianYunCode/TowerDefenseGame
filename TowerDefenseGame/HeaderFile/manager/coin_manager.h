#ifndef _COIN_MANAGER_H_
#define _COIN_MANAGER_H_

#include "coin_prop.h"
#include "manager.h"
#include "config_manager.h"

#include <vector>

class CoinManager : public Manager<CoinManager>
{
	friend class Manager<CoinManager>;

public:
	typedef vector<CoinProp*> CoinPropList;

public:
	void increase_coin(double val);
	void decrease_coin(double val);

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

	double get_current_coin_num();
	CoinPropList& get_coin_prop_list();

	void spawn_coin_prop(const Vector2& position);

protected:
	CoinManager();
	~CoinManager();

private:
	double num_coin = 0;

	CoinPropList coin_prop_list;
};

#endif