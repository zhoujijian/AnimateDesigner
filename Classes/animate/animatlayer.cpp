#include "animatlayer.h"
#include "layout.h"
#include "userobj.h"
#include "aniutil.h"
#include "fragment.h"

#define FRAME_SPRITE_TAGID 200
#define BONES_ROOTER_TAGID 6000

AnimatLayer* AnimatLayer::aniinst = NULL;

void AnimatLayer::onbegin_create(const CCPoint& poi) {
	const char *rs = MoveLayer::sharedMoveLayer()->getcur_rect();
	if (NULL == rs) { return; }
	const char *ts = MoveLayer::sharedMoveLayer()->getcur_text();
	CCAssert(ts, "selected rect not nil, texture nil");

	AnimateObject *anio = AnimateObject::create(false);
	anio->setcur_frame(rs, ts);

	CCSpriteFrame *rect = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(rs);
	CCSprite *sprite = CCSprite::createWithSpriteFrame(rect);
	sprite->setPosition(convertToNodeSpace(poi));
	sprite->setUserObject(anio);
	addChild(sprite);

	set_curspr(sprite);
}

void AnimatLayer::onbegin_rotate(const CCPoint& poi) {
	if (sprcur) {
		posstart = sprcur->getParent()->convertToNodeSpace(poi);
		angstart = sprcur->getRotation();
	}
}

void AnimatLayer::onmoved_rotate(const CCPoint& poigl) {
	if (sprcur) {
		CCPoint poscur = sprcur->getParent()->convertToNodeSpace(poigl);
		rotate_a_b(posstart, poscur);
	}
}

void AnimatLayer::onbegin_translate(const CCPoint& poigl) {
	if (sprcur) {
		posstart = poigl;
	}
}

void AnimatLayer::onmoved_translate(const CCPoint& poigl) {
	if (sprcur) {
		sprcur->setPositionX(sprcur->getPositionX() + poigl.x - posstart.x);
		sprcur->setPositionY(sprcur->getPositionY() + poigl.y - posstart.y);
		posstart = poigl;
	}
}

void AnimatLayer::onbegin_scale(const CCPoint& poigl) {

}

void AnimatLayer::onmoved_scale(const CCPoint& poigl) {

}

void AnimatLayer::onbegin_append(const CCPoint& poigl) {
	const char *rect = MoveLayer::sharedMoveLayer()->getcur_rect();
	if (NULL == rect) { return; }
	const char *text = MoveLayer::sharedMoveLayer()->getcur_text();
	CCAssert(text, "selected rect not nil, texture nil");

	if (sprcur) {
		AnimateObject *anio = dynamic_cast<AnimateObject*>(sprcur->getUserObject());
		CCAssert(anio, "sprite selected not [animate|bone]");
		if (anio->isbone()) { return; }

		anio->setcur_frame(rect, text);
		AnimateUtiler::setframe(sprcur, rect);
	}
}

void AnimatLayer::onbegin_poser(const CCPoint& poigl) {
	CCSprite *spr = testarea(this, poigl);

	if (spr) {
		if (isspr_bone(spr)) { set_curspr(spr); }
		return;
	}

	if (sprcur && isspr_bone(sprcur)) {
		CCSprite *spr = CCSprite::create("ball.png");
		AnimateObject *anio = AnimateObject::create(true);
		spr->setUserObject(anio);
		spr->setPosition(sprcur->convertToNodeSpace(poigl));

		sprcur->addChild(spr);
	}
}

void AnimatLayer::onclear_poser() {
	sprold = NULL;
}

void AnimatLayer::onbegin_connect(const CCPoint& poigl) {
	CCSprite *spr = testarea(this, poigl);

	if (NULL == spr) { return; }

	if (isspr_bone(spr)) {
		set_curspr(spr);
		return;
	}

	if (sprcur && isspr_bone(sprcur)) {
		CCPoint pos = sprcur->convertToNodeSpace(spr->getParent()->convertToWorldSpace(spr->getPosition()));
		spr->retain();
		spr->removeFromParentAndCleanup(true);
		spr->setPosition(pos);
		sprcur->addChild(spr);

		set_curspr(spr);
	}
}

void AnimatLayer::rotate_a_b(const CCPoint& poia, const CCPoint& poib) {
	CCRect rect = sprcur->boundingBox();
	float ax = poia.x - rect.getMidX();
	float ay = poia.y - rect.getMidY();
	float bx = poib.x - rect.getMidX();
	float by = poib.y - rect.getMidY();
	float angle = (atan2(bx, by) - atan2(ax, ay)) * 180 / 3.1415926 + angstart;
	sprcur->setRotation(angle);
}

