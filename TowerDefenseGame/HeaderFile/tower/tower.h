#ifndef _TOWER_H_
#define _TOWER_H_

#include "facing.h"
#include "two_vector.h"
#include "animation.h"
#include "tower_type.h"
#include "enemy_manager.h"
#include "bullet_manager.h"

//����������
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
	TwoVector size; //�ߴ�

	Animation anim_idle_up;	   //����ʱ����
	Animation anim_idle_down;  //����ʱ����
	Animation anim_idle_left;  //����ʱ����
	Animation anim_idle_right; //����ʱ����

	Animation anim_fire_up;	   //����ʱ����
	Animation anim_fire_down;  //����ʱ����
	Animation anim_fire_left;  //����ʱ����
	Animation anim_fire_right; //����ʱ����

	TowerType tower_type = TowerType::Archer; //��������Ĭ���ǹ�����

	double fire_speed = 0; //�����ٶ�
	BulletType bullet_type = BulletType::Arrow; //�������ӵ���Ĭ���Ǽ�

private:
	Timer timer_fire;							//������ʱ����
	TwoVector position;							//�¼�����λ��
	bool can_fire = true;						//��ǰ��һ֡�Ƿ���Թ���
	Facing facing = Facing::Right;				//���������泯��
	Animation* anim_current = &anim_idle_right; //��ǰ����

private:
	void update_idle_animation(); //���´�������
	void update_fire_animation(); //���¿��𶯻�

	Enemy* find_target_enemy(); //�ҵ�Ŀ�����

	void on_fire(); //����
};

#endif