#pragma once

#include <raylib.h>

#include <src/int2.h>
#include <src/level.fwd.h>

class TileEntity
{
protected:
	Int2 pos;
	Level* level;
public:
	TileEntity( const Int2 pos, Level* level );
	virtual ~TileEntity();

	void set_pos( const Int2 new_pos );
	Int2 get_pos() { return pos; }

	virtual Color get_color() { return RAYWHITE; }
};