AnimatLayer::AnimatLayer() : cur_state(max_state), boneroot(NULL), sprold(NULL), sprcur(NULL) {
}

AnimatLayer::~AnimatLayer() {
}

AnimatLayer* AnimatLayer::instance() {
	CCAssert(aniinst);
	return aniinst;
}

AnimatLayer* AnimatLayer::create(const ccColor4B& color, GLfloat width, GLfloat height) {
	if (!aniinst) {
		AnimatLayer *layer = new AnimatLayer();
		layer->autorelease();
		if (layer->initWithColor(color, width, height)) {
			layer->simple_layer = SimpleLayer::create();
			layer->simple_layer->setTag(SIMPL_LAYER_TAGID);
			layer->simple_layer->setContentSize(CCSizeMake(width, height));

			layer->addChild(layer->simple_layer);

			CCSize size = layer->getContentSize();
			layer->boneroot = CCSprite::create("ball.png");
			AnimateObject *anio = AnimateObject::create(true);
			layer->boneroot->setUserObject(anio);
			layer->boneroot->setPosition(ccp(size.width * 0.5, size.height * 0.5));
			layer->boneroot->setTag(BONES_ROOTER_TAGID);
			layer->addChild(layer->boneroot);

			aniinst = layer;
		}		
	}

	return aniinst;
}

void AnimatLayer::set_curspr(CCSprite *spr) {
	CCLayerColor *back;
	if (sprcur != spr) {
		if (NULL == sprcur) {
			back = CCLayerColor::create(ccc4(100, 100, 100, 100));
			back->setTag(SELET_SPRITE_TAGID);			
		} else {
			back = (CCLayerColor*)sprcur->getChildByTag(SELET_SPRITE_TAGID);
			CCAssert(back, "selected sprite no back");
		}

		back->retain();
		if (sprcur) {
			sprcur->removeChildByTag(SELET_SPRITE_TAGID, true);
		}
		if (spr) {
			back->setContentSize(spr->getContentSize());
			spr->addChild(back);
		}
		back->release();
		sprcur = spr;
	}
}

bool AnimatLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
	CCPoint poigl = pTouch->getLocation();
	if (!AnimateUtiler::inarea(this, poigl)) { return true; }
		
	CCSprite *spr = testarea(this, poigl);
	if (AnimatLayer::creat != cur_state &&
		AnimatLayer::poser != cur_state &&
		AnimatLayer::connect != cur_state)
	{
		set_curspr(spr);
	}
	
	switch(cur_state) {
	case AnimatLayer::creat:    { onbegin_create(poigl);    break; }
	case AnimatLayer::translat: { onbegin_translate(poigl); break; }
	case AnimatLayer::rotate:   { onbegin_rotate(poigl);    break; }
	case AnimatLayer::scale:    { onbegin_scale(poigl);     break; }
	case AnimatLayer::append:   { onbegin_append(poigl);    break; }
	case AnimatLayer::poser:    { onbegin_poser(poigl);     break; }
	case AnimatLayer::connect:  { onbegin_connect(poigl);   break; }

	default: { CCAssert(false, "unknown state"); break; }
	}

	return true;
}

void AnimatLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
	CCPoint poigl = pTouch->getLocation();
	if (!AnimateUtiler::inarea(this, poigl)) { return; }

	switch(cur_state) {
	case AnimatLayer::translat: { onmoved_translate(poigl); break; }
	case AnimatLayer::rotate:   { onmoved_rotate(poigl);    break; }
	case AnimatLayer::scale:    { onmoved_scale(poigl);     break; }
	}
}

void AnimatLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {

}

void AnimatLayer::registerWithTouchDispatcher() {
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, 0, false);
}

bool AnimatLayer::iskey_frame(int index) {
	if (sprcur) {
		AnimateObject *anio = dynamic_cast<AnimateObject*>(sprcur->getUserObject());
		CCAssert(anio, "sprite selected not [bone|animate]");
		return anio->getkey_frame(index) != NULL;
	}
	return false;
}

void AnimatLayer::setkey_frame(int index, bool iskey) {
	if (sprcur) {
		AnimateObject *anio = dynamic_cast<AnimateObject*>(sprcur->getUserObject());
		CCAssert(anio, "sprite selected not [bone|animate]");
		anio->setkey_frame(sprcur, index, iskey);

		anio->prikey_frame();
	}
}

