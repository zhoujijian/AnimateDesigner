#ifndef _ANIMAT_LAYER_H_
#define _ANIMAT_LAYER_H_

#include "cocos2d.h"
#include <queue>

using namespace std;
using namespace cocos2d;

#define MAX_SPRITE_COUNT 256

class SimpleLayer;

class AnimatLayer : public CCLayerColor {
public:
	enum {
		creat = 0,
		rotate,
		translat,
		scale,
		poser,
		connect,
		append,
		max_state
	};

private:
	static AnimatLayer *aniinst;

public:
	AnimatLayer();
	~AnimatLayer();	

	static AnimatLayer* create(const ccColor4B& color, GLfloat width, GLfloat height);
	static AnimatLayer* instance();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void registerWithTouchDispatcher();

	virtual void draw();

	void drawbone();

	int getcur_state() { return cur_state; }
	void setcur_state(int next);

public:
	void setkey_frame(int index, bool iskey);
	void plykey_frame();
	void frame_selected(int index);
	bool iskey_frame(int index);

private:
	CCSprite* testarea(CCNode *root, bool isbone, const CCPoint& poi);
	CCSprite* testarea(CCNode *root, const CCPoint& poi);

	void set_curspr(CCSprite *spr);
	void rotate_a_b(const CCPoint& poia, const CCPoint& poib);
	void playani(CCSprite *spr);

private:
	bool isspr_bone(CCSprite *spr);

	void onbegin_create(const CCPoint& poigl);
	void onbegin_rotate(const CCPoint& poigl);
	void onbegin_translate(const CCPoint& poigl);
	void onbegin_scale(const CCPoint& poigl);
	void onbegin_append(const CCPoint& poigl);
	void onbegin_poser(const CCPoint& poigl);
	void onbegin_connect(const CCPoint& poigl);

	void onmoved_rotate(const CCPoint& poigl);
	void onmoved_translate(const CCPoint& poigl);
	void onmoved_scale(const CCPoint& poigl);

	void onclear_poser();

	CCSprite *sprcur, *sprold;
	CCSprite *boneroot;
	CCPoint posstart;
	float angstart;
	queue<CCSprite*> Q;	

private:
	SimpleLayer *simple_layer;
	int cur_state;
};

#endif