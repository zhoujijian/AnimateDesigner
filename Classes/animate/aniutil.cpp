#include <stack>
#include "aniutil.h"
#include "userobj.h"

using namespace std;

#define FRAME_DELTA 0.3

CCControlButton* AnimateUtiler::simple_button(const char *text) {
	CCLabelBMFont *label = CCLabelBMFont::create(text, "fonts/bitmapFontChinese.fnt");
	label->setScale(0.5);
	label->setColor(ccGREEN);
	CCControlButton *b = CCControlButton::create(label, CCScale9Sprite::create("button.png"));
	b->setZoomOnTouchDown(false);
	b->setAnchorPoint(ccp(0.0f, 0.0f));
	b->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
	return b;
}

CCControlButton* AnimateUtiler::bone_pose() {
	CCLabelTTF *label = CCLabelTTF::create("", "Courier New", 12);
	CCControlButton *b = CCControlButton::create(label, CCScale9Sprite::create("ball.png"));
	return b;
}

bool AnimateUtiler::inarea(CCNode *node, const CCPoint& poigl) {
	CCPoint poi = node->convertToNodeSpace(poigl);
	if (poi.x >= 0 && poi.x < node->getContentSize().width &&
		poi.y >= 0 && poi.y < node->getContentSize().height)
	{
		return true;
	}
	return false;
}

void AnimateUtiler::setframe(CCSprite *spr, const char *name) {
	CCSpriteFrame *sfr = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
	CCAssert(sfr, "no sprite frame");
	spr->setDisplayFrame(sfr);

	CCLayerColor *layer = (CCLayerColor*)spr->getChildByTag(SELET_SPRITE_TAGID);
	if (layer) {
		layer->setContentSize(spr->getContentSize());
	}
}

void AnimateUtiler::setattr(CCSprite *spr, KeyFrameObject *ko) {
	spr->setRotation(ko->get_rotate());
	spr->setPosition(ccp(ko->get_posx(), ko->get_posy()));
	spr->setScaleX(ko->get_scalex());
	spr->setScaleY(ko->get_scaley());
}

void AnimateUtiler::layout(CCNode *parent, int linear) {
	CCAssert(AnimateUtiler::HLR == linear || AnimateUtiler::HRL == linear ||
			 AnimateUtiler::VTB == linear || AnimateUtiler::VBT == linear, "linear param error");

	CCObject *o = NULL;
	CCArray *ac = parent->getChildren();
	if (NULL == ac) { return; }

	float x = 0, y = 0;
	CCSize sp = CCSizeZero;
	if (AnimateUtiler::HLR == linear || AnimateUtiler::HRL == linear) {
		CCARRAY_FOREACH(ac, o) {
			CCNode *c = (CCNode*)o;
			CCSize sc = c->getContentSize();
			c->setPosition(sp.width, 0);
			sp.width += sc.width;
			if (sp.height < sc.height) { sp.height = sc.height; }
		}
	}
	if (AnimateUtiler::VBT == linear || AnimateUtiler::VTB == linear) {
		CCARRAY_FOREACH(ac, o) {
			CCNode *c = (CCNode*)o;
			CCSize sc = c->getContentSize();
			c->setPosition(0, sp.height);
			sp.height += sc.height;
			if (sp.width < sc.width) { sp.width = sc.width; }
		}
	}
	parent->setContentSize(sp);
}

void AnimateObject::setcur_frame(const char *frame, const char *text) {
	CCAssert(frame, "frame nil");
	CCAssert(text,  "text nil");

	CC_SAFE_RELEASE(curframe);
	CC_SAFE_RELEASE(curtext);
	curframe = CCString::create(frame);
	curtext  = CCString::create(text);
	CC_SAFE_RETAIN(curframe);
	CC_SAFE_RETAIN(curtext);
}

AnimateObject* AnimateObject::create(bool bone) {
	AnimateObject *o = new AnimateObject(bone);
	o->seq = CCArray::create();
	o->seq->retain();
	o->autorelease();
	return o;
}

KeyFrameObject* AnimateObject::getkey_frame(int index) {
	CCObject *o;
	CCARRAY_FOREACH(seq, o) {
		KeyFrameObject *ko = (KeyFrameObject*)o;
		if (ko->getkey_index() == index) { return ko; }
	}
	return NULL;
}

