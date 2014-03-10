#include <stack>
#include "fragment.h"
#include "aniutil.h"

using namespace std;

#define PLIST_LAYER_TAGID 500
#define SELET_LAYER_TAGID 501

MoveLayer* MoveLayer::instance = NULL;

MoveLayer::~MoveLayer() {
	CC_SAFE_RELEASE(cur_rect);
	CC_SAFE_RELEASE(cur_text);
	CC_SAFE_RELEASE(cur_plist);
}

bool MoveLayer::init() {
	if (CCLayer::init()) {
		setTouchEnabled(true);
		return true;
	}
	return false;
}

MoveLayer* MoveLayer::create() {
	MoveLayer *view = new MoveLayer();
	view->autorelease();
	if (view->init()) {	return view; }
	return NULL;
}

MoveLayer* MoveLayer::sharedMoveLayer() {
	if (!instance) {
		instance = new MoveLayer();
		instance->init();
	}
	return instance;
}

void MoveLayer::registerWithTouchDispatcher() {
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, 0, false);
}

bool MoveLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {	
	CCPoint poigl = pTouch->getLocation();	
	if (!AnimateUtiler::inarea(this, poigl)) { return true; }
	
	CCLayerColor *layer = (CCLayerColor*)getChildByTag(PLIST_LAYER_TAGID);
	if (NULL == layer) { return true; }

	poslast = poigl;

	CCObject *o;
	CCSprite *select = NULL;
	CCARRAY_FOREACH(layer->getChildren(), o) {
		CCSprite *sp = (CCSprite*)o;
		sp->removeChildByTag(SELET_LAYER_TAGID, true);

		if (AnimateUtiler::inarea(sp, poigl) && NULL == select)	{
			select = sp;
			CCLayerColor *sc = CCLayerColor::create(ccc4(ccRED.r, ccRED.g, ccRED.b, 120));
			sc->setTag(SELET_LAYER_TAGID);
			sc->setContentSize(sp->getContentSize());
			sp->addChild(sc);
		}
	}

	CC_SAFE_RELEASE(cur_rect);
	CC_SAFE_RELEASE(cur_text);
	if (!select) {
		cur_rect = NULL;
		cur_text = NULL;
	} else {
		CCArray *array = (CCArray*)select->getUserObject();
		CCAssert(array->count() == 2, "rect or png lose");

		CCString *rect = (CCString*)array->objectAtIndex(0);
		cur_rect = CCString::create(rect->getCString());
		CC_SAFE_RETAIN(cur_rect);

		CCString *text = (CCString*)array->objectAtIndex(1);
		cur_text = CCString::create(text->getCString());
		CC_SAFE_RETAIN(cur_text);
	}

	return true;
}

void MoveLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
	CCPoint poigl = pTouch->getLocation();
	if (!AnimateUtiler::inarea(this, poigl)) { return; }

	float dx = poigl.x - poslast.x;
	float dy = poigl.y - poslast.y;
	poslast = poigl;

	CCNode *c = getChildByTag(PLIST_LAYER_TAGID);
	if (NULL == c) { return; }

	CCPoint pos_c = c->getPosition();
	pos_c.x += dx;
	pos_c.y += dy;

	CCSize size_c = c->getContentSize();
	size_c.width * 0.5;
	size_c.height * 0.5;
	if (pos_c.x >  size_c.width)  { pos_c.x =  size_c.width; }
	if (pos_c.x < -size_c.width)  { pos_c.x = -size_c.width; }
	if (pos_c.y >  size_c.height) { pos_c.y =  size_c.height; }
	if (pos_c.y < -size_c.height) { pos_c.y = -size_c.height; }

	c->setPosition(pos_c.x + dx, pos_c.y + dy);
}

void MoveLayer::visit() {
	if (!isVisible()) { return; }

	kmGLPushMatrix();
	transform();

	CCPoint ps = getParent()->convertToWorldSpace(getPosition());
	glEnable(GL_SCISSOR_TEST);
	CCEGLView::sharedOpenGLView()->setScissorInPoints(ps.x, ps.y, m_tContentSize.width, m_tContentSize.height);

	if (m_pChildren) {
		CCObject *o;
		CCARRAY_FOREACH(m_pChildren, o) {
			CCNode *c = (CCNode*)o;
			if (c->getZOrder() < 0) { c->visit(); }
			else {
				break;
			}
		}
		
		draw();

		CCARRAY_FOREACH(m_pChildren, o) {
			CCNode *c = (CCNode*)o;
			if (c->getZOrder() >= 0) { c->visit(); }
			else {
				break;
			}
		}
	} else {
		draw();
	}

	glDisable(GL_SCISSOR_TEST);
	kmGLPopMatrix();
}

