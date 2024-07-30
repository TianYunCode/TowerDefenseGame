#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include "manager.h"

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <unordered_map>

enum class ResID
{
	Tex_Tileset,

	Tex_Player,
	Tex_Archer,
	Tex_Axeman,
	Tex_Gunner,

	Tex_Slime,
	Tex_KingSlime,
	Tex_Skeleton,
	Tex_Goblin,
	Tex_GoblinPriest,
	Tex_SlimeSketch,
	Tex_KingSlimeSketch,
	Tex_SkeletonSketch,
	Tex_GoblinSketch,
	Tex_GoblinPriestSketch,

	Tex_BulletArrow,
	Tex_BulletAxe,
	Tex_BulletShell,

	Tex_Coin,
	Tex_Home,

	Tex_EffectFlash_Up,
	Tex_EffectFlash_Down,
	Tex_EffectFlash_Left,
	Tex_EffectFlash_Right,
	Tex_EffectImpact_Up,
	Tex_EffectImpact_Down,
	Tex_EffectImpact_Left,
	Tex_EffectImpact_Right,
	Tex_EffectExplode,

	Tex_UISelectCursor,
	Tex_UIPlaceIdle,
	Tex_UIPlaceHoveredTop,
	Tex_UIPlaceHoveredLeft,
	Tex_UIPlaceHoveredRight,
	Tex_UIUpgradeIdle,
	Tex_UIUpgradeHoveredTop,
	Tex_UIUpgradeHoveredLeft,
	Tex_UIUpgradeHoveredRight,
	Tex_UIHomeAvatar,
	Tex_UIPlayerAvatar,
	Tex_UIHeart,
	Tex_UICoin,
	Tex_UIGameOverBar,
	Tex_UIWinText,
	Tex_UILossText,

	Sound_ArrowFire_1,
	Sound_ArrowFire_2,
	Sound_AxeFire,
	Sound_ShellFire,
	Sound_ArrowHit_1,
	Sound_ArrowHit_2,
	Sound_ArrowHit_3,
	Sound_AxeHit_1,
	Sound_AxeHit_2,
	Sound_AxeHit_3,
	Sound_ShellHit,

	Sound_Flash,
	Sound_Impact,

	Sound_Coin,
	Sound_HomeHurt,
	Sound_PlaceTower,
	Sound_TowerLevelUp,

	Sound_Win,
	Sound_Loss,

	Music_BGM,

	Font_Main
};

class ResourcesManager : public Manager<ResourcesManager>
{
	friend class Manager<ResourcesManager>;

public:
	typedef std::unordered_map<ResID, TTF_Font*> FontPool;
	typedef std::unordered_map<ResID, Mix_Chunk*> SoundPool;
	typedef std::unordered_map<ResID, Mix_Music*> MusicPool;
	typedef std::unordered_map<ResID, SDL_Texture*> TexturePool;

public:
	bool load_from_file(SDL_Renderer* renderer);

	const FontPool& get_font_pool();
	const SoundPool& get_sound_pool();
	const MusicPool& get_music_pool();
	const TexturePool& get_texture_pool();

protected:
	ResourcesManager() = default;
	~ResourcesManager() = default;

private:
	FontPool font_pool;
	SoundPool sound_pool;
	MusicPool music_pool;
	TexturePool texture_pool;
};

#endif