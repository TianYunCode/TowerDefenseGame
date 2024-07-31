#include "../../HeaderFile/manager/game_manager.h"

GameManager::GameManager()
{
	//初始化第三方库
	init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2 初始化失败！");             //初始化SDL2
	init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_imgae 初始化失败！"); //初始化SDL_imgae
	init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer 初始化失败！");                //初始化SDL_mixer
	init_assert(!TTF_Init(), u8"SDL_ttf 初始化失败！");                             //初始化SDL_ttf

	//初始化音频
	//44100------------------频率（以赫兹为单位）播放音频
	//MIX_DEFAULT_FORMAT-----默认音频格式
	//2----------------------通道数量（1是单声道，2是立体声等）
	//2048-------------------样本框架中的块大小音频缓冲区大小（总样本除以通道计数）
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//设置提示（给SDL提供建议）
	//SDL_HINT_IME_SHOW_UI-----控制某些IME是否应显示本机Ul组件（如候选列表）而不是抑制它们的变量
	//"1"----------------------SDL_HINT_IME_SHOW_UI变量的值
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

	ConfigManager* config = ConfigManager::instance();

	init_assert(config->map.load("map.csv"), u8"加载游戏地图失败！");
	init_assert(config->load_level_config("level.json"), u8"加载关卡配置失败！");
	init_assert(config->load_game_config("config.json"), u8"加载游戏配置失败！");

	//创建窗口
	//config->basic_template.window_title.c_str()-----窗口标题
	//SDL_WINDOWPOS_CENTERED--------------------------窗口居中
	//config->basic_template.window_width-------------窗口宽度
	//config->basic_template.window_height------------窗口高度
	//SDL_WINDOW_SHOWN--------------------------------显示窗口
	window = SDL_CreateWindow(config->basic_template.window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		config->basic_template.window_width, config->basic_template.window_height, SDL_WINDOW_SHOWN);
	init_assert(window, u8"创建游戏窗口失败！"); //断言窗口是否创建成功

	//创建渲染器
	//window-------------------------游戏窗口
	//-1-----------------------------初始化的渲染驱动程序的索引，-1表示以初始化支持请求标志的第一个
	//SDL_RENDERER_ACCELERATED-------渲染器加速（硬件加速）
	//SDL_RENDERER_PRESENTVSYNC------垂直同步
	//SDL_RENDERER_TARGETTEXTURE-----目标纹理
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	init_assert(renderer, u8"创建渲染器失败！");//断言渲染器是否创建成功

	init_assert(ResourcesManager::instance()->load_from_file(renderer), u8"加载游戏资源失败！");

	init_assert(generate_tile_map_texture(), u8"生成瓦片地图纹理失败！");

	status_bar.set_position(15, 15);

	banner = new Banner();
	place_panel = new PlacePanel();
	upgrade_panel = new UpgradePanel();
}

GameManager::~GameManager()
{
	SDL_DestroyRenderer(renderer); //销毁渲染器
	SDL_DestroyWindow(window); //销毁窗口

	TTF_Quit(); //退出TTF库
	Mix_Quit(); //退出Mix库
	IMG_Quit(); //退出IMG库
	SDL_Quit(); //退出SDL库
}

int GameManager::run(int argc, char** argv)
{
	Mix_FadeInMusic(ResourcesManager::instance()->get_music_pool().find(ResID::Music_BGM)->second, -1, 1500);

	//获取高分辨率计数器的当前值
	Uint64 last_counter = SDL_GetPerformanceCounter();
	//获取高分辨率计数器的每秒计数
	const Uint64 counter_freq = SDL_GetPerformanceFrequency();

	//如果游戏没有退出
	while (!is_quit)
	{
		//获取事件
		while (SDL_PollEvent(&event))
		{
			on_input();
		}

		////获取高分辨率计数器的当前值
		Uint64 current_counter = SDL_GetPerformanceCounter();
		//获取帧间隔
		double delta = (double)(current_counter - last_counter) / counter_freq;
		last_counter = current_counter;
		//让游戏稳定在60帧
		if (delta * 1000 < 1000.0 / 60) SDL_Delay((Uint32)(1000.0 / 60 - delta * 1000));

		//更新数据
		on_update(delta);

		//以纯黑清空窗口
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		//情况上一帧的内容
		SDL_RenderClear(renderer);

		//绘制画面
		on_render();

		//刷新
		SDL_RenderPresent(renderer);
	}

	return 0;
}

