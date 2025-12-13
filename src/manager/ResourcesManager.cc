#include "ResourcesManager.h"

bool ResourcesManager::loadFromFile(SDL_Renderer* renderer)
{
	if (!loadTexture(renderer))
	{
		return false;
	}

	if (!loadSound(renderer))
	{
		return false;
	}

	if (!loadMusic(renderer))
	{
		return false;
	}

	if (!loadFont(renderer))
	{
		return false;
	}

	return true;
}

const ResourcesManager::FontPool& ResourcesManager::getFontPool()
{
	return m_fontPool;
}

const ResourcesManager::SoundPool& ResourcesManager::getSoundPool()
{
	return m_soundPool;
}

const ResourcesManager::MusicPool& ResourcesManager::getMusicPool()
{
	return m_musicPool;
}

const ResourcesManager::TexturePool& ResourcesManager::getTexturePool()
{
	return m_texturePool;
}

bool ResourcesManager::loadTexture(SDL_Renderer* renderer)
{
	m_texturePool[ResID::Tex_Tileset] = IMG_LoadTexture(renderer, "resources/tileset.png");

	m_texturePool[ResID::Tex_Player] = IMG_LoadTexture(renderer, "resources/player.png");
	m_texturePool[ResID::Tex_Archer] = IMG_LoadTexture(renderer, "resources/tower_archer.png");
	m_texturePool[ResID::Tex_Axeman] = IMG_LoadTexture(renderer, "resources/tower_axeman.png");
	m_texturePool[ResID::Tex_Gunner] = IMG_LoadTexture(renderer, "resources/tower_gunner.png");

	m_texturePool[ResID::Tex_Slime] = IMG_LoadTexture(renderer, "resources/enemy_slime.png");
	m_texturePool[ResID::Tex_KingSlime] = IMG_LoadTexture(renderer, "resources/enemy_king_slime.png");
	m_texturePool[ResID::Tex_Skeleton] = IMG_LoadTexture(renderer, "resources/enemy_skeleton.png");
	m_texturePool[ResID::Tex_Goblin] = IMG_LoadTexture(renderer, "resources/enemy_goblin.png");
	m_texturePool[ResID::Tex_GoblinPriest] = IMG_LoadTexture(renderer, "resources/enemy_goblin_priest.png");
	m_texturePool[ResID::Tex_SlimeSketch] = IMG_LoadTexture(renderer, "resources/enemy_slime_sketch.png");
	m_texturePool[ResID::Tex_KingSlimeSketch] = IMG_LoadTexture(renderer, "resources/enemy_king_slime_sketch.png");
	m_texturePool[ResID::Tex_SkeletonSketch] = IMG_LoadTexture(renderer, "resources/enemy_skeleton_sketch.png");
	m_texturePool[ResID::Tex_GoblinSketch] = IMG_LoadTexture(renderer, "resources/enemy_goblin_sketch.png");
	m_texturePool[ResID::Tex_GoblinPriestSketch] = IMG_LoadTexture(renderer, "resources/enemy_goblin_priest_sketch.png");

	m_texturePool[ResID::Tex_BulletArrow] = IMG_LoadTexture(renderer, "resources/bullet_arrow.png");
	m_texturePool[ResID::Tex_BulletAxe] = IMG_LoadTexture(renderer, "resources/bullet_axe.png");
	m_texturePool[ResID::Tex_BulletShell] = IMG_LoadTexture(renderer, "resources/bullet_shell.png");

	m_texturePool[ResID::Tex_Coin] = IMG_LoadTexture(renderer, "resources/coin.png");
	m_texturePool[ResID::Tex_Home] = IMG_LoadTexture(renderer, "resources/home.png");

	m_texturePool[ResID::Tex_EffectFlash_Up] = IMG_LoadTexture(renderer, "resources/effect_flash_up.png");
	m_texturePool[ResID::Tex_EffectFlash_Down] = IMG_LoadTexture(renderer, "resources/effect_flash_down.png");
	m_texturePool[ResID::Tex_EffectFlash_Left] = IMG_LoadTexture(renderer, "resources/effect_flash_left.png");
	m_texturePool[ResID::Tex_EffectFlash_Right] = IMG_LoadTexture(renderer, "resources/effect_flash_right.png");
	m_texturePool[ResID::Tex_EffectImpact_Up] = IMG_LoadTexture(renderer, "resources/effect_impact_up.png");
	m_texturePool[ResID::Tex_EffectImpact_Down] = IMG_LoadTexture(renderer, "resources/effect_impact_down.png");
	m_texturePool[ResID::Tex_EffectImpact_Left] = IMG_LoadTexture(renderer, "resources/effect_impact_left.png");
	m_texturePool[ResID::Tex_EffectImpact_Right] = IMG_LoadTexture(renderer, "resources/effect_impact_right.png");
	m_texturePool[ResID::Tex_EffectExplode] = IMG_LoadTexture(renderer, "resources/effect_explode.png");

	m_texturePool[ResID::Tex_UISelectCursor] = IMG_LoadTexture(renderer, "resources/ui_select_cursor.png");
	m_texturePool[ResID::Tex_UIPlaceIdle] = IMG_LoadTexture(renderer, "resources/ui_place_idle.png");
	m_texturePool[ResID::Tex_UIPlaceHoveredTop] = IMG_LoadTexture(renderer, "resources/ui_place_hovered_top.png");
	m_texturePool[ResID::Tex_UIPlaceHoveredLeft] = IMG_LoadTexture(renderer, "resources/ui_place_hovered_left.png");
	m_texturePool[ResID::Tex_UIPlaceHoveredRight] = IMG_LoadTexture(renderer, "resources/ui_place_hovered_right.png");
	m_texturePool[ResID::Tex_UIUpgradeIdle] = IMG_LoadTexture(renderer, "resources/ui_upgrade_idle.png");
	m_texturePool[ResID::Tex_UIUpgradeHoveredTop] = IMG_LoadTexture(renderer, "resources/ui_upgrade_hovered_top.png");
	m_texturePool[ResID::Tex_UIUpgradeHoveredLeft] = IMG_LoadTexture(renderer, "resources/ui_upgrade_hovered_left.png");
	m_texturePool[ResID::Tex_UIUpgradeHoveredRight] = IMG_LoadTexture(renderer, "resources/ui_upgrade_hovered_right.png");
	m_texturePool[ResID::Tex_UIHomeAvatar] = IMG_LoadTexture(renderer, "resources/ui_home_avatar.png");
	m_texturePool[ResID::Tex_UIPlayerAvatar] = IMG_LoadTexture(renderer, "resources/ui_player_avatar.png");
	m_texturePool[ResID::Tex_UIHeart] = IMG_LoadTexture(renderer, "resources/ui_heart.png");
	m_texturePool[ResID::Tex_UICoin] = IMG_LoadTexture(renderer, "resources/ui_coin.png");
	m_texturePool[ResID::Tex_UIGameOverBar] = IMG_LoadTexture(renderer, "resources/ui_game_over_bar.png");
	m_texturePool[ResID::Tex_UIWinText] = IMG_LoadTexture(renderer, "resources/ui_win_text.png");
	m_texturePool[ResID::Tex_UILossText] = IMG_LoadTexture(renderer, "resources/ui_loss_text.png");

	for (const auto& pair : m_texturePool)
	{
		if (!pair.second)
		{
			return false;
		}
	}

	return true;
}

