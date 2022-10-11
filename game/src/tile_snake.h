#pragma once

#include "tile_entity.h"

class TileSnake : public TileEntity
{
public:
	const Color HEAD_COLOR { 27, 255, 27, 255 };
	const Color BODY_COLOR { 27, 213, 27, 255 };
private:
	int length;
public:
	TileSnake( const Int2 pos, Level* level, int length )
		: length( length ), TileEntity( pos, level )
	{}

	Color get_color() override
	{
		/*return Color
		{
			27,
			(unsigned char) ( std::max( 55, 255 - length * 5 ) ),
			27,
			255,
		};*/
		return length == 0 ? HEAD_COLOR : BODY_COLOR;
	}
};