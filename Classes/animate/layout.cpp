#include "layout.h"
#include "frameip.h"
#include "fragment.h"
#include "imagespliter.h"
#include "luagenerator.h"
#include "animatlayer.h"
#include "aniutil.h"

using namespace std;

AnimatLayout::AnimatLayout() : animlayer(NULL) {

}

AnimatLayout::~AnimatLayout() {
}

AnimatLayout* AnimatLayout::create(float width, float height) {	
	AnimatLayout *layout = new AnimatLayout();
	layout->autorelease();
	if (layout->init(width, height)) {
		return layout;
	}
	return NULL;
}

void AnimatLayout::on_clear_clicked(CCObject *sender, CCControlEvent event) {
	AnimatLayer *animat_layer = (AnimatLayer*)animlayer->getChildByTag(DEBUG_SHOW_LAYER_TAGID);
	if (animat_layer->getcur_state() < AnimatLayer::max_state) {
		// animat_layer->get_current_state(animat_layer->get_current_state())->on_clear();
	}
}

void AnimatLayout::on_save_clicked(CCObject *sender, CCControlEvent event) {
	LuaGenerator::generator()->save_generat();
}

CCControlButton* AnimatLayout::get_oper_button(int state) {
	CCAssert(state >= AnimatLayer::creat && state < AnimatLayer::max_state, "state out range");
	CCNode *layer = animlayer->getChildByTag(OPER_ANIMAT_NODE_TAGID);
	CCControlButton *b = (CCControlButton*)layer->getChildByTag(state + BUTTON_MINTAG);
	return b;
}

void AnimatLayout::nextmode(int state) {
	CCAssert(state < AnimatLayer::max_state, "invalid state parameter!");

	int cur = AnimatLayer::instance()->getcur_state();
	if (cur != AnimatLayer::max_state) {
		CCControlButton *prev = get_oper_button(cur);
		prev->setBackgroundSpriteForState(CCScale9Sprite::create("button.png"), CCControlStateNormal);
	}
	CCControlButton *b = get_oper_button(state);
	b->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateNormal);

	AnimatLayer::instance()->setcur_state(state);
}

CCLayerColor* AnimatLayout::create_mode_layer() {
	CCControlButton *save = AnimateUtiler::simple_button("save");
	save->setTag(BUTTON_SAVER_TAGID);
	save->addTargetWithActionForControlEvents(this, cccontrol_selector(AnimatLayout::on_save_clicked), CCControlEventTouchDown);

	CCLayerColor *layer = CCLayerColor::create(ccc4(ccGRAY.r, ccGRAY.g, ccGRAY.b, 100));
	layer->setTag(DEBUG_MODE_LAYER_TAGID);
	layer->addChild(save);
	AnimateUtiler::layout(layer, AnimateUtiler::HLR);

	return layer;
}

LayerFrame* AnimatLayout::create_frame_layer(float width, float height) {
	LayerFrame *frame_layer = LayerFrame::create(ccc4(100, 100, 100, 50), width, height);
	frame_layer->setTag(DEBUG_FRAME_LAYER_TAGID);
	frame_layer->registerWithTouchDispatcher();
	return frame_layer;
}

void AnimatLayout::onmode_click(CCObject *sender, CCControlEvent event) {
	int state[BUTTON_MAXTAG - BUTTON_MINTAG] = {
		AnimatLayer::creat,		
		AnimatLayer::rotate,
		AnimatLayer::translat,
		AnimatLayer::scale,			
		AnimatLayer::poser,
		AnimatLayer::connect,
		AnimatLayer::append
	};

	int tag = ((CCNode*)sender)->getTag();
	CCAssert(BUTTON_MINTAG <= tag && tag < BUTTON_MAXTAG);

	nextmode(state[tag - BUTTON_MINTAG]);
}

