#ifndef _BULLET_H_
#define _BULLET_H_

#include "two_vector.h"
#include "enemy.h"
#include "animation.h"
#include "config_manager.h"

//�ӵ�����
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

	void disable_collide();	  //������ײ
	bool can_collide() const; //������ײ

	void make_invalid();	 //�ӵ���Ч��
	bool can_remove() const; //�Ƿ�����Ƴ��ӵ�

	virtual void on_update(double delta);
	virtual void on_render(SDL_Renderer* renderer);
	virtual void on_collide(Enemy* enemy);

protected:
	TwoVector size;		//�ߴ�
	TwoVector velocity;	//�����ٶ�
	TwoVector position; //λ��

	Animation animation;
	bool can_rotated = false; //�Ƿ������ת

	double damage = 0;		  //�˺�
	double damage_range = -1; //�˺���Χ

private:
	bool is_valid = true;		   //��ǰ���ӵ��Ƿ���Ч
	bool is_collisional = true;	   //�ӵ��Ƿ���Է�����ײ
	double angle_anim_rotated = 0; //������ת�Ƕ�
};

#endif