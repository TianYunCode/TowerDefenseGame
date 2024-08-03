#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "timer.h"

#include <SDL.h>
#include <vector>
#include <functional>

//动画类
class Animation
{
public:
	typedef function<void()> PlayCallback; //播放回调

public:
	Animation();
	~Animation() = default;

	void reset();

	void set_frame_data(SDL_Texture* texture, int num_h, int num_v, const vector<int>& idx_list);
	void set_loop(bool is_loop);					//设置是否循环播放
	void set_interval(double interval);				//设置帧间隔
	void set_on_finished(PlayCallback on_finished); //设置回调函数

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer, const SDL_Point& pos_dst, double angle = 0) const
	{
		static SDL_Rect rect_dst;

		rect_dst.x = pos_dst.x, rect_dst.y = pos_dst.y;
		rect_dst.w = width_frame, rect_dst.h = height_frame;

		SDL_RenderCopyEx(renderer, texture, &rect_src_list[idx_frame], &rect_dst, angle, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	}

private:
	Timer timer;						   //计时器
	bool is_loop = true;				   //是否循环播放
	size_t idx_frame = 0;				   //帧索引
	PlayCallback on_finished;			   //动画播放结束回调函数
	SDL_Texture* texture = nullptr;		   //播放的纹理
	vector<SDL_Rect> rect_src_list;		   //原矩形列表
	int width_frame = 0, height_frame = 0; //目标矩形的宽高
};

#endif