CCLayerColor* AnimatLayout::create_operanimat_layer() {
	const char *name[BUTTON_MAXTAG - BUTTON_MINTAG] = {
		"creat", "rotat", "trans", "scale", "poser", "conct", "apend"
	};

	CCLayerColor *layer = CCLayerColor::create(ccc4(ccGRAY.r, ccGRAY.g, ccGRAY.b, 100));
	layer->setTag(OPER_ANIMAT_NODE_TAGID);

	for (int i = BUTTON_MINTAG; i < BUTTON_MAXTAG; ++ i) {
		int index = i - BUTTON_MINTAG;
		CCControlButton *b = AnimateUtiler::simple_button(name[index]);
		b->setTag(i);
		b->addTargetWithActionForControlEvents(this,
			cccontrol_selector(AnimatLayout::onmode_click), CCControlEventTouchDown);
		layer->addChild(b);
	}
	AnimateUtiler::layout(layer, AnimateUtiler::HLR);
	return layer;
}

AnimatLayer* AnimatLayout::create_animat_layer(float width, float height) {
	AnimatLayer *show_layer = AnimatLayer::create(ccc4(100, 125, 0, 125), width, height);
	show_layer->setTag(DEBUG_SHOW_LAYER_TAGID);
	show_layer->setTouchEnabled(true);
	return show_layer;
}

CCLayerColor* AnimatLayout::create_operlevel_layer(LayerFrame *frame_layer) {
	CCControlButton *add = AnimateUtiler::simple_button("ADD");
	CCControlButton *del = AnimateUtiler::simple_button("DEL");
	CCControlButton *ins = AnimateUtiler::simple_button("KEY");
	CCControlButton *ply = AnimateUtiler::simple_button("PLY");
	add->addTargetWithActionForControlEvents(frame_layer, cccontrol_selector(LayerFrame::add_layer), CCControlEventTouchDown);
	del->addTargetWithActionForControlEvents(frame_layer, cccontrol_selector(LayerFrame::remove_layer), CCControlEventTouchDown);
	ins->addTargetWithActionForControlEvents(frame_layer, cccontrol_selector(LayerFrame::set_keyframe), CCControlEventTouchDown);
	ply->addTargetWithActionForControlEvents(frame_layer, cccontrol_selector(LayerFrame::play_frame), CCControlEventTouchDown);

	CCLayerColor *layer = CCLayerColor::create();
	layer->addChild(del);
	layer->addChild(add);
	layer->addChild(ins);
	layer->addChild(ply);
	AnimateUtiler::layout(layer, AnimateUtiler::VTB);

	return layer;
}

bool AnimatLayout::init(float width, float height) {
	setContentSize(CCSizeMake(width, height));

	CCLayerColor *mode_layer = create_mode_layer();
	CCLayerColor *oper_animat_layer = create_operanimat_layer();
	AnimatLayer *show_layer = create_animat_layer(width * 0.8,
		height * 0.8 - mode_layer->getContentSize().height - oper_animat_layer->getContentSize().height);
	animlayer = CCNode::create();
	animlayer->addChild(oper_animat_layer);
	animlayer->addChild(show_layer);
	animlayer->addChild(mode_layer);
	AnimateUtiler::layout(animlayer, AnimateUtiler::VBT);
		
	MoveLayer *movelayer = MoveLayer::sharedMoveLayer();
	movelayer->setContentSize(CCSizeMake(width - animlayer->getContentSize().width, height * 0.8));

	CCNode *node = CCNode::create();
	node->addChild(animlayer);
	node->addChild(movelayer);
	AnimateUtiler::layout(node, AnimateUtiler::HLR);
	
	LayerFrame *frame_layer = create_frame_layer(width, height * 0.2);
	CCLayerColor *oper_layer = create_operlevel_layer(frame_layer);
	CCNode *node_frame = CCNode::create();
	node_frame->addChild(oper_layer);
	node_frame->addChild(frame_layer);
	AnimateUtiler::layout(node_frame, AnimateUtiler::HLR);
	
 	addChild(node_frame);
	addChild(node);
	AnimateUtiler::layout(this, AnimateUtiler::VBT);

	nextmode(AnimatLayer::creat);
	return true;
}
