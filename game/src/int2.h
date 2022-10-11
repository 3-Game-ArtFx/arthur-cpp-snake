#pragma once

#include <functional>

struct Int2
{
	int x = 0, y = 0;

	Int2 operator *( Int2& a ) { return Int2 { x * a.x, y * a.y }; }
	Int2 operator *( int n ) { return Int2 { x * n, y * n }; }

	Int2 operator /( Int2& a ) { return Int2 { x / a.x, y / a.y }; }
	Int2 operator /( int n ) { return Int2 { x / n, y / n }; }

	Int2 operator +( Int2& a ) { return Int2 { x + a.x, y + a.y }; }
	Int2 operator -( Int2& a ) { return Int2 { x - a.x, y - a.y }; }

	//  required to implement std::unordered_map
	bool operator ==( const Int2& a ) const { return x == a.x && y == a.y; }
};

struct Int2Hasher
{
	size_t operator()( const Int2& a ) const
	{
		//return (size_t) ( a.x + a.y * 10 );
		return std::hash<int>()( a.x ) ^ ( std::hash<int>()( a.y ) << 1 );
	}
};