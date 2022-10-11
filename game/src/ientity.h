#pragma once

class IEntity
{
public:
	virtual ~IEntity() {};

	virtual void update( float dt ) = 0;
	virtual void draw() = 0;
};