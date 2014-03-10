#ifndef _COCOS_2D_APP_H_
#define _COCOS_2D_APP_H_

#include "wx/wx.h"
#include "cocos2d.h"
#include "AppDelegate.h"

using namespace cocos2d;

class AppCocos2d : public AppDelegate {
public:
	void Init(HWND hwnd, float width, float height);
	int run();
};

class wxAppCocos2d : public wxApp {
public:
	virtual bool OnInit();
};

#endif