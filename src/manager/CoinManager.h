#pragma once

#include "CoinProp.h"
#include "Manager.h"
#include "ConfigManager.h"

#include <vector>

class CoinManager : public Manager<CoinManager>
{
	friend class Manager<CoinManager>;

public:
	typedef std::vector<CoinProp*> CoinPropList;

public:
	void increaseCoin(double val);
	void decreaseCoin(double val);

	void onUpdate(double delta);
	void onRender(SDL_Renderer* renderer);

	double getCurrentCoinNum();
	CoinPropList& getCoinPropList();

	void spawnCoinProp(const TwoVector& position);

protected:
	CoinManager();
	~CoinManager();

private:
	double m_numCoin = 0;
	CoinPropList m_coinPropList;
};