void GameManager::init_assert(bool flag, const char* err_msg)
{
	if (flag) return;

	//弹出一个消息框
	//SDL_MESSAGEBOX_ERROR-----表示是一个error提示框
	//u8"游戏启动失败"----------窗口标题
	//err_msg------------------消息文本
	//window-------------------指定父窗口，设置为NULL表示为非模态窗口
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"游戏启动失败", err_msg, window);
	exit(-1);
}

void GameManager::on_input()
{
	static SDL_Point pos_center;
	static SDL_Point idx_tile_selected;
	static ConfigManager* instance = ConfigManager::instance();

	switch (event.type)
	{
	case SDL_QUIT:
		is_quit = true;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (instance->is_game_over) break;
		if (get_cursor_idx_tile(idx_tile_selected, event.motion.x, event.motion.y))
		{
			get_selected_tile_center_pos(pos_center, idx_tile_selected);

			if (check_home(idx_tile_selected))
			{
				upgrade_panel->set_idx_tile(idx_tile_selected);
				upgrade_panel->set_center_pos(pos_center);
				upgrade_panel->show();
			}
			else if (can_place_tower(idx_tile_selected))
			{
				place_panel->set_idx_tile(idx_tile_selected);
				place_panel->set_center_pos(pos_center);
				place_panel->show();
			}
		}
		break;
	default:
		break;
	}

	if (!instance->is_game_over)
	{
		place_panel->on_input(event);
		upgrade_panel->on_input(event);
		PlayerManager::instance()->on_input(event);
	}
}

void GameManager::on_update(double delta)
{
	static bool is_game_over_last_tick = false;
	static ConfigManager* instance = ConfigManager::instance();

	if (!instance->is_game_over)
	{
		status_bar.on_update(renderer);
		place_panel->on_update(renderer);
		upgrade_panel->on_update(renderer);
		WaveManager::instance()->on_update(delta);
		EnemyManager::instance()->on_update(delta);
		CoinManager::instance()->on_update(delta);
		BulletManager::instance()->on_update(delta);
		TowerManager::instance()->on_update(delta);
		PlayerManager::instance()->on_update(delta);

		return;
	}

	if (!is_game_over_last_tick && instance->is_game_over)
	{
		static const ResourcesManager::SoundPool& sound_pool = ResourcesManager::instance()->get_sound_pool();

		Mix_FadeOutMusic(1500);
		Mix_PlayChannel(-1, sound_pool.find(instance->is_game_win ? ResID::Sound_Win : ResID::Sound_Loss)->second, 0);
	}

	is_game_over_last_tick = instance->is_game_over;

	banner->on_update(delta);
	if (banner->check_end_dispaly()) is_quit = true;
}

void GameManager::on_render()
{
	static ConfigManager* instance = ConfigManager::instance();
	static SDL_Rect& rect_dst = instance->rect_tile_map;
	SDL_RenderCopy(renderer, tex_tile_map, nullptr, &rect_dst);

	EnemyManager::instance()->on_render(renderer);
	CoinManager::instance()->on_render(renderer);
	BulletManager::instance()->on_render(renderer);
	TowerManager::instance()->on_render(renderer);
	PlayerManager::instance()->on_render(renderer);

	if (!instance->is_game_over)
	{
		place_panel->on_render(renderer);
		upgrade_panel->on_render(renderer);
		status_bar.on_render(renderer);

		return;
	}

	int width_screen, height_screen;
	SDL_GetWindowSizeInPixels(window, &width_screen, &height_screen);
	banner->set_center_position({ (double)width_screen / 2, (double)height_screen / 2 });
	banner->on_render(renderer);
}

