#ifndef _BULLET_H_
#define _BULLET_H_

#include "two_vector.h"
#include "enemy.h"
#include "animation.h"
#include "config_manager.h"

class Bullet
{
public:
	Bullet() = default;
	~Bullet() = default;

	void set_velocity(const TwoVector& velocity);
	void set_position(const TwoVector& position);
	void set_damage(double damage);

	const TwoVector& get_size() const;
	const TwoVector& get_position() const;

	double get_damage() const;
	double get_damage_range() const;

	void disable_collide();
	bool can_collide() const;

	void make_invalid();
	bool can_remove() const;

	virtual void on_update(double delta);
	virtual void on_render(SDL_Renderer* renderer);
	virtual void on_collide(Enemy* enemy);

protected:
	TwoVector size;
	TwoVector velocity;
	TwoVector position;

	Animation animation;
	bool can_rotated = false;

	double damage = 0;
	double damage_range = -1;

private:
	bool is_valid = true;
	bool is_collisional = true;
	double angle_anim_rotated = 0;
};

#endif