#pragma once

#include "Banner.h"
#include "Manager.h"
#include "ConfigManager.h"
#include "EnemyManager.h"
#include "WaveManager.h"
#include "ResourcesManager.h"
#include "TowerManager.h"
#include "BulletManager.h"
#include "StatusBar.h"
#include "Panel.h"
#include "PlacePanel.h"
#include "UpgradePanel.h"
#include "PlayerManager.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class GameManager : public Manager<GameManager>
{
	friend class Manager<GameManager>;

public:
	int run(int argc, char** argv);

protected:
	GameManager();
	~GameManager();

private:
	SDL_Event m_event;
	bool m_isQuit = false;

	StatusBar m_statusBar;

	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	SDL_Texture* m_texTileMap = nullptr;

	Panel* m_placePanel = nullptr;
	Panel* m_upgradePanel = nullptr;
	Banner* m_banner = nullptr;

private:
	void initAssert(bool flag, const char* errMsg);

	void onInput();
	void onUpdate(double delta);
	void onRender();

	bool generateTileMapTexture();
	bool checkHome(const SDL_Point& idxTileSelected);
	bool getCursorIdxTile(SDL_Point& idxTileSelected, int screenX, int screenY) const;
	bool canPlaceTower(const SDL_Point& idxTileSelected) const;
	void getSelectedTileCenterPos(SDL_Point& pos, const SDL_Point& idxTileSelected) const;
};
