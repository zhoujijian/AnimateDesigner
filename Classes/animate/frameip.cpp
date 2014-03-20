#include "frameip.h"
#include "aniutil.h"
#include "animatlayer.h"

LayerFrame::LayerFrame() : cur_layer_index(-1), layerid(0), layer_count(0), cur_frame_selected(-1) {
}

LayerFrame::~LayerFrame() {

}

LayerFrame* LayerFrame::create(const ccColor4B& color, GLfloat width, GLfloat height) {
	LayerFrame *layer = new LayerFrame();
	if (layer->initWithColor(color, width, height)) {		
		layer->autorelease();
		layer->init_layout();
		return layer;
	}
	return NULL;
}

void LayerFrame::init_layout() {
	const CCSize& size = m_tContentSize;
	for (int i = 0; i < MAX_FRAME_COUNT; i += 5) {
		float x = (i + 1) * UNIT_WIDTH;

		if (x < size.width) {
			CCString *str = CCString::createWithFormat("%d", i);
			CCNode *number = CCLabelBMFont::create(str->getCString(), "fonts/bitmapFontChinese.fnt");
			number->setScale(0.35);
			number->setPosition(ccp(x,
				size.height - LINE_LONGH - UNIT_WIDTH - number->getContentSize().height));
			addChild(number);
		}
	}
}

float LayerFrame::header_H() {
	return LINE_LONGH + UNIT_WIDTH + NUMBER_H;
}

void LayerFrame::add_layer(CCObject *sender, CCControlEvent evt) {	
	rect_layer[layer_count ++] = layerid ++;
}

void LayerFrame::remove_layer(CCObject *sender, CCControlEvent evt) {
    if (cur_layer_index >= 0) {
		if (cur_layer_index + 1 < layer_count) {
			for (int i = cur_layer_index; i < layer_count - 1; ++ i) {
				rect_layer[i] = rect_layer[i + 1];
		    }
		}		
		-- layer_count;
		if (cur_layer_index >= layer_count) {
			-- cur_layer_index;
		} else {
			if (layer_count <= 0) {
				cur_layer_index = -1;
			}
		}
	}
}

void LayerFrame::set_keyframe(CCObject *sender, CCControlEvent evt) {
	if (cur_frame_selected >= 0) {
		bool iskey = AnimatLayer::instance()->iskey_frame(cur_frame_selected);
		AnimatLayer::instance()->setkey_frame(cur_frame_selected, !iskey);
	}
}

void LayerFrame::play_frame(CCObject *sender, CCControlEvent evt) {
	AnimatLayer::instance()->plykey_frame();
}

void LayerFrame::registerWithTouchDispatcher() {
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}

void LayerFrame::draw_frame_line() {
	float y = m_tContentSize.height;
	for (int i = 0; i < MAX_FRAME_COUNT; ++ i) {
		float x = (i + 1) * UNIT_WIDTH;
		if (x >= m_tContentSize.width) { return; }

		ccDrawColor4B(ccGREEN.r, ccGREEN.g, ccGREEN.b, 255);
		if (i % 5 != 0) {
			ccDrawLine(ccp(x, y), ccp(x, y - LINE_SHORTH));
		} else {
			ccDrawLine(ccp(x, y), ccp(x, y - LINE_LONGH));
		}

		// key frame
		if (AnimatLayer::instance()->iskey_frame(i)) {
			ccDrawSolidRect(ccp(x - UNIT_WIDTH * 0.5, y - LINE_LONGH),
					ccp(x + UNIT_WIDTH * 0.5, y - LINE_LONGH - UNIT_WIDTH),
					ccc4FFromccc3B(ccBLUE));
		}
	}
}
bool LayerFrame::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {	
	if (AnimateUtiler::inarea(this, pTouch->getLocation())) {
		CCPoint poi_layer = convertToNodeSpace(pTouch->getLocation());
		if (poi_layer.y > m_tContentSize.height - header_H()) {
			if (poi_layer.x >= UNIT_WIDTH) {
				int frame_index = poi_layer.x / UNIT_WIDTH - 1;
				cur_frame_selected = frame_index;
				AnimatLayer::instance()->frame_selected(frame_index);
			}
		} else {
			int selected = (m_tContentSize.height - poi_layer.y - header_H()) / RECT_HEIGHT;
			if (selected < layer_count) {
				cur_layer_index = selected;
			}
		}
	}
	
	// NO TOUCHMOVE / TOUCHEND [I suppose so, Jijian.Zhou]
	return false;
}

void LayerFrame::draw() {
	CCLayerColor::draw();

	ccColor4F green = ccc4FFromccc3B(ccGREEN);
	const CCSize& size = m_tContentSize;

	if (layer_count > 0) {
		ccDrawColor4B(ccRED.r, ccRED.g, ccRED.b, 255);		
		for (int i = 0; i <= layer_count; ++ i) {
			float y = size.height - i * RECT_HEIGHT - header_H();
			ccDrawLine(ccp(0, y), ccp(size.width, y));
	    }
	}

	if (cur_layer_index >= 0) {
		float y = size.height - (cur_layer_index + 1) * RECT_HEIGHT - header_H();		
		ccDrawSolidRect(ccp(0, y - 1), ccp(size.width, y + RECT_HEIGHT),
			ccc4f(green.r, green.g, green.b, 0.5));
	}

	if (cur_frame_selected >= 0) {
		float x = cur_frame_selected * UNIT_WIDTH + UNIT_WIDTH;
		ccDrawSolidRect(ccp(x, 0), ccp(x + UNIT_WIDTH, size.height),
			ccc4f(green.r, green.g, green.b, 0.25));
	}

	draw_frame_line();
}
