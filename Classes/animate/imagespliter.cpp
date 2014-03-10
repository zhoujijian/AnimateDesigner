#include "imagespliter.h"

using namespace std;

#define alpha_pixel(r, c) ((r) * W * 4 + (c) * 4 + 3)
#define alpha_signa(r, c) ((r) * W + (c))

bool ImageSpliter::split_image(CCImage *image, vector<CCRect>& rects) {
	if (!image->hasAlpha()) { return false; }

	int W = image->getWidth();
	int H = image->getHeight();
	u8 *alpha = new u8[W * H];
	memset(alpha, 0, sizeof(u8) * W * H);

	u8 *data = image->getData();
	for (int r = 0; r < H; ++ r) {
		for (int c = 0; c < W; ++ c) {
			if (!alpha[alpha_signa(r, c)] && data[alpha_pixel(r, c)] > 0) {
				CCRect rect;
				dfsarea(data, alpha, r, c, W, H, rect);
				rects.push_back(rect);
			}
		}
	}
	delete []alpha;
	return true;
}

void ImageSpliter::dfsarea(u8 *data, u8 *alpha, int r, int c, int W, int H, CCRect& rt) {
	stack<ui_pixel> s;
	ui_pixel pixel(r, c, 0);
	s.push(pixel);

	ui_rect rect(c, c, r, r);
	while(!s.empty()) {
		const ui_pixel& cur = s.top();
		switch(cur.tag) {
		case 0:  { dfs_next(data, alpha, cur.row - 1, cur.col, s, W, H, rect); break; }
		case 1:  { dfs_next(data, alpha, cur.row + 1, cur.col, s, W, H, rect); break; }
		case 2:  { dfs_next(data, alpha, cur.row, cur.col - 1, s, W, H, rect); break; }
		case 3:  { dfs_next(data, alpha, cur.row, cur.col + 1, s, W, H, rect); break; }
		default: { s.pop(); break; }
		}
	}
	CCAssert(rect.left <= rect.right && rect.bottom <= rect.top, "Invalid rect!");
	for (int rr = rect.bottom; rr < rect.top; ++ rr) {
		for (int cc = rect.left; cc < rect.right; ++ cc) {
			alpha[alpha_signa(rr, cc)] = 1;
		}
	}
	rt.origin.x    = rect.left;
	rt.origin.y    = H - rect.top;
	rt.size.width  = rect.right - rect.left + 1;
	rt.size.height = rect.top - rect.bottom + 1;
}

void ImageSpliter::dfs_next(u8 *data, u8 *alpha, int row, int col, stack<ui_pixel>& s, int W, int H, ui_rect& rect) {
	s.top().tag ++;

	if (row >= 0 && row < H - 1 && col >= 0 && col < W - 1 &&
		data[alpha_pixel(row, col)] && !alpha[alpha_signa(row, col)])
	{		
		s.push(ui_pixel(row, col, 0));
		alpha[alpha_signa(row, col)] = 1;

		if (rect.left   > col) { rect.left   = col; }
		if (rect.right  < col) { rect.right  = col; }
		if (rect.top    < row) { rect.top    = row; }
		if (rect.bottom > row) { rect.bottom = row; }		
	}
}
