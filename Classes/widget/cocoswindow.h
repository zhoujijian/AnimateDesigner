#ifndef _COCOS_2D_WINDOW_H_
#define _COCOS_2D_WINDOW_H_

#include "wx/wx.h"
#include "cocosapp.h"

#define COCOS2D_TIMER 100
#define COCOS2D_WX_WINDOW_WIDTH 800
#define COCOS2D_WX_WINDOW_HEIGH 480
#define COCOS2D_WINDOW_WIDTH    800
#define COCOS2D_WINDOW_HEIGH    480

#define APP_WINDOW_WIDTH        1000
#define APP_WINDOW_HEIGH        700

class CocosWindow : public wxControl {
public:
	CocosWindow();
	// ~CocosWindow();

	CocosWindow(wxWindow *parent, wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = 0,
		const wxValidator& validator = wxDefaultValidator,
		const wxString& name = wxControlNameStr) : draw_timer(this, COCOS2D_TIMER)
	{
		Create(parent, id, pos, size, style, validator, name);
	}

	bool Create(wxWindow *parent, wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = 0,
		const wxValidator& validator = wxDefaultValidator,
		const wxString& name = wxControlNameStr);

	void Init() { }
	void OnTimer(wxTimerEvent& evt);
	void Start();
	void StopCocos();
	wxSize DoGetBestSize() const { return wxSize(COCOS2D_WX_WINDOW_WIDTH, COCOS2D_WX_WINDOW_HEIGH); }

	virtual WXLRESULT MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam);

private:
	wxTimer draw_timer;
	AppCocos2d app_cocos;

private:
	DECLARE_EVENT_TABLE()
};

#endif