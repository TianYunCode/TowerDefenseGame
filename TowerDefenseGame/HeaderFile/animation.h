#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "timer.h"

#include <SDL.h>
#include <vector>
#include <functional>

//������
class Animation
{
public:
	typedef function<void()> PlayCallback; //���Żص�

public:
	Animation();
	~Animation() = default;

	void reset();

	void set_frame_data(SDL_Texture* texture, int num_h, int num_v, const vector<int>& idx_list);
	void set_loop(bool is_loop);					//�����Ƿ�ѭ������
	void set_interval(double interval);				//����֡���
	void set_on_finished(PlayCallback on_finished); //���ûص�����

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer, const SDL_Point& pos_dst, double angle = 0) const
	{
		static SDL_Rect rect_dst;

		rect_dst.x = pos_dst.x, rect_dst.y = pos_dst.y;
		rect_dst.w = width_frame, rect_dst.h = height_frame;

		SDL_RenderCopyEx(renderer, texture, &rect_src_list[idx_frame], &rect_dst, angle, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	}

private:
	Timer timer;						   //��ʱ��
	bool is_loop = true;				   //�Ƿ�ѭ������
	size_t idx_frame = 0;				   //֡����
	PlayCallback on_finished;			   //�������Ž����ص�����
	SDL_Texture* texture = nullptr;		   //���ŵ�����
	vector<SDL_Rect> rect_src_list;		   //ԭ�����б�
	int width_frame = 0, height_frame = 0; //Ŀ����εĿ��
};

#endif