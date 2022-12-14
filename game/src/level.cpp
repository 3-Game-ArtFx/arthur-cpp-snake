#include "level.h"

Level::Level()
{
	//  reset zoom & rotation
	_camera.zoom = 1.0f;
	_camera.rotation = 0.0f;
	//  offset to screen center
	_camera.offset = Vector2 {
		(float) SCREEN_WIDTH / 2,
		(float) SCREEN_HEIGHT / 2,
	};
	//  origin to map's center
	_camera.target = Vector2 {
		(float) WIDTH * TILE_SIZE / 2 + TILE_MARGIN * ( WIDTH - 1 ) / 2,
		(float) HEIGHT * TILE_SIZE / 2 + TILE_MARGIN * ( HEIGHT - 1 ) / 2 - PADDING / 4,
	};
}

void Level::update( float dt )
{
	//  shake
	if ( _shake_intensity > 0.0f )
	{
		float offset = GetRandomValue( -1, 1 );
		_shake_intensity = std::max( 0.0f, _shake_intensity - dt * 1.5f );
		_camera.rotation = offset * _shake_intensity;
	}
	//_camera.rotation += dt * 5.0f;
}

void Level::draw()
{
	//  render tile map (w/ margins)
	_x_margin = 0, _y_margin = 0;
	for ( _y = 0; _y < HEIGHT; _y++ )
	{
		for ( _x = 0; _x < WIDTH; _x++ )
		{
			Color color = LIGHTGRAY;

			//  get tile entity's color
			Int2 pos { _x, _y };
			if ( has_entity_at( pos ) )
			{
				TileEntity* tile = get_entity_at( pos );
				color = tile->get_color();
			}

			//  draw rectangle
			draw_rectangle( color );

			//  margin
			_x_margin += TILE_MARGIN;
		}

		_y_margin += TILE_MARGIN;
		_x_margin = 0;
	}
}

void Level::draw_rectangle( Color color )
{
	DrawRectangle( _x * TILE_SIZE + _x_margin, _y * TILE_SIZE + _y_margin, TILE_SIZE, TILE_SIZE, color );
}

void Level::shake( float intensity )
{
	_shake_intensity += intensity;
}

bool Level::add_entity( TileEntity* entity )
{
	Int2 pos = entity->get_pos();
	if ( has_entity_at( pos ) ) return false;

	_entities[pos] = entity;
	return true;
}

bool Level::remove_entity( TileEntity* entity )
{
	Int2 pos = entity->get_pos();
	if ( !has_entity_at( pos ) ) return false;

	_entities.erase( pos );
	return true;
}

bool Level::has_entity_at( const Int2 pos )
{
	return _entities.find( pos ) != _entities.end();
}

TileEntity* Level::get_entity_at( const Int2 pos )
{
	return _entities[pos];
}

bool Level::is_in_bounds( const Int2 pos )
{
	if ( pos.x < 0 || pos.x >= WIDTH ) return false;
	if ( pos.y < 0 || pos.y >= HEIGHT ) return false;

	return true;
}

Int2 Level::get_random_free_position()
{
	Int2 pos;

	do
	{
		pos.x = rand() % WIDTH;
		pos.y = rand() % HEIGHT;
	}
	while ( has_entity_at( pos ) );

	return pos;
}

Int2 Level::get_center_position()
{
	return Int2 { WIDTH / 2, HEIGHT / 2 };
}