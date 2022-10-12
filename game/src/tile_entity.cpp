#include "tile_entity.h"

#include <src/level.h>

TileEntity::TileEntity( const Int2 pos, Level* level )
	: pos( pos ), _level( level )
{
	_level->add_entity( this );
}

TileEntity::~TileEntity()
{
	_level->remove_entity( this );
}


void TileEntity::set_pos( const Int2 new_pos )
{
	_level->remove_entity( this );
	pos = new_pos;
	_level->add_entity( this );
}