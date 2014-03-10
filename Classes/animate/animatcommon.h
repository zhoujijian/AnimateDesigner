#ifndef _ANIMAT_COMMON_H_
#define _ANIMAT_COMMON_H_

#define MAX_PNG_PATH_LENGTH    128
#define MAX_KEY_FRAME_COUNT    64

#define MAX_PNG_COUNT          32
#define MAX_PNG_RECT_COUNT     128
#define MAX_PATH_LENG          64
#define MAX_FRAME_COUNT        128

#include <string>
#include <vector>

using namespace std;

struct LuaPngRect {
	int rectid;
	float x, y;
	float width;
	float height;
};

struct LuaPngInfo {
	int pngid;
	char png_path[MAX_PNG_PATH_LENGTH];
	LuaPngRect png_rect[MAX_PNG_RECT_COUNT];
	int rect_count;
};

struct LuaRectSpriteFrame {
	float orix;
	float oriy;
	float width;
	float heigt;
	char png_path[MAX_PNG_PATH_LENGTH];
};

struct LuaFrameAttribute {
	float posx;
	float posy;
	float scalex;
	float scaley;
	float rotate;
	LuaRectSpriteFrame rect_sprite_frame;
	int key_frame_id;
};

struct LuaKeySprite {
	LuaFrameAttribute key_frame_attribute[MAX_KEY_FRAME_COUNT];
	int key_frame_count;
	int rect_sprite_id;
};

typedef enum {
	Solution = 0,
	Folder,
	Filer,
	Project
} CoKind;

class CoConfig {
public:
	~CoConfig();
	CoConfig() { }
	CoConfig(CoKind k, const string& p) : kind(k), path(p) { }

	string path;
	string alias; // needed for folder alias
	CoKind kind;
	vector<CoConfig*> files;
	vector<CoConfig*> folders;
};

#endif
