#include "cocoswindow.h"
#include "cocos2d.h"

using namespace cocos2d;

BEGIN_EVENT_TABLE(CocosWindow, wxControl)
	EVT_TIMER(COCOS2D_TIMER, CocosWindow::OnTimer)
END_EVENT_TABLE()

CocosWindow::CocosWindow() {
	Init();
}

bool CocosWindow::Create(wxWindow *parent, wxWindowID id,
	const wxPoint& pos /* = wxDefaultPosition */,
	const wxSize& size /* = wxDefaultSize */, long style /* = 0 */,
	const wxValidator& validator /* = wxDefaultValidator */,
	const wxString& name /* = wxControlNameStr */)
{
	if (!wxControl::Create(parent, id, pos, size, style, validator)) {
		return false;
	}
	return true;
}

WXLRESULT CocosWindow::MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) {
	WXLRESULT ret = wxWindow::MSWWindowProc(nMsg, wParam, lParam);
	CCEGLView::sharedOpenGLView()->WindowProc(nMsg, wParam, lParam);
	return ret;
}

void CocosWindow::Start() {
	app_cocos.Init((HWND)GetHWND(), COCOS2D_WINDOW_WIDTH, COCOS2D_WINDOW_HEIGH);
	draw_timer.Start(30);
}

void CocosWindow::StopCocos() {
	draw_timer.Stop();
	CCDirector::sharedDirector()->end();
	app_cocos.run();
}

void CocosWindow::OnTimer(wxTimerEvent& evt) {
	app_cocos.run();
}