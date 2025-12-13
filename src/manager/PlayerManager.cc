#include "PlayerManager.h"

PlayerManager::PlayerManager()
{
	m_timerAutoIncreaseMp.setOneShot(false);
	m_timerAutoIncreaseMp.setWaitTime(0.1);
	m_timerAutoIncreaseMp.setOnTimeout([&]()
		{
			double interval = ConfigManager::instance()->m_playerTemplate.m_skillInterval;
			m_mp = std::min(m_mp + 100 / (interval / 0.1), 100.0);
		});

	m_timerReleaseFlashCd.setOneShot(true);
	m_timerReleaseFlashCd.setWaitTime(ConfigManager::instance()->m_playerTemplate.m_skillInterval);
	m_timerReleaseFlashCd.setOnTimeout([&]() { m_canReleaseFlash = true; });

	const ResourcesManager::TexturePool& tex_pool = ResourcesManager::instance()->getTexturePool();

	SDL_Texture* tex_player = tex_pool.find(ResID::Tex_Player)->second;

	m_animIdleUp.setLoop(true); m_animIdleUp.setInterval(0.1);
	m_animIdleUp.setFrameData(tex_player, 4, 8, { 4, 5, 6, 7 });
	m_animIdleDown.setLoop(true); m_animIdleDown.setInterval(0.1);
	m_animIdleDown.setFrameData(tex_player, 4, 8, { 0, 1, 2, 3 });
	m_animIdleLeft.setLoop(true); m_animIdleLeft.setInterval(0.1);
	m_animIdleLeft.setFrameData(tex_player, 4, 8, { 8, 9, 10, 11 });
	m_animIdleRight.setLoop(true); m_animIdleRight.setInterval(0.1);
	m_animIdleRight.setFrameData(tex_player, 4, 8, { 12, 13, 14, 15 });

	m_animAttackUp.setLoop(true); m_animAttackUp.setInterval(0.1);
	m_animAttackUp.setFrameData(tex_player, 4, 8, { 20, 21 });
	m_animAttackDown.setLoop(true); m_animAttackDown.setInterval(0.1);
	m_animAttackDown.setFrameData(tex_player, 4, 8, { 16, 17 });
	m_animAttackLeft.setLoop(true); m_animAttackLeft.setInterval(0.1);
	m_animAttackLeft.setFrameData(tex_player, 4, 8, { 24, 25 });
	m_animAttackRight.setLoop(true); m_animAttackRight.setInterval(0.1);
	m_animAttackRight.setFrameData(tex_player, 4, 8, { 28, 29 });

	m_animEffectFlashUp.setLoop(false); m_animEffectFlashUp.setInterval(0.1);
	m_animEffectFlashUp.setFrameData(tex_pool.find(ResID::Tex_EffectFlash_Up)->second, 5, 1, { 0, 1, 2, 3, 4 });
	m_animEffectFlashUp.setOnFinished([&]() { m_isReleasingFlash = false; });
	m_animEffectFlashDown.setLoop(false); m_animEffectFlashDown.setInterval(0.1);
	m_animEffectFlashDown.setFrameData(tex_pool.find(ResID::Tex_EffectFlash_Down)->second, 5, 1, { 4, 3, 2, 1, 0 });
	m_animEffectFlashDown.setOnFinished([&]() { m_isReleasingFlash = false; });
	m_animEffectFlashLeft.setLoop(false); m_animEffectFlashLeft.setInterval(0.1);
	m_animEffectFlashLeft.setFrameData(tex_pool.find(ResID::Tex_EffectFlash_Left)->second, 1, 5, { 4, 3, 2, 1, 0 });
	m_animEffectFlashLeft.setOnFinished([&]() { m_isReleasingFlash = false; });
	m_animEffectFlashRight.setLoop(false); m_animEffectFlashRight.setInterval(0.1);
	m_animEffectFlashRight.setFrameData(tex_pool.find(ResID::Tex_EffectFlash_Right)->second, 1, 5, { 0, 1, 2, 3, 4 });
	m_animEffectFlashRight.setOnFinished([&]() { m_isReleasingFlash = false; });

	m_animEffectImpactUp.setLoop(false); m_animEffectImpactUp.setInterval(0.1);
	m_animEffectImpactUp.setFrameData(tex_pool.find(ResID::Tex_EffectImpact_Up)->second, 5, 1, { 0, 1, 2, 3, 4 });
	m_animEffectImpactUp.setOnFinished([&]() { m_isReleasingImpact = false; });
	m_animEffectImpactDown.setLoop(false); m_animEffectImpactDown.setInterval(0.1);
	m_animEffectImpactDown.setFrameData(tex_pool.find(ResID::Tex_EffectImpact_Down)->second, 5, 1, { 4, 3, 2, 1, 0 });
	m_animEffectImpactDown.setOnFinished([&]() { m_isReleasingImpact = false; });
	m_animEffectImpactLeft.setLoop(false); m_animEffectImpactLeft.setInterval(0.1);
	m_animEffectImpactLeft.setFrameData(tex_pool.find(ResID::Tex_EffectImpact_Left)->second, 1, 5, { 4, 3, 2, 1, 0 });
	m_animEffectImpactLeft.setOnFinished([&]() { m_isReleasingImpact = false; });
	m_animEffectImpactRight.setLoop(false); m_animEffectImpactRight.setInterval(0.1);
	m_animEffectImpactRight.setFrameData(tex_pool.find(ResID::Tex_EffectImpact_Right)->second, 1, 5, { 0, 1, 2, 3, 4 });
	m_animEffectImpactRight.setOnFinished([&]() { m_isReleasingImpact = false; });

	const SDL_Rect& rectMap = ConfigManager::instance()->m_rectTileMap;
	m_position.m_x = rectMap.x + rectMap.w / 2;
	m_position.m_y = rectMap.y + rectMap.h / 2;

	m_speed = ConfigManager::instance()->m_playerTemplate.m_speed;

	m_size.m_x = 96, m_size.m_y = 96;
}

