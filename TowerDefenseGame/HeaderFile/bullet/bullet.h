#ifndef _BULLET_H_
#define _BULLET_H_

#include "two_vector.h"
#include "enemy.h"
#include "animation.h"
#include "config_manager.h"

//子弹基类
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

	void disable_collide();	  //禁用碰撞
	bool can_collide() const; //可以碰撞

	void make_invalid();	 //子弹无效化
	bool can_remove() const; //是否可以移除子弹

	virtual void on_update(double delta);
	virtual void on_render(SDL_Renderer* renderer);
	virtual void on_collide(Enemy* enemy);

protected:
	TwoVector size;		//尺寸
	TwoVector velocity;	//飞行速度
	TwoVector position; //位置

	Animation animation;
	bool can_rotated = false; //是否可以旋转

	double damage = 0;		  //伤害
	double damage_range = -1; //伤害范围

private:
	bool is_valid = true;		   //当前的子弹是否还有效
	bool is_collisional = true;	   //子弹是否可以发生碰撞
	double angle_anim_rotated = 0; //动画旋转角度
};

#endif