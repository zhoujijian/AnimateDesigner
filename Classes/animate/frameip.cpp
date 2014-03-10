#include "frameip.h"
#include "aniutil.h"
#include "animatlayer.h"

LayerFrame::LayerFrame() : cur_layer_index(-1), layerid(0), layer_count(0), cur_frame_selected(-1) {
	memset(frame_local, 0, sizeof(frame_local));
}

LayerFrame::~LayerFrame() {

}

LayerFrame* LayerFrame::create(const ccColor4B& color, GLfloat width, GLfloat height) {
	LayerFrame *layer = new LayerFrame();
	if (layer->initWithColor(color, width, height)) {		
		layer->autorelease();
		layer->init_layout(width, height);
		return layer;
	}
	return NULL;
}

void LayerFrame::init_layout(GLfloat width, GLfloat height) {
	// TODO => add button, etc.
}

float LayerFrame::get_frame_header_height() {
	return FRAME_LINE_LONGH + FRAME_UNIT_WIDTH + FRAME_NUMBER_H;
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

void LayerFrame::set_key_frame(int frameid) {
	CCAssert(frameid >= 0 && frameid < MAX_FRAME_COUNT, "Invalid frame-id parameter!");
	frame_local[frameid].is_keyframe = true;
}

void LayerFrame::set_keyframe(CCObject *sender, CCControlEvent evt) {
	if (cur_frame_selected >= 0) {
		frame_local[cur_frame_selected].is_keyframe = !frame_local[cur_frame_selected].is_keyframe;

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
		float x = (i + 1) * FRAME_UNIT_WIDTH;
		if (x >= m_tContentSize.width) { return; }

		ccDrawColor4B(ccGREEN.r, ccGREEN.g, ccGREEN.b, 255);
		if (i % 5 != 0) {
			ccDrawLine(ccp(x, y), ccp(x, y - FRAME_LINE_SHORTH));
		} else {
			ccDrawLine(ccp(x, y), ccp(x, y - FRAME_LINE_LONGH));
			if (frame_local[i].number == NULL) {
				CCString *str = CCString::createWithFormat("%d", i);
				frame_local[i].number = CCLabelBMFont::create(str->getCString(), "fonts/bitmapFontChinese.fnt");
				frame_local[i].number->setScale(0.35);
				frame_local[i].number->setPosition(ccp(x,
					y - FRAME_LINE_LONGH - FRAME_UNIT_WIDTH - frame_local[i].number->getContentSize().height));
				addChild(frame_local[i].number);
			}
		}

		// key frame
		if (AnimatLayer::instance()->iskey_frame(i)) {
			ccDrawSolidRect(ccp(x - FRAME_UNIT_WIDTH / 2, y - FRAME_LINE_LONGH),
					ccp(x + FRAME_UNIT_WIDTH / 2, y - FRAME_LINE_LONGH - FRAME_UNIT_WIDTH),
					ccc4f(ccBLUE.r / 255, ccBLUE.g / 255, ccBLUE.b / 255, 1.0));
		}
	}
}
bool LayerFrame::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {	
	if (AnimateUtiler::inarea(this, pTouch->getLocation())) {
		CCPoint poi_layer = convertToNodeSpace(pTouch->getLocation());
		if (poi_layer.y > m_tContentSize.height - get_frame_header_height()) {
			if (poi_layer.x >= FRAME_UNIT_WIDTH) {
				int frame_index = poi_layer.x / FRAME_UNIT_WIDTH - 1;
				cur_frame_selected = frame_index;
				AnimatLayer::instance()->frame_selected(frame_index);
			}
		} else {
			int selected = (m_tContentSize.height - poi_layer.y - get_frame_header_height()) / RECT_LAYER_HEIGHT;
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

	if (layer_count > 0) {
		ccDrawColor4B(ccRED.r, ccRED.g, ccRED.b, 255);		
		for (int i = 0; i <= layer_count; ++ i) {
			float y = m_tContentSize.height - i * RECT_LAYER_HEIGHT - get_frame_header_height();
			ccDrawLine(ccp(0, y), ccp(m_tContentSize.width, y));
	    }
	}

	if (cur_layer_index >= 0) {
		float y = m_tContentSize.height - (cur_layer_index + 1) * RECT_LAYER_HEIGHT - get_frame_header_height();		
		ccDrawSolidRect(ccp(0, y - 1), ccp(m_tContentSize.width, y + RECT_LAYER_HEIGHT),
				ccc4f(ccGREEN.r / 255, ccGREEN.g / 255, ccGREEN.b / 255, 0.5));
	}

	if (cur_frame_selected >= 0) {
		float x = cur_frame_selected * FRAME_UNIT_WIDTH + FRAME_UNIT_WIDTH;
		ccDrawSolidRect(ccp(x, 0), ccp(x + FRAME_UNIT_WIDTH, m_tContentSize.height),
			ccc4f(ccGREEN.r / 255, ccGREEN.g / 255, ccGREEN.b / 255, 0.25));
	}

	draw_frame_line();
}
