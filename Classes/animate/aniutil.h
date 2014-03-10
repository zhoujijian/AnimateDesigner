#ifndef _ANIMATE_UTIL_H_
#define _ANIMATE_UTIL_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "userobj.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define SELET_SPRITE_TAGID 201

class AnimateUtiler {
public:
	enum {
		VBT = 0,
		VTB,
		HLR,
		HRL
	};

	static CCControlButton* simple_button(const char *text);
	static CCControlButton* bone_pose();

	static bool inarea(CCNode *node, const CCPoint& poigl);
	static void setframe(CCSprite *spr, const char *name);
	static void setattr(CCSprite *spr, KeyFrameObject *ko);
	static void layout(CCNode *parent, int linear);
};

#endif