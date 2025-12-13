#include "CoinManager.h"

CoinManager::CoinManager()
{
	m_numCoin = ConfigManager::instance()->m_numInitialCoin;
}

CoinManager::~CoinManager()
{
	for (CoinProp* coinProp : m_coinPropList)
	{
		delete coinProp;
	}
}

void CoinManager::increaseCoin(double val)
{
	m_numCoin += val;
}

void CoinManager::decreaseCoin(double val)
{
	m_numCoin -= val;

	if (m_numCoin < 0)
	{
		m_numCoin = 0;
	}
}

void CoinManager::onUpdate(double delta)
{
	for (CoinProp* coinProp : m_coinPropList)
	{
		coinProp->onUpdate(delta);
	}

	m_coinPropList.erase(std::remove_if(m_coinPropList.begin(), m_coinPropList.end(), [](CoinProp* coinProp)
		{
			bool deletable = coinProp->canRemove();

			if (deletable)
			{
				delete coinProp;
				coinProp = nullptr;
			}

			return deletable;
		}), m_coinPropList.end());
}

void CoinManager::onRender(SDL_Renderer* renderer)
{
	for (CoinProp* coinProp : m_coinPropList)
	{
		coinProp->onRender(renderer);
	}
}

double CoinManager::getCurrentCoinNum()
{
	return m_numCoin;
}

CoinManager::CoinPropList& CoinManager::getCoinPropList()
{
	return m_coinPropList;
}

void CoinManager::spawnCoinProp(const TwoVector& position)
{
	CoinProp* coinProp = new CoinProp();
	coinProp->setPosition(position);

	m_coinPropList.push_back(coinProp);
}
