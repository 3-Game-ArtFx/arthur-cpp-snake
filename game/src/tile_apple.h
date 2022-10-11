#pragma once

#include "tile_entity.h"

class TileApple : public TileEntity
{
public:
	TileApple( const Int2 pos, Level* level )
		: TileEntity( pos, level )
	{}

	void eat()
	{
		set_pos( level->get_random_free_position() );
	}

	Color get_color() override
	{
		return RED;
	}
};