#ifndef _LAYOUT_H_
#define _LAYOUT_H_

#include<vector>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "frameip.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define IMAGE_LAYER_TAGID 300
#define BONES_LAYER_TAGID 301
#define SIMPL_LAYER_TAGID 302

#define OPER_ANIMAT_NODE_TAGID    304

// ########################################
#define BUTTON_MINTAG             305

#define BUTTON_CREAT_TAGID        305
#define BUTTON_ROTAT_TAGID        306
#define BUTTON_TRANS_TAGID        307
#define BUTTON_SCALE_TAGID        308
#define BUTTON_POSER_TAGID        309
#define BUTTON_CONCT_TAGID        310
#define BUTTON_APEND_TAGID        311

#define BUTTON_MAXTAG             312
// ########################################

#define BUTTON_SAVER_TAGID        313
#define BUTTON_MODER_TAGID        314
#define BUTTON_CLEAR_TAGID        315

#define DEBUG_SHOW_LAYER_TAGID    100
#define DEBUG_FRAME_LAYER_TAGID   101
#define DEBUG_MODE_LAYER_TAGID    102

class AnimatLayer;

class SimpleLayer : public CCLayer {
public:
    SimpleLayer() { }
	static SimpleLayer* create();
	virtual void draw();
};

class AnimatLayout : public CCNode {
public:
	AnimatLayout();
	~AnimatLayout();

	static AnimatLayout* create(float width, float height);

	virtual bool init(float width, float height);

private:
	CCLayerColor* create_mode_layer();
	LayerFrame* create_frame_layer(float width, float height);
	CCLayerColor* create_operanimat_layer();
	AnimatLayer* create_animat_layer(float width, float height);
	CCLayerColor* create_operlevel_layer(LayerFrame *frame_layer);

private:
	void onmode_click(CCObject *sender, CCControlEvent event);

	void on_clear_clicked(CCObject *sender, CCControlEvent event);
	void on_save_clicked(CCObject *sender, CCControlEvent event);

	void nextmode(int state);
	CCControlButton* get_oper_button(int state);

private:
	CCSprite* load_png_animat(const char *path);

private:
	CCNode *animlayer;
};

#endif
