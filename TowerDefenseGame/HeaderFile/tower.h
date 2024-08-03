#ifndef _TOWER_H_
#define _TOWER_H_

#include "facing.h"
#include "two_vector.h"
#include "animation.h"
#include "tower_type.h"
#include "enemy_manager.h"
#include "bullet_manager.h"

class Tower
{
public:
	Tower();
	~Tower() = default;

	void set_position(const TwoVector& position);

	const TwoVector& get_size() const;
	const TwoVector& get_position() const;

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

protected:
	TwoVector size;

	Animation anim_idle_up;
	Animation anim_idle_down;
	Animation anim_idle_left;
	Animation anim_idle_right;
	Animation anim_fire_up;
	Animation anim_fire_down;
	Animation anim_fire_left;
	Animation anim_fire_right;

	TowerType tower_type = TowerType::Archer;

	double fire_speed = 0;
	BulletType bullet_type = BulletType::Arrow;

private:
	Timer timer_fire;
	TwoVector position;
	bool can_fire = true;
	Facing facing = Facing::Right;
	Animation* anim_current = &anim_idle_right;

private:
	void update_idle_animation();
	void update_fire_animation();

	Enemy* find_target_enemy();

	void on_fire();
};

#endif