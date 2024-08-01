#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include "manager.h"

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <unordered_map>

using namespace std;

//资源ID
enum class ResID
{
	Tex_Tileset, //地图纹理

	Tex_Player, //玩家角色（龙）
	Tex_Archer, //弓箭手
	Tex_Axeman, //斧头兵
	Tex_Gunner, //枪炮兵

	Tex_Slime,				//史莱姆
	Tex_KingSlime,			//皇家史莱姆
	Tex_Skeleton,			//骷髅兵
	Tex_Goblin,				//哥布林
	Tex_GoblinPriest,		//哥布林祭司

	Tex_SlimeSketch,		//史莱姆素描（纯白体型图片，受到伤害后把素描图片叠加上去）
	Tex_KingSlimeSketch,	//皇家史莱姆素描
	Tex_SkeletonSketch,		//骷髅兵素描
	Tex_GoblinSketch,		//哥布林素描
	Tex_GoblinPriestSketch, //哥布林祭司素描

	Tex_BulletArrow, //箭（弓箭手的兵器）
	Tex_BulletAxe,	 //斧头（斧头兵的兵器）
	Tex_BulletShell, //炮弹（枪炮兵的兵器）

	Tex_Coin, //金币
	Tex_Home, //房子（防守的目标）

	//对应资源文件

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

	Sound_Win,  //游戏胜利音效
	Sound_Loss, //游戏失败音效

	Music_BGM, //背景音乐

	Font_Main //字体
};

//资源管理类
class ResourcesManager : public Manager<ResourcesManager>
{
	friend class Manager<ResourcesManager>;

public:
	typedef unordered_map<ResID, TTF_Font*> FontPool;		//字体池
	typedef unordered_map<ResID, Mix_Chunk*> SoundPool;		//音效池
	typedef unordered_map<ResID, Mix_Music*> MusicPool;		//音乐池
	typedef unordered_map<ResID, SDL_Texture*> TexturePool; //地图池

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
	FontPool font_pool;		  //字体池对象
	SoundPool sound_pool;	  //音效池对象
	MusicPool music_pool;	  //音乐池对象
	TexturePool texture_pool; //地图池对象
};

#endif