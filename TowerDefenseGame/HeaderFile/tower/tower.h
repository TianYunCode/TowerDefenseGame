#ifndef _TOWER_H_
#define _TOWER_H_

#include "facing.h"
#include "two_vector.h"
#include "animation.h"
#include "tower_type.h"
#include "enemy_manager.h"
#include "bullet_manager.h"

//防御塔基类
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
	TwoVector size; //尺寸

	Animation anim_idle_up;	   //待机时，上
	Animation anim_idle_down;  //待机时，下
	Animation anim_idle_left;  //待机时，左
	Animation anim_idle_right; //待机时，右

	Animation anim_fire_up;	   //开火时，上
	Animation anim_fire_down;  //开火时，上
	Animation anim_fire_left;  //开火时，上
	Animation anim_fire_right; //开火时，上

	TowerType tower_type = TowerType::Archer; //防御塔，默认是弓箭手

	double fire_speed = 0; //攻击速度
	BulletType bullet_type = BulletType::Arrow; //攻击的子弹，默认是箭

private:
	Timer timer_fire;							//攻击的时间间隔
	TwoVector position;							//事件坐标位置
	bool can_fire = true;						//当前这一帧是否可以攻击
	Facing facing = Facing::Right;				//防御塔正面朝向
	Animation* anim_current = &anim_idle_right; //当前动画

private:
	void update_idle_animation(); //更新待机动画
	void update_fire_animation(); //更新开火动画

	Enemy* find_target_enemy(); //找到目标敌人

	void on_fire(); //开火
};

#endif