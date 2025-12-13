#include "Animation.h"

Animation::Animation()
{
	m_timer.setOneShot(false);
	m_timer.setOnTimeout([&]()
		{
			m_idxFrame++;
			if (m_idxFrame >= m_rectSrcList.size())
			{
				m_idxFrame = m_isLoop ? 0 : m_rectSrcList.size() - 1;
				if (!m_isLoop && m_onFinished)
				{
					m_onFinished();
				}
			}
		}
	);
}

void Animation::reset()
{
	m_timer.restart();

	m_idxFrame = 0;
}

void Animation::setFrameData(SDL_Texture* texture, int numH, int numV, const std::vector<int>& idxList)
{
	int widthTex, heightTex;

	this->m_texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &widthTex, &heightTex);
	m_widthFrame = widthTex / numH, m_heightFrame = heightTex / numV;

	m_rectSrcList.resize(idxList.size());
	for (size_t i = 0; i < idxList.size(); i++)
	{
		int idx = idxList[i];
		SDL_Rect& rectSrc = m_rectSrcList[i];

		rectSrc.x = (idx % numH) * m_widthFrame;
		rectSrc.y = (idx / numH) * m_heightFrame;
		rectSrc.w = m_widthFrame, rectSrc.h = m_heightFrame;
	}
}

void Animation::setLoop(bool isLoop)
{
	this->m_isLoop = isLoop;
}

void Animation::setInterval(double interval)
{
	m_timer.setWaitTime(interval);
}

void Animation::setOnFinished(PlayCallback onFinished)
{
	this->m_onFinished = onFinished;
}

void Animation::onUpdate(double delta)
{
	m_timer.onUpdate(delta);
}

void Animation::onRender(SDL_Renderer* renderer, const SDL_Point& posDst, double angle) const
{
	static SDL_Rect rectDst;

	rectDst.x = posDst.x, rectDst.y = posDst.y;
	rectDst.w = m_widthFrame, rectDst.h = m_heightFrame;

	SDL_RenderCopyEx(renderer, m_texture, &m_rectSrcList[m_idxFrame], &rectDst, angle, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
}