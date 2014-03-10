#ifndef _FRAGMENT_H_
#define _FRAGMENT_H_

#include <string>
#include "cocos2d.h"
#include "CCControlButton.h"
#include "imagespliter.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class MoveLayer : public CCLayer {
public:
	MoveLayer() : sprite(NULL), cur_rect(NULL), cur_text(NULL), cur_plist(NULL) { }
	~MoveLayer();

	static MoveLayer* create();
	static MoveLayer* sharedMoveLayer();
	bool init();

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void visit();

	void setpng(const char *key);
	void rempng(const char *key);

	void setplist(const char *plist);
	const char *getcur_plist() {
		return cur_plist ? cur_plist->getCString() : NULL;
	}
	const char* getcur_rect() {
		return cur_rect ? cur_rect->getCString() : NULL;
	}
	const char* getcur_text() {
		return cur_text ? cur_text->getCString() : NULL;
	}

	const char* getcur_pngkey();

private:
	void create_sprite_fragment(CCTexture2D *texture);

private:
	static MoveLayer *instance;

private:
	CCPoint poslast;
	ImageSpliter spliter;
	CCSprite *sprite;
	std::string curpngkey;

	CCString *cur_rect;
	CCString *cur_text;
	CCString *cur_plist;
};

#endif
