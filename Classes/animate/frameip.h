#ifndef _ANIMATE_FRAME_IP_H_
#define _ANIMATE_FRAME_IP_H_

#include "cocos2d.h"
#include "GUI/CCControlExtension/CCControlExtensions.h"
#include "animatcommon.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define MAX_LAYER_COUNT   6

#define RECT_LAYER_HEIGHT 10
#define FRAME_UNIT_WIDTH  7
#define FRAME_LINE_SHORTH 5
#define FRAME_LINE_LONGH  10
#define FRAME_NUMBER_H    6

struct RectLayer {
	int layerid;
	CCRect rect;
};

class LayerFrame : public CCLayerColor {
public:
	struct FrameLocal {
		bool is_keyframe;
		CCLabelBMFont *number;
	};

	LayerFrame();
	~LayerFrame();

	static LayerFrame* create(const ccColor4B& color, GLfloat width, GLfloat height);

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void draw();

	void set_key_frame(int frameid);

	void add_layer(CCObject *sender, CCControlEvent evt);
	void remove_layer(CCObject *sender, CCControlEvent evt);
	void set_keyframe(CCObject *sender, CCControlEvent evt);
	void play_frame(CCObject *sender, CCControlEvent evt);

private:
	void draw_frame_line();
	void init_layout(GLfloat width, GLfloat height);
	float get_frame_header_height();

private:
	int cur_layer_index;

	int layerid;
	int rect_layer[MAX_LAYER_COUNT];
	int layer_count;

	int cur_frame_selected;
	FrameLocal frame_local[MAX_FRAME_COUNT];
};

#endif
