#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "timer.h"
#include "route.h"
#include "two_vector.h"
#include "animation.h"
#include "config_manager.h"

#include <functional>

//敌人基类
class Enemy
{
public:
	typedef function<void(Enemy* enemy)> SkillCallback; //技能回调函数

public:
	Enemy();
	~Enemy() = default;

	void on_update(double delta);								 //帧更新
	void on_render(SDL_Renderer* renderer);						 //渲染绘图
	void set_on_skill_released(SkillCallback on_skill_released); //设置技能回调

	void increase_hp(double val); //增加生命值
	void decrease_hp(double val); //减少生命值

	void slow_down(); //减速

	void set_position(const TwoVector& position); //设置位置
	void set_route(const Route* route);			  //设置路径

	void make_invalid();   //碰触房屋时，敌人消失
	double get_hp() const; //获取生命值

	const TwoVector& get_size() const;	   //获取大小
	const TwoVector& get_position() const; //获取位置
	const TwoVector& get_velocity() const; //获取速度

	double get_damage() const;			  //获取伤害
	double get_reward_ratio() const;	  //获得金币爆率
	double get_recover_radius() const;    //获取回复范围
	double get_recover_intensity() const; //获取回复强度

	bool can_remove() const;		  //判断敌人是否可以移除
	double get_route_process() const; //获取路线流程

protected:
	TwoVector size; //敌人大小

	Timer timer_skill; //计时器

	Animation anim_up;			 //动画，向上
	Animation anim_down;		 //动画，向下
	Animation anim_left;		 //动画，向左
	Animation anim_right;		 //动画，向右
	Animation anim_up_sketch;	 //动画，向上素描
	Animation anim_down_sketch;  //动画，向下素描
	Animation anim_left_sketch;  //动画，向左素描
	Animation anim_right_sketch; //动画，向右素描

	double hp = 0;				  //当前血量
	double max_hp = 0;			  //最大血量
	double speed = 0;			  //当前移动速度
	double max_speed = 0;		  //最高移动速度
	double damage = 0;			  //怪物对防守目标造成的伤害
	double reward_ratio = 0;	  //爆金币的概率
	double recover_interval = 0;  //回复技能的CD
	double recover_range = 0;	  //回复技能的范围
	double recover_intensity = 0; //回复技能的强度

private:
	TwoVector position;  //位置
	TwoVector velocity;  //速度
	TwoVector direction; //方向

	bool is_valid = true; //敌人是否被击杀

	Timer timer_sketch;			 //受到伤害后，贴素描，有一段时间的闪白效果（受击特效）
	bool is_show_sketch = false; //是否展示素描

	Animation* anim_current = nullptr; //记录当前在进行哪个动画

	SkillCallback on_skill_released; //技能回调

	Timer timer_restore_speed; //受到减速后恢复正常速度的时间

	const Route* route = nullptr; //行走的路径
	int idx_target = 0;			  //当前走到的单元格
	TwoVector position_target;	  //位置目标

private:
	void refresh_position_target(); //更新目标点位置
};

#endif