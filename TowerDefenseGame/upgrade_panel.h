#ifndef _UPGRADE_PANEL_H_
#define _UPGRADE_PANEL_H_

#include "panel.h"
#include "tower_manager.h"
#include "resources_manager.h"

class UpgradePanel : public Panel
{
public:
	UpgradePanel();
	~UpgradePanel() = default;

	void on_update(SDL_Renderer* renderer);

protected:
	void on_click_top_area() override;
	void on_click_left_area() override;
	void on_click_right_area() override;
};

#endif
