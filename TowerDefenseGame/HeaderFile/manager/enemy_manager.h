#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include "../enemy/enemy.h"
#include "manager.h"
#include "config_manager.h"
#include "home_manager.h"
#include "../enemy/slim_enemy.h"
#include "../enemy/king_slim_enemy.h"
#include "../enemy/skeleton_enemy.h"
#include "../enemy/goblin_enemy.h"
#include "../enemy/goblin_priest_enemy.h"
#include "../manager/bullet_manager.h"
#include "../manager/coin_manager.h"

#include <vector>
#include <SDL.h>

class EnemyManager : public Manager<EnemyManager>
{
	friend class Manager<EnemyManager>;

public:
	typedef std::vector<Enemy*> EnemyList;

public:
	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

	void spawn_enemy(EnemyType type, int idx_spawn_point);
	bool check_cleared();

	EnemyManager::EnemyList& get_enemy_list();

protected:
	EnemyManager() = default;

	~EnemyManager();

private:
	EnemyList enemy_list;

private:
	void process_home_collision();
	void process_bullet_collision();
	void remove_invalid_enemy();
	void try_spawn_coin_prop(const Vector2& position, double ratio);
};

#endif