void AnimatLayer::plykey_frame() {
	if (sprcur) {
		playani(sprcur);
	}
}

void AnimatLayer::frame_selected(int index) {
	if (sprcur) {
		AnimateObject *anio = dynamic_cast<AnimateObject*>(sprcur->getUserObject());
		CCAssert(anio, "sprite selected not [bone|animate]");
		KeyFrameObject *ko = anio->getkey_frame(index);
		if (ko) {
			AnimateUtiler::setattr(sprcur, ko);
			if (!anio->isbone()) {
				AnimateUtiler::setframe(sprcur, ko->getkey_frame());
			}
		}
	}
}

void AnimatLayer::playani(CCSprite *spr) {
	AnimateObject *anio = dynamic_cast<AnimateObject*>(spr->getUserObject());
	CCAssert(anio, "sprite not [bone|animate]");
	anio->plykey_frame(spr);

	CCObject *o;
	CCARRAY_FOREACH(spr->getChildren(), o) {
		CCSprite *c = dynamic_cast<CCSprite*>(o);
		if (c) {
			playani(c);
		}
	}
}

void AnimatLayer::draw() {
	CCLayerColor::draw();
	ccDrawColor4B(ccGRAY.r, ccGRAY.g, ccGRAY.b, 125);

	const CCPoint& poi = boneroot->getPosition();
	ccDrawLine(ccp(poi.x, 0), ccp(poi.x, m_tContentSize.height));
	ccDrawLine(ccp(0, poi.y), ccp(m_tContentSize.width, poi.y));
}

void AnimatLayer::drawbone() {
	Q.push(boneroot);

	while(Q.size() > 0) {
		CCSprite *spr = Q.front();
		CCPoint src = convertToNodeSpace(spr->getParent()->convertToWorldSpace(spr->getPosition()));
		ccDrawColor4B(ccRED.r, ccRED.g, ccRED.b, 255);
		ccDrawCircle(src, spr->getContentSize().width * 0.5, 0, 10, false);
				
		CCArray *array = spr->getChildren();
		if (array) {
			CCObject *o;
			CCARRAY_FOREACH(array, o) {
				CCSprite *c = dynamic_cast<CCSprite*>(o);
				if (c && isspr_bone(c)) {
					Q.push(c);

					CCPoint dst = convertToNodeSpace(c->getParent()->convertToWorldSpace(c->getPosition()));
					ccDrawLine(src, dst);
				}
			}
		}

		Q.pop();
	}
}

CCSprite* AnimatLayer::testarea(CCNode *root, const CCPoint& poi) {
	CCSprite *spr = testarea(root, true, poi);
	if (NULL == spr) {
		spr = testarea(root, false, poi);
	}
	return spr;
}

CCSprite* AnimatLayer::testarea(CCNode *root, bool isbone, const CCPoint& poi) {
	CCArray *ac = root->getChildren();

	CCObject *o;
	CCARRAY_FOREACH(ac, o) {
		CCNode *node = (CCNode*)o;
		AnimateObject *anio = dynamic_cast<AnimateObject*>(node->getUserObject());
		if (anio && (anio->isbone() == isbone)) {
			if (AnimateUtiler::inarea(node, poi)) {
				CCSprite *spr = dynamic_cast<CCSprite*>(o);
				CCAssert(spr, "not sprite");
				return spr;
			}
		}

		CCSprite *sprite = testarea(node, isbone, poi);
		if (sprite) { return sprite; }
	}
	return NULL;
}

void AnimatLayer::setcur_state(int next) {
	if (next == cur_state) { return; }

	switch(cur_state) {
	case AnimatLayer::poser: { onclear_poser(); break; }
	default: { break; }
	}

	cur_state = next;
}

bool AnimatLayer::isspr_bone(CCSprite *spr) {
	AnimateObject *anio = dynamic_cast<AnimateObject*>(spr->getUserObject());
	CCAssert(anio, "sprite not [animate|bone]");

	return anio->isbone();
}

SimpleLayer* SimpleLayer::create() {
	SimpleLayer *layer = new SimpleLayer();
	layer->autorelease();
	if (layer->init()) { return layer; }
	return NULL;
}

void SimpleLayer::draw() {
	CCLayer::draw();
	AnimatLayer::instance()->drawbone();
}