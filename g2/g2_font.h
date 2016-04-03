#pragma once

namespace g2 {
	void font(char* name, int height);
	void text(int x, int y, char* str);
	void text_flow(char* str);
	int* font_metric(char* str);
	int  font_height();

	namespace Internal {
		extern int last_font_x, last_font_y;

		extern char last_font_c;

		int _text(int x, int y, char* str);
	}
}