void MoveLayer::rempng(const char *key) {
	if (curpngkey.compare(key) == 0) {
		sprite->removeFromParentAndCleanup(true);
		curpngkey.clear();
	}
}

void MoveLayer::setplist(const char *plist) {
	const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(plist);
	CCAssert(path, "plist full path nil");
	
	CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(path);
	if (!dict) {
		CCLog("[setplist error]read plist %s failure!", path);
		return;
	}

	if (NULL == cur_plist) {
		CCAssert(NULL == cur_text, "cur text not nil(no plist load)");
		CCAssert(NULL == cur_rect, "cur rect not nil(no plist load)");
	}

	if (cur_plist && (cur_plist->compare(plist) != 0)) {
		cur_plist->release();
		cur_plist = NULL;
		CC_SAFE_RELEASE(cur_rect);
		CC_SAFE_RELEASE(cur_text);
		cur_rect = NULL;
		cur_text = NULL;
	}
	cur_plist = CCString::create(plist);
	cur_plist->retain();

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist);
	CCLayerColor *layer = (CCLayerColor*)getChildByTag(PLIST_LAYER_TAGID);
	if (NULL == layer) {		
		layer = CCLayerColor::create(ccc4(100, 100, 100, 100));
		layer->setTag(PLIST_LAYER_TAGID);
		layer->setAnchorPoint(CCPointZero);
		layer->setPosition(CCPointZero);
		layer->ignoreAnchorPointForPosition(false);
		addChild(layer);
	}
	layer->removeAllChildrenWithCleanup(true);
	
	CCDictionary *frame = (CCDictionary*)dict->objectForKey("frames");
	CCAssert(frame, "no frames in plist");
	CCDictionary *meta = (CCDictionary*)dict->objectForKey("metadata");	
	CCAssert(meta, "no meta in plist");
	CCString *name = CCString::create(meta->valueForKey("textureFileName")->getCString());
	
	CCObject *o;
	CCArray *keys = frame->allKeys();
	CCARRAY_FOREACH(keys, o) {
		CCString *key = (CCString*)o;
		CCSpriteFrame *sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key->getCString());
		if (NULL == sf) {
			CCLog("[setplist error]load sprite frame %s failure!", key->getCString());
			break;
		}

		float x = sf->getRect().origin.x + sf->getRect().size.width * 0.5;
		float y = sf->getRect().origin.y + sf->getRect().size.height * 0.5;
		y = sf->getTexture()->getContentSize().height - y;

		CCArray *array = CCArray::create();
		array->addObject(key);
		array->addObject(name);
		CCSprite *sp = CCSprite::createWithSpriteFrame(sf);
		sp->setPosition(ccp(x, y));
		sp->setUserObject(array);
		layer->addChild(sp);
		layer->setContentSize(sf->getTexture()->getContentSize());
	}

	dict->release(); // not auto-release
}

void MoveLayer::setpng(const char* key) {
	CCAssert(key, "[setpng] png path key NULL!");

	if (curpngkey.compare(key) == 0) {
		return;
	}

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->textureForKey(key);
	if (!texture) {
		texture = CCTextureCache::sharedTextureCache()->addImage(key);
		if (!texture) {
			CCLog("Load png resource from path %s failure!", key);
			return;
		}
	}

	CCImage image;
	if (!image.initWithImageFile(key)) {
		CCLog("Initialize image with file %s failure!", key);
		return;
	}

	vector<CCRect> pngrects;
	if (!spliter.split_image(&image, pngrects)) {
		CCLog("Split image file %s into small rectangles failure!", key);
		return;
	}

	if (sprite) {
		sprite->removeFromParentAndCleanup(true);
	}

	curpngkey = string(key);
}

void MoveLayer::create_sprite_fragment(CCTexture2D *texture) {
	sprite = CCSprite::createWithTexture(texture);
	sprite->setPosition(ccp(0, 0));
	sprite->setAnchorPoint(ccp(0, 0));
	sprite->ignoreAnchorPointForPosition(false);

	addChild(sprite);
}

const char* MoveLayer::getcur_pngkey() {
	return NULL;
}
