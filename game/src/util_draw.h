#pragma once

#include <raylib.h>

namespace util
{
	void draw_centered_text( const char* text, int x, int y, int font_size, Color color )
	{
		Vector2 text_size = MeasureTextEx( GetFontDefault(), text, font_size, 1.0f );

		DrawText( text, x - text_size.x / 2, y - text_size.y / 2, font_size, color );
	}
}