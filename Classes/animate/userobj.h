#ifndef _ANIMATE_USER_OBJECT_H_
#define _ANIMATE_USER_OBJECT_H_

#include "cocos2d.h"

using namespace cocos2d;

class KeyFrameObject : public CCObject {
public:
	KeyFrameObject()
		: keyframe(NULL), textname(NULL), rotation(0), scalex(0), scaley(0), posx(0), posy(0), keyindex(-1) { }
	~KeyFrameObject() {
		CC_SAFE_RELEASE(keyframe);
		CC_SAFE_RELEASE(textname);
	}

	static KeyFrameObject* create() {
		KeyFrameObject *o = new KeyFrameObject();
		o->autorelease();
		return o;
	}

public:
	float get_rotate() { return rotation; }
	float get_scalex() { return scalex; }
	float get_scaley() { return scaley; }
	float get_posx() { return posx; }
	float get_posy() { return posy; }	
	int getkey_index() { return keyindex; }
	const char* getkey_frame() {
		return keyframe ? keyframe->getCString() : NULL;
	}
	const char* gettex_name() {
		return textname ? textname->getCString() : NULL;
	}

	void set_rotate(float r) { rotation = r; }
	void set_scale(float sx, float sy) {
		scalex = sx;
		scaley = sy;
	}
	void set_pos(float px, float py) {
		posx = px;
		posy = py;
	}
	void setkey_frame(const char *frame) {
		CCAssert(frame, "frame nil");
		CC_SAFE_RELEASE(keyframe);
		keyframe = CCString::create(frame);
		CC_SAFE_RETAIN(keyframe);
	}
	void settex_name(const char *name) {
		CCAssert(name, "texture name nil");
		CC_SAFE_RELEASE(textname);
		textname = CCString::create(name);
		CC_SAFE_RETAIN(textname);
	}
	void setkey_index(int index) {
		CCAssert(index >= 0 && index < 256, "index out range");
		keyindex = index;
	}

private:
	float rotation;
	float scalex, scaley;
	float posx, posy;
	CCString *keyframe;
	CCString *textname;
	int keyindex;
};

class AnimateObject : public CCObject {
public:
	AnimateObject(bool bone) : is_bone(bone), seq(NULL), curframe(NULL), curtext(NULL) {

	}

	~AnimateObject() {
		CC_SAFE_RELEASE(seq);
		CC_SAFE_RELEASE(curframe);
		CC_SAFE_RELEASE(curtext);
	}

public:
	static AnimateObject* create(bool bone);

	CCArray* getseq() { return seq; }
	bool isbone() { return is_bone; }
	void setcur_frame(const char *frame, const char *text);
	void setkey_frame(CCSprite *spr, int index, bool iskey);
	KeyFrameObject* getkey_frame(int index);
	void prikey_frame();
	void plykey_frame(CCSprite *spr);

	void frame_callback(CCObject *o);

private:
	bool is_bone;
	CCArray *seq;
	CCString *curframe, *curtext;

	int index_call_back;
};

#endif