#pragma once

#include "tile_entity.h"

class TileSnake : public TileEntity
{
public:
	const Color HEAD_COLOR { 27, 255, 27, 255 };
	const Color BODY_COLOR { 27, 213, 27, 255 };
private:
	int _length;
public:
	TileSnake( const Int2 pos, Level* _level, int length )
		: _length( length ), TileEntity( pos, _level )
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
		return _length == 0 ? HEAD_COLOR : BODY_COLOR;
	}
};