void PlayerManager::onInput(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			m_isMoveLeft = true;
			break;
		case SDLK_d:
			m_isMoveRight = true;
			break;
		case SDLK_w:
			m_isMoveUp = true;
			break;
		case SDLK_s:
			m_isMoveDown = true;
			break;
		case SDLK_j:
			onReleaseFlash();
			break;
		case SDLK_k:
			onReleaseImpact();
			break;
		default:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			m_isMoveLeft = false;
			break;
		case SDLK_d:
			m_isMoveRight = false;
			break;
		case SDLK_w:
			m_isMoveUp = false;
			break;
		case SDLK_s:
			m_isMoveDown = false;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void PlayerManager::onUpdate(double delta)
{
	m_timerAutoIncreaseMp.onUpdate(delta);
	m_timerReleaseFlashCd.onUpdate(delta);

	TwoVector direction = TwoVector(m_isMoveRight - m_isMoveLeft, m_isMoveDown - m_isMoveUp).normalize();
	m_velocity = direction * m_speed * SIZE_TILE;

	if (!m_isReleasingFlash && !m_isReleasingImpact)
	{
		m_position += m_velocity * delta;

		const SDL_Rect& rectMap = ConfigManager::instance()->m_rectTileMap;
		if (m_position.m_x < rectMap.x)
		{
			m_position.m_x = rectMap.x;
		}

		if (m_position.m_x > rectMap.x + rectMap.w)
		{
			m_position.m_x = rectMap.x + rectMap.w;
		}

		if (m_position.m_y < rectMap.y)
		{
			m_position.m_y = rectMap.y;
		}

		if (m_position.m_y > rectMap.y + rectMap.h)
		{
			m_position.m_y = rectMap.y + rectMap.h;
		}

		if (m_velocity.m_y > 0)
		{
			m_facing = Facing::Down;
		}

		if (m_velocity.m_y < 0)
		{
			m_facing = Facing::Up;
		}

		if (m_velocity.m_x > 0)
		{
			m_facing = Facing::Right;
		}

		if (m_velocity.m_x < 0)
		{
			m_facing = Facing::Left;
		}

		switch (m_facing)
		{
		case Facing::Left:
			m_animCurrent = &m_animIdleLeft;
			break;
		case Facing::Right:
			m_animCurrent = &m_animIdleRight;
			break;
		case Facing::Up:
			m_animCurrent = &m_animIdleUp;
			break;
		case Facing::Down:
			m_animCurrent = &m_animIdleDown;
			break;
		}
	}
	else
	{
		switch (m_facing)
		{
		case Facing::Left:
			m_animCurrent = &m_animAttackLeft;
			break;
		case Facing::Right:
			m_animCurrent = &m_animAttackRight;
			break;
		case Facing::Up:
			m_animCurrent = &m_animAttackUp;
			break;
		case Facing::Down:
			m_animCurrent = &m_animAttackDown;
			break;
		}
	}

	m_animCurrent->onUpdate(delta);

	if (m_isReleasingFlash)
	{
		m_animEffectFlashCurrent->onUpdate(delta);

		EnemyManager::EnemyList& enemyList = EnemyManager::instance()->getEnemyList();
		for (Enemy* enemy : enemyList)
		{
			if (enemy->canRemove())
			{
				continue;
			}

			const TwoVector& position = enemy->getPosition();
			if (position.m_x >= m_rectHitboxFlash.x
				&& position.m_x <= m_rectHitboxFlash.x + m_rectHitboxFlash.w
				&& position.m_y >= m_rectHitboxFlash.y
				&& position.m_y <= m_rectHitboxFlash.y + m_rectHitboxFlash.h)
			{
				enemy->decreaseHp(ConfigManager::instance()->m_playerTemplate.m_normalAttackDamage * delta);
			}
		}
	}

	if (m_isReleasingImpact)
	{
		m_animEffectImpactCurrent->onUpdate(delta);

		EnemyManager::EnemyList& enemyList = EnemyManager::instance()->getEnemyList();
		for (Enemy* enemy : enemyList)
		{
			if (enemy->canRemove())
			{
				continue;
			}

			const TwoVector& size = enemy->getSize();
			const TwoVector& position = enemy->getPosition();
			if (position.m_x >= m_rectHitboxImpact.x
				&& position.m_x <= m_rectHitboxImpact.x + m_rectHitboxImpact.w
				&& position.m_y >= m_rectHitboxImpact.y
				&& position.m_y <= m_rectHitboxImpact.y + m_rectHitboxImpact.h)
			{
				enemy->decreaseHp(ConfigManager::instance()->m_playerTemplate.m_skillDamage * delta);
				enemy->slowDown();
			}
		}
	}

	CoinManager::CoinPropList& coinPropList = CoinManager::instance()->getCoinPropList();
	static const ResourcesManager::SoundPool& soundPool = ResourcesManager::instance()->getSoundPool();

	for (CoinProp* coinProp : coinPropList)
	{
		if (coinProp->canRemove())
		{
			continue;
		}

		const TwoVector& posCoinProp = coinProp->getPosition();
		if (posCoinProp.m_x >= m_position.m_x - m_size.m_x / 2
			&& posCoinProp.m_x <= m_position.m_x + m_size.m_x / 2
			&& posCoinProp.m_y >= m_position.m_y - m_size.m_y / 2
			&& posCoinProp.m_y <= m_position.m_y + m_size.m_y / 2)
		{
			coinProp->makeInvalid();
			CoinManager::instance()->increaseCoin(10);

			Mix_PlayChannel(-1, soundPool.find(ResID::Sound_Coin)->second, 0);
		}
	}
}

void PlayerManager::onRender(SDL_Renderer* renderer)
{
	static SDL_Point point;

	point.x = (int)(m_position.m_x - m_size.m_x / 2);
	point.y = (int)(m_position.m_y - m_size.m_y / 2);
	m_animCurrent->onRender(renderer, point);

	if (m_isReleasingFlash)
	{
		point.x = m_rectHitboxFlash.x;
		point.y = m_rectHitboxFlash.y;
		m_animEffectFlashCurrent->onRender(renderer, point);
	}

	if (m_isReleasingImpact)
	{
		point.x = m_rectHitboxImpact.x;
		point.y = m_rectHitboxImpact.y;
		m_animEffectImpactCurrent->onRender(renderer, point);
	}
}

double PlayerManager::getCurrentMp() const
{
	return m_mp;
}

void PlayerManager::onReleaseFlash()
{
	if (!m_canReleaseFlash || m_isReleasingFlash)
	{
		return;
	}

	switch (m_facing)
	{
	case Facing::Left:
		m_animEffectFlashCurrent = &m_animEffectFlashLeft;
		m_rectHitboxFlash.x = (int)(m_position.m_x - m_size.m_x / 2 - 300);
		m_rectHitboxFlash.y = (int)(m_position.m_y - 68 / 2);
		m_rectHitboxFlash.w = 300, m_rectHitboxFlash.h = 68;
		break;
	case Facing::Right:
		m_animEffectFlashCurrent = &m_animEffectFlashRight;
		m_rectHitboxFlash.x = (int)(m_position.m_x + m_size.m_x / 2);
		m_rectHitboxFlash.y = (int)(m_position.m_y - 68 / 2);
		m_rectHitboxFlash.w = 300, m_rectHitboxFlash.h = 68;
		break;
	case Facing::Up:
		m_animEffectFlashCurrent = &m_animEffectFlashUp;
		m_rectHitboxFlash.x = (int)(m_position.m_x - 68 / 2);
		m_rectHitboxFlash.y = (int)(m_position.m_y - m_size.m_x / 2 - 300);
		m_rectHitboxFlash.w = 68, m_rectHitboxFlash.h = 300;
		break;
	case Facing::Down:
		m_animEffectFlashCurrent = &m_animEffectFlashDown;
		m_rectHitboxFlash.x = (int)(m_position.m_x - 68 / 2);
		m_rectHitboxFlash.y = (int)(m_position.m_y + m_size.m_x / 2);
		m_rectHitboxFlash.w = 68, m_rectHitboxFlash.h = 300;
		break;
	}

	m_isReleasingFlash = true;
	m_animEffectFlashCurrent->reset();
	m_timerReleaseFlashCd.restart();

	static const ResourcesManager::SoundPool& soundPool = ResourcesManager::instance()->getSoundPool();

	Mix_PlayChannel(-1, soundPool.find(ResID::Sound_Flash)->second, 0);
}

void PlayerManager::onReleaseImpact()
{
	if (m_mp < 100 || m_isReleasingImpact)
	{
		return;
	}

	switch (m_facing)
	{
	case Facing::Left:
		m_animEffectImpactCurrent = &m_animEffectImpactLeft;
		m_rectHitboxImpact.x = (int)(m_position.m_x - m_size.m_x / 2 - 60);
		m_rectHitboxImpact.y = (int)(m_position.m_y - 140 / 2);
		m_rectHitboxImpact.w = 60, m_rectHitboxImpact.h = 140;
		break;
	case Facing::Right:
		m_animEffectImpactCurrent = &m_animEffectImpactRight;
		m_rectHitboxImpact.x = (int)(m_position.m_x + m_size.m_x / 2);
		m_rectHitboxImpact.y = (int)(m_position.m_y - 140 / 2);
		m_rectHitboxImpact.w = 60, m_rectHitboxImpact.h = 140;
		break;
	case Facing::Up:
		m_animEffectImpactCurrent = &m_animEffectImpactUp;
		m_rectHitboxImpact.x = (int)(m_position.m_x - 140 / 2);
		m_rectHitboxImpact.y = (int)(m_position.m_y - m_size.m_x / 2 - 60);
		m_rectHitboxImpact.w = 140, m_rectHitboxImpact.h = 60;
		break;
	case Facing::Down:
		m_animEffectImpactCurrent = &m_animEffectImpactDown;
		m_rectHitboxImpact.x = (int)(m_position.m_x - 140 / 2);
		m_rectHitboxImpact.y = (int)(m_position.m_y + m_size.m_x / 2);
		m_rectHitboxImpact.w = 140, m_rectHitboxImpact.h = 60;
		break;
	}

	m_mp = 0;
	m_isReleasingImpact = true;
	m_animEffectImpactCurrent->reset();

	static const ResourcesManager::SoundPool& soundPool = ResourcesManager::instance()->getSoundPool();

	Mix_PlayChannel(-1, soundPool.find(ResID::Sound_Impact)->second, 0);
}