bool ResourcesManager::loadSound(SDL_Renderer* renderer)
{
	m_soundPool[ResID::Sound_ArrowFire_1] = Mix_LoadWAV("resources/sound_arrow_fire_1.mp3");
	m_soundPool[ResID::Sound_ArrowFire_2] = Mix_LoadWAV("resources/sound_arrow_fire_2.mp3");
	m_soundPool[ResID::Sound_AxeFire] = Mix_LoadWAV("resources/sound_axe_fire.wav");
	m_soundPool[ResID::Sound_ShellFire] = Mix_LoadWAV("resources/sound_shell_fire.wav");
	m_soundPool[ResID::Sound_ArrowHit_1] = Mix_LoadWAV("resources/sound_arrow_hit_1.mp3");
	m_soundPool[ResID::Sound_ArrowHit_2] = Mix_LoadWAV("resources/sound_arrow_hit_2.mp3");
	m_soundPool[ResID::Sound_ArrowHit_3] = Mix_LoadWAV("resources/sound_arrow_hit_3.mp3");
	m_soundPool[ResID::Sound_AxeHit_1] = Mix_LoadWAV("resources/sound_axe_hit_1.mp3");
	m_soundPool[ResID::Sound_AxeHit_2] = Mix_LoadWAV("resources/sound_axe_hit_2.mp3");
	m_soundPool[ResID::Sound_AxeHit_3] = Mix_LoadWAV("resources/sound_axe_hit_3.mp3");
	m_soundPool[ResID::Sound_ShellHit] = Mix_LoadWAV("resources/sound_shell_hit.mp3");

	m_soundPool[ResID::Sound_Flash] = Mix_LoadWAV("resources/sound_flash.wav");
	m_soundPool[ResID::Sound_Impact] = Mix_LoadWAV("resources/sound_impact.wav");

	m_soundPool[ResID::Sound_Coin] = Mix_LoadWAV("resources/sound_coin.mp3");
	m_soundPool[ResID::Sound_HomeHurt] = Mix_LoadWAV("resources/sound_home_hurt.wav");
	m_soundPool[ResID::Sound_PlaceTower] = Mix_LoadWAV("resources/sound_place_tower.mp3");
	m_soundPool[ResID::Sound_TowerLevelUp] = Mix_LoadWAV("resources/sound_tower_level_up.mp3");

	m_soundPool[ResID::Sound_Win] = Mix_LoadWAV("resources/sound_win.wav");
	m_soundPool[ResID::Sound_Loss] = Mix_LoadWAV("resources/sound_loss.mp3");

	for (const auto& pair : m_soundPool)
	{
		if (!pair.second)
		{
			return false;
		}
	}

	return true;
}

bool ResourcesManager::loadMusic(SDL_Renderer* renderer)
{
	m_musicPool[ResID::Music_BGM] = Mix_LoadMUS("resources/music_bgm.mp3");

	for (const auto& pair : m_musicPool)
	{
		if (!pair.second)
		{
			return false;
		}
	}

	return true;
}

bool ResourcesManager::loadFont(SDL_Renderer* renderer)
{
	m_fontPool[ResID::Font_Main] = TTF_OpenFont("resources/ipix.ttf", 25);

	for (const auto& pair : m_fontPool)
	{
		if (!pair.second)
		{
			return false;
		}
	}

	return true;
}