void AnimateObject::setkey_frame(CCSprite *spr, int index, bool iskey) {
	int i = 0;
	for (i = 0; i < seq->count(); ++ i) {
		KeyFrameObject *o = dynamic_cast<KeyFrameObject*>(seq->objectAtIndex(i));

		if (o->getkey_index() == index) {
			CCAssert(!iskey, "set key repeated");
			seq->removeObject(o);
			return;
		}

		if (index < o->getkey_index()) { break; }
	}

	CCAssert(iskey, "set key error");

	KeyFrameObject *ko = KeyFrameObject::create();
	ko->setkey_index(index);
	ko->set_pos(spr->getPositionX(), spr->getPositionY());
	ko->set_scale(spr->getScaleX(), spr->getScaleY());
	ko->set_rotate(spr->getRotation());
	if (!is_bone) {
		ko->settex_name(curtext->getCString());
		ko->setkey_frame(curframe->getCString());		
	}

	seq->insertObject(ko, i);
}

void AnimateObject::frame_callback(CCObject *o) {
	CCAssert(index_call_back < seq->count(), "call back index out range");
	KeyFrameObject *ko = (KeyFrameObject*)seq->objectAtIndex(index_call_back);
	CCSprite *spr = dynamic_cast<CCSprite*>(o);
	CCAssert(spr, "sprite nil");

	AnimateUtiler::setattr(spr, ko);
	index_call_back ++;

	CCLayerColor *layer = (CCLayerColor*)spr->getChildByTag(SELET_SPRITE_TAGID);
	if (layer) {
		layer->setVisible(index_call_back >= seq->count());
	}
}

void AnimateObject::plykey_frame(CCSprite *spr) {
	CCArray *bone_seqarr = CCArray::create();
	CCArray *anim_seqarr = CCArray::create();
	CCArray *aniarr = CCArray::create();

	// care! ccArray::count() ret is [unsigned int], not use[seq->count() - 1]
	for (int i = 0; i + 1 < seq->count(); ++ i) {
		KeyFrameObject *r = (KeyFrameObject*)seq->objectAtIndex(i);
		KeyFrameObject *k = (KeyFrameObject*)seq->objectAtIndex(i + 1);
		float delta = FRAME_DELTA * (k->getkey_index() - r->getkey_index());
		if (is_bone) {
			CCScaleTo  *scato = CCScaleTo::create(delta, k->get_scalex(), k->get_scaley());
			CCMoveTo   *movto = CCMoveTo ::create(delta, ccp(k->get_posx(), k->get_posy()));
			CCRotateTo *rotto = CCRotateTo::create(delta, k->get_rotate());
			CCArray *arr = CCArray::create();
			arr->addObject(scato);
			arr->addObject(movto);
			arr->addObject(rotto);
			CCFiniteTimeAction *spawn = CCSpawn::create(arr);
			bone_seqarr->addObject(spawn);
		} else {
			CCSpriteFrame *sfr = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(r->getkey_frame());
			CCAnimationFrame *frame = new CCAnimationFrame();
			frame->initWithSpriteFrame(sfr, k->getkey_index() - r->getkey_index(), NULL);
			frame->autorelease();
			aniarr->addObject(frame);

			CCDelayTime *delay = CCDelayTime::create(delta);
			CCCallFunc *call = CCCallFuncO::create(this, callfuncO_selector(AnimateObject::frame_callback), spr);
			anim_seqarr->addObject(delay);
			anim_seqarr->addObject(call);
		}
	}

	if (bone_seqarr->count() > 0) {
		KeyFrameObject *ko = (KeyFrameObject*)seq->objectAtIndex(0);
		AnimateUtiler::setattr(spr, ko);

		CCFiniteTimeAction *seq = CCSequence::create(bone_seqarr);
		spr->runAction(seq);
	}

	if (aniarr->count() > 0) {
		index_call_back = 0;
		frame_callback(spr);

		KeyFrameObject *ko = (KeyFrameObject*)seq->lastObject();
		CCSpriteFrame *sfr = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ko->getkey_frame());
		CCAnimationFrame *fir = new CCAnimationFrame();
		fir->initWithSpriteFrame(sfr, 0, NULL);
		aniarr->addObject(fir);
		CCAnimation *animate = CCAnimation::create(aniarr, FRAME_DELTA, 1);
		CCAnimate *aniact = CCAnimate::create(animate);
		
		CCFiniteTimeAction *spa = CCSpawn::createWithTwoActions(CCSequence::create(anim_seqarr), aniact);
		spr->runAction(spa);
	}
}

void AnimateObject::prikey_frame() {
	CCLog("key frame count %d", seq->count());

	CCObject *o;
	CCARRAY_FOREACH(seq, o) {
		KeyFrameObject *ko = dynamic_cast<KeyFrameObject*>(o);
		CCLog("pos(%f, %f), rot(%f), scale(%f, %f), index(%d), frame(%s)",
			ko->get_posx(), ko->get_posy(), ko->get_rotate(),
			ko->get_scalex(), ko->get_scaley(), ko->getkey_index(),
			ko->getkey_frame() ? ko->getkey_frame() : "nil");
	}
}
