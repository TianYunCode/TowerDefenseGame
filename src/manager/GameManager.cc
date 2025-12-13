#include "GameManager.h"

GameManager::GameManager()
{
	initAssert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2 初始化失败！");
	initAssert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_imgae 初始化失败！");
	initAssert(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer 初始化失败！");
	initAssert(!TTF_Init(), u8"SDL_ttf 初始化失败！");

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

	ConfigManager* config = ConfigManager::instance();

	initAssert(config->m_map.load("config/map.csv"), u8"加载游戏地图失败！");
	initAssert(config->loadLevelConfig("config/level.json"), u8"加载关卡配置失败！");
	initAssert(config->loadGameConfig("config/config.json"), u8"加载游戏配置失败！");

	m_window = SDL_CreateWindow(config->m_basicTemplate.m_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		config->m_basicTemplate.m_windowWidth, config->m_basicTemplate.m_windowHeight, SDL_WINDOW_SHOWN);
	initAssert(m_window, u8"创建游戏窗口失败！");

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	initAssert(m_renderer, u8"创建渲染器失败！");

	initAssert(ResourcesManager::instance()->loadFromFile(m_renderer), u8"加载游戏资源失败！");

	initAssert(generateTileMapTexture(), u8"生成瓦片地图纹理失败！");

	m_statusBar.setPosition(15, 15);

	m_banner = new Banner();
	m_placePanel = new PlacePanel();
	m_upgradePanel = new UpgradePanel();
}

GameManager::~GameManager()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int GameManager::run(int argc, char** argv)
{
	Mix_FadeInMusic(ResourcesManager::instance()->getMusicPool().find(ResID::Music_BGM)->second, -1, 1500);

	Uint64 lastCounter = SDL_GetPerformanceCounter();
	const Uint64 counterFreq = SDL_GetPerformanceFrequency();

	while (!m_isQuit)
	{
		while (SDL_PollEvent(&m_event))
		{
			onInput();
		}

		Uint64 currentCounter = SDL_GetPerformanceCounter();
		double delta = (double)(currentCounter - lastCounter) / counterFreq;
		lastCounter = currentCounter;
		if (delta * 1000 < 1000.0 / 60)
		{
			SDL_Delay((Uint32)(1000.0 / 60 - delta * 1000));
		}

		onUpdate(delta);

		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);

		onRender();

		SDL_RenderPresent(m_renderer);
	}

	return 0;
}

void GameManager::initAssert(bool flag, const char* errMsg)
{
	if (flag)
	{
		return;
	}

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"游戏启动失败", errMsg, m_window);
	exit(-1);
}

void GameManager::onInput()
{
	static SDL_Point posCenter;
	static SDL_Point idxTileSelected;
	static ConfigManager* instance = ConfigManager::instance();

	switch (m_event.type)
	{
	case SDL_QUIT:
		m_isQuit = true;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (instance->m_isGameOver)
		{
			break;
		}

		if (getCursorIdxTile(idxTileSelected, m_event.motion.x, m_event.motion.y))
		{
			getSelectedTileCenterPos(posCenter, idxTileSelected);

			if (checkHome(idxTileSelected))
			{
				m_upgradePanel->setIdxTile(idxTileSelected);
				m_upgradePanel->setCenterPos(posCenter);
				m_upgradePanel->show();
			}
			else if (canPlaceTower(idxTileSelected))
			{
				m_placePanel->setIdxTile(idxTileSelected);
				m_placePanel->setCenterPos(posCenter);
				m_placePanel->show();
			}
		}
		break;
	default:
		break;
	}

	if (!instance->m_isGameOver)
	{
		m_placePanel->onInput(m_event);
		m_upgradePanel->onInput(m_event);
		PlayerManager::instance()->onInput(m_event);
	}
}

void GameManager::onUpdate(double delta)
{
	static bool isGameOverLastTick = false;
	static ConfigManager* instance = ConfigManager::instance();

	if (!instance->m_isGameOver)
	{
		m_statusBar.onUpdate(m_renderer);
		m_placePanel->onUpdate(m_renderer);
		m_upgradePanel->onUpdate(m_renderer);
		WaveManager::instance()->onUpdate(delta);
		EnemyManager::instance()->onUpdate(delta);
		CoinManager::instance()->onUpdate(delta);
		BulletManager::instance()->onUpdate(delta);
		TowerManager::instance()->onUpdate(delta);
		PlayerManager::instance()->onUpdate(delta);

		return;
	}

	if (!isGameOverLastTick && instance->m_isGameOver)
	{
		static const ResourcesManager::SoundPool& soundPool = ResourcesManager::instance()->getSoundPool();

		Mix_FadeOutMusic(1500);
		Mix_PlayChannel(-1, soundPool.find(instance->m_isGameWin ? ResID::Sound_Win : ResID::Sound_Loss)->second, 0);
	}

	isGameOverLastTick = instance->m_isGameOver;

	m_banner->onUpdate(delta);
	if (m_banner->checkEndDispaly())
	{
		m_isQuit = true;
	}
}