bool GameManager::generate_tile_map_texture()
{
	const Map& map = ConfigManager::instance()->map;
	const TileMap& tile_map = map.get_tile_map();
	SDL_Rect& rect_tile_map = ConfigManager::instance()->rect_tile_map;
	SDL_Texture* tex_tile_set = ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Tileset)->second;

	int width_tex_tile_set, height_tex_tile_set;
	SDL_QueryTexture(tex_tile_set, nullptr, nullptr, &width_tex_tile_set, &height_tex_tile_set);
	int num_tile_single_line = (int)ceil((double)width_tex_tile_set / SIZE_TILE);

	int width_tex_tile_map, height_tex_tile_map;
	width_tex_tile_map = (int)map.get_width() * SIZE_TILE;
	height_tex_tile_map = (int)map.get_height() * SIZE_TILE;
	tex_tile_map = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width_tex_tile_map, height_tex_tile_map);
	if (!tex_tile_map) return false;

	ConfigManager* config = ConfigManager::instance();
	rect_tile_map.x = (config->basic_template.window_width - width_tex_tile_map) / 2;
	rect_tile_map.y = (config->basic_template.window_height - height_tex_tile_map) / 2;
	rect_tile_map.w = width_tex_tile_map;
	rect_tile_map.h = height_tex_tile_map;

	SDL_SetTextureBlendMode(tex_tile_map, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, tex_tile_map);

	for (int y = 0; y < map.get_height(); y++)
	{
		for (int x = 0; x < map.get_width(); x++)
		{
			SDL_Rect rect_src;
			const Tile& tile = tile_map[y][x];

			const SDL_Rect& rect_dst =
			{
				x * SIZE_TILE, y * SIZE_TILE,
				SIZE_TILE, SIZE_TILE
			};

			rect_src =
			{
				(tile.terrian % num_tile_single_line) * SIZE_TILE,
				(tile.terrian / num_tile_single_line) * SIZE_TILE,
				SIZE_TILE, SIZE_TILE
			};
			SDL_RenderCopy(renderer, tex_tile_set, &rect_src, &rect_dst);

			if (tile.decoration >= 0)
			{
				rect_src =
				{
					(tile.decoration % num_tile_single_line) * SIZE_TILE,
					(tile.decoration / num_tile_single_line) * SIZE_TILE,
					SIZE_TILE, SIZE_TILE
				};
				SDL_RenderCopy(renderer, tex_tile_set, &rect_src, &rect_dst);
			}
		}
	}

	const SDL_Point& idx_home = map.get_idx_home();
	const SDL_Rect rect_dst =
	{
		idx_home.x * SIZE_TILE, idx_home.y * SIZE_TILE,
		SIZE_TILE, SIZE_TILE
	};
	SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Home)->second, nullptr, &rect_dst);

	SDL_SetRenderTarget(renderer, nullptr);

	return true;
}

bool GameManager::check_home(const SDL_Point& idx_tile_selected)
{
	static const Map& map = ConfigManager::instance()->map;
	static const SDL_Point& idx_home = map.get_idx_home();

	return (idx_home.x == idx_tile_selected.x && idx_home.y == idx_tile_selected.y);
}

bool GameManager::get_cursor_idx_tile(SDL_Point& idx_tile_selected, int screen_x, int screen_y) const
{
	static const Map& map = ConfigManager::instance()->map;
	static const SDL_Rect& rect_tile_map = ConfigManager::instance()->rect_tile_map;

	if (screen_x < rect_tile_map.x || screen_x > rect_tile_map.x + rect_tile_map.w
		|| screen_y	 < rect_tile_map.y || screen_y > rect_tile_map.x + rect_tile_map.h) return false;

	idx_tile_selected.x = min((screen_x - rect_tile_map.x) / SIZE_TILE, (int)map.get_width() - 1);
	idx_tile_selected.y = min((screen_y - rect_tile_map.y) / SIZE_TILE, (int)map.get_height() - 1);

	return true;
}

bool GameManager::can_place_tower(const SDL_Point& idx_tile_selected) const
{
	static const Map& map = ConfigManager::instance()->map;
	const Tile& tile = map.get_tile_map()[idx_tile_selected.y][idx_tile_selected.x];

	return (tile.decoration < 0 && tile.direction == Tile::Direction::None && !tile.has_tower);
}

void GameManager::get_selected_tile_center_pos(SDL_Point& pos, const SDL_Point& idx_tile_selected) const
{
	static const SDL_Rect& rect_tile_map = ConfigManager::instance()->rect_tile_map;

	pos.x = rect_tile_map.x + idx_tile_selected.x * SIZE_TILE + SIZE_TILE / 2;
	pos.y = rect_tile_map.y + idx_tile_selected.y * SIZE_TILE + SIZE_TILE / 2;
}