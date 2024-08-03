#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "timer.h"
#include "route.h"
#include "two_vector.h"
#include "animation.h"
#include "config_manager.h"

#include <functional>

//���˻���
class Enemy
{
public:
	typedef function<void(Enemy* enemy)> SkillCallback; //���ܻص�����

public:
	Enemy();
	~Enemy() = default;

	void on_update(double delta);								 //֡����
	void on_render(SDL_Renderer* renderer);						 //��Ⱦ��ͼ
	void set_on_skill_released(SkillCallback on_skill_released); //���ü��ܻص�

	void increase_hp(double val); //��������ֵ
	void decrease_hp(double val); //��������ֵ

	void slow_down(); //����

	void set_position(const TwoVector& position); //����λ��
	void set_route(const Route* route);			  //����·��

	void make_invalid();   //��������ʱ��������ʧ
	double get_hp() const; //��ȡ����ֵ

	const TwoVector& get_size() const;	   //��ȡ��С
	const TwoVector& get_position() const; //��ȡλ��
	const TwoVector& get_velocity() const; //��ȡ�ٶ�

	double get_damage() const;			  //��ȡ�˺�
	double get_reward_ratio() const;	  //��ý�ұ���
	double get_recover_radius() const;    //��ȡ�ظ���Χ
	double get_recover_intensity() const; //��ȡ�ظ�ǿ��

	bool can_remove() const;		  //�жϵ����Ƿ�����Ƴ�
	double get_route_process() const; //��ȡ·������

protected:
	TwoVector size; //���˴�С

	Timer timer_skill; //��ʱ��

	Animation anim_up;			 //����������
	Animation anim_down;		 //����������
	Animation anim_left;		 //����������
	Animation anim_right;		 //����������
	Animation anim_up_sketch;	 //��������������
	Animation anim_down_sketch;  //��������������
	Animation anim_left_sketch;  //��������������
	Animation anim_right_sketch; //��������������

	double hp = 0;				  //��ǰѪ��
	double max_hp = 0;			  //���Ѫ��
	double speed = 0;			  //��ǰ�ƶ��ٶ�
	double max_speed = 0;		  //����ƶ��ٶ�
	double damage = 0;			  //����Է���Ŀ����ɵ��˺�
	double reward_ratio = 0;	  //����ҵĸ���
	double recover_interval = 0;  //�ظ����ܵ�CD
	double recover_range = 0;	  //�ظ����ܵķ�Χ
	double recover_intensity = 0; //�ظ����ܵ�ǿ��

private:
	TwoVector position;  //λ��
	TwoVector velocity;  //�ٶ�
	TwoVector direction; //����

	bool is_valid = true; //�����Ƿ񱻻�ɱ

	Timer timer_sketch;			 //�ܵ��˺��������裬��һ��ʱ�������Ч�����ܻ���Ч��
	bool is_show_sketch = false; //�Ƿ�չʾ����

	Animation* anim_current = nullptr; //��¼��ǰ�ڽ����ĸ�����

	SkillCallback on_skill_released; //���ܻص�

	Timer timer_restore_speed; //�ܵ����ٺ�ָ������ٶȵ�ʱ��

	const Route* route = nullptr; //���ߵ�·��
	int idx_target = 0;			  //��ǰ�ߵ��ĵ�Ԫ��
	TwoVector position_target;	  //λ��Ŀ��

private:
	void refresh_position_target(); //����Ŀ���λ��
};

#endif