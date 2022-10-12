#include "tile_entity.h"

#include <src/level.h>

TileEntity::TileEntity( const Int2 pos, Level* level )
	: pos( pos ), level( level )
{
	level->add_entity( this );
}

TileEntity::~TileEntity()
{
	level->remove_entity( this );
}


void TileEntity::set_pos( const Int2 new_pos )
{
	level->remove_entity( this );
	pos = new_pos;
	level->add_entity( this );
}