void GameManager::onRender()
{
	static ConfigManager* instance = ConfigManager::instance();
	static SDL_Rect& rectDst = instance->m_rectTileMap;
	SDL_RenderCopy(m_renderer, m_texTileMap, nullptr, &rectDst);

	EnemyManager::instance()->onRender(m_renderer);
	CoinManager::instance()->onRender(m_renderer);
	BulletManager::instance()->onRender(m_renderer);
	TowerManager::instance()->onRender(m_renderer);
	PlayerManager::instance()->onRender(m_renderer);

	if (!instance->m_isGameOver)
	{
		m_placePanel->onRender(m_renderer);
		m_upgradePanel->onRender(m_renderer);
		m_statusBar.onRender(m_renderer);

		return;
	}

	int widthScreen, heightScreen;
	SDL_GetWindowSizeInPixels(m_window, &widthScreen, &heightScreen);
	m_banner->setCenterPosition({ (double)widthScreen / 2, (double)heightScreen / 2 });
	m_banner->onRender(m_renderer);
}

bool GameManager::generateTileMapTexture()
{
	const Map& map = ConfigManager::instance()->m_map;
	const TileMap& tileMap = map.getTileMap();
	SDL_Rect& rectTileMap = ConfigManager::instance()->m_rectTileMap;
	SDL_Texture* texTileSet = ResourcesManager::instance()->getTexturePool().find(ResID::Tex_Tileset)->second;

	int widthTexTileSet, heightTexTileSet;
	SDL_QueryTexture(texTileSet, nullptr, nullptr, &widthTexTileSet, &heightTexTileSet);
	int numTileSingleLine = (int)std::ceil((double)widthTexTileSet / SIZE_TILE);

	int widthTexTileMap, heightTexTileMap;
	widthTexTileMap = (int)map.getWidth() * SIZE_TILE;
	heightTexTileMap = (int)map.getHeight() * SIZE_TILE;
	m_texTileMap = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, widthTexTileMap, heightTexTileMap);
	if (!m_texTileMap)
	{
		return false;
	}

	ConfigManager* config = ConfigManager::instance();
	rectTileMap.x = (config->m_basicTemplate.m_windowWidth - widthTexTileMap) / 2;
	rectTileMap.y = (config->m_basicTemplate.m_windowHeight - heightTexTileMap) / 2;
	rectTileMap.w = widthTexTileMap;
	rectTileMap.h = heightTexTileMap;

	SDL_SetTextureBlendMode(m_texTileMap, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(m_renderer, m_texTileMap);

	for (int y = 0; y < map.getHeight(); y++)
	{
		for (int x = 0; x < map.getWidth(); x++)
		{
			SDL_Rect rectSrc;
			const Tile& tile = tileMap[y][x];

			const SDL_Rect& rectDst =
			{
				x * SIZE_TILE, y * SIZE_TILE,
				SIZE_TILE, SIZE_TILE
			};

			rectSrc =
			{
				(tile.m_terrian % numTileSingleLine) * SIZE_TILE,
				(tile.m_terrian / numTileSingleLine) * SIZE_TILE,
				SIZE_TILE, SIZE_TILE
			};
			SDL_RenderCopy(m_renderer, texTileSet, &rectSrc, &rectDst);

			if (tile.m_decoration >= 0)
			{
				rectSrc =
				{
					(tile.m_decoration % numTileSingleLine) * SIZE_TILE,
					(tile.m_decoration / numTileSingleLine) * SIZE_TILE,
					SIZE_TILE, SIZE_TILE
				};
				SDL_RenderCopy(m_renderer, texTileSet, &rectSrc, &rectDst);
			}
		}
	}

	const SDL_Point& idxHome = map.getIdxHome();
	const SDL_Rect rectDst =
	{
		idxHome.x * SIZE_TILE, idxHome.y * SIZE_TILE,
		SIZE_TILE, SIZE_TILE
	};
	SDL_RenderCopy(m_renderer, ResourcesManager::instance()->getTexturePool().find(ResID::Tex_Home)->second, nullptr, &rectDst);

	SDL_SetRenderTarget(m_renderer, nullptr);

	return true;
}

bool GameManager::checkHome(const SDL_Point& idxTileSelected)
{
	static const Map& map = ConfigManager::instance()->m_map;
	static const SDL_Point& idxHome = map.getIdxHome();

	return (idxHome.x == idxTileSelected.x && idxHome.y == idxTileSelected.y);
}

bool GameManager::getCursorIdxTile(SDL_Point& idxTileSelected, int screenX, int screenY) const
{
	static const Map& map = ConfigManager::instance()->m_map;
	static const SDL_Rect& rectTileMap = ConfigManager::instance()->m_rectTileMap;

	if (screenX < rectTileMap.x || screenX > rectTileMap.x + rectTileMap.w || screenY < rectTileMap.y || screenY > rectTileMap.x + rectTileMap.h)
	{
		return false;
	}

	idxTileSelected.x = std::min((screenX - rectTileMap.x) / SIZE_TILE, (int)map.getWidth() - 1);
	idxTileSelected.y = std::min((screenY - rectTileMap.y) / SIZE_TILE, (int)map.getHeight() - 1);

	return true;
}

bool GameManager::canPlaceTower(const SDL_Point& idxTileSelected) const
{
	static const Map& map = ConfigManager::instance()->m_map;
	const Tile& tile = map.getTileMap()[idxTileSelected.y][idxTileSelected.x];

	return (tile.m_decoration < 0 && tile.m_direction == Tile::Direction::None && !tile.m_hasTower);
}

void GameManager::getSelectedTileCenterPos(SDL_Point& pos, const SDL_Point& idxTileSelected) const
{
	static const SDL_Rect& rectTileMap = ConfigManager::instance()->m_rectTileMap;

	pos.x = rectTileMap.x + idxTileSelected.x * SIZE_TILE + SIZE_TILE / 2;
	pos.y = rectTileMap.y + idxTileSelected.y * SIZE_TILE + SIZE_TILE / 2;
}