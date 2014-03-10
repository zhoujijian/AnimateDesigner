#ifndef _IMAGE_SPLITER_H_
#define _IMAGE_SPLITER_H_

#include <vector>
#include <stack>
#include "cocos2d.h"

using namespace cocos2d;

typedef unsigned char u8;

struct ui_pixel {
public:
	int row;
	int col;
	int tag;
	ui_pixel(int r, int c, int t) : row(r), col(c), tag(t) { }
};

struct ui_rect {
public:
	int left;
	int right;
	int top;
	int bottom;
	ui_rect(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b) { }
};

class ImageSpliter {
public:
	bool split_image(CCImage *image, std::vector<CCRect>& rects);
	void dfsarea(u8 *data, u8 *alpha, int r, int c, int W, int H, CCRect& rt);
	void saverect(CCImage *image, const CCRect& rect);

private:
	void dfs_next(u8* data, u8 *alpha, int row, int col, std::stack<ui_pixel>& s, int W, int H, ui_rect& rect);

private:
	std::vector<CCRect> image_rects;
};

#endif