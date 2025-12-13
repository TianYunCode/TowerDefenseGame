#pragma once

#include "Timer.h"

#include <SDL.h>
#include <vector>
#include <functional>

class Animation
{
public:
	typedef std::function<void()> PlayCallback;

public:
	Animation();
	~Animation() = default;

	void reset();

	void setFrameData(SDL_Texture* texture, int numH, int numV, const std::vector<int>& idxList);
	void setLoop(bool isLoop);
	void setInterval(double interval);
	void setOnFinished(PlayCallback onFinished);

	void onUpdate(double delta);
	void onRender(SDL_Renderer* renderer, const SDL_Point& posDst, double angle = 0) const;

private:
	Timer m_timer;
	bool m_isLoop = true;
	size_t m_idxFrame = 0;
	PlayCallback m_onFinished;
	SDL_Texture* m_texture = nullptr;
	std::vector<SDL_Rect> m_rectSrcList;
	int m_widthFrame = 0;
	int m_heightFrame = 0;
};
