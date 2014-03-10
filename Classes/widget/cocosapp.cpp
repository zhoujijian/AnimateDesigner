#include "cocosapp.h"
#include "cocosframe.h"

IMPLEMENT_APP(wxAppCocos2d);

void AppCocos2d::Init(HWND hwnd, float width, float height) {
	CCEGLView::sharedOpenGLView()->setFrameSize(width, height, hwnd);
	applicationDidFinishLaunching();
}

int AppCocos2d::run() {
	CCDirector::sharedDirector()->mainLoop();
	return 1;
}

bool wxAppCocos2d::OnInit() {
	CocosFrame *frame = new CocosFrame();
	frame->CentreOnScreen();

	frame->Show();
	return true;
}
