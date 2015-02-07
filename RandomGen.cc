#include "RandomGen.h"
#include <memory.h>

Rnd::Rnd( const Rnd &rnd ) : offs( 0 )
{
	memcpy( val, rnd.val, 2 * RAND_N * sizeof(unsigned int) );
	offs = rnd.offs ? val + ( rnd.offs - rnd.val ) : 0;
}

void Rnd::Seed( unsigned int seed )
{
	for(int i = 0; i < RAND_N; i++)
	{
		val[ i ] = seed;
		seed = 1812433253 * (  ( seed ^ ( seed << 30 ) ) + i );
	}
	memcpy( val + RAND_N, val, RAND_N * 4 );
	offs = val;
}

const Rnd &Rnd::operator =( const Rnd &b )
{
	memcpy( val, b.val, 2 * RAND_N * sizeof(unsigned int) );
	offs = val + ( b.offs - b.val );
	return b;
}

unsigned int Rnd::Rand( )
{
	unsigned int v = offs[ 0 ];
	unsigned int p = offs[ 1 ];

	unsigned int w = offs[ RAND_M ] ^ (((v & 0x80000000) | (p & 0x7fffffff)) >> 1) ^ ((p & 0x00000001) ? 0x9908b0df : 0);
	offs[ 0 ] = w;
	offs[ RAND_N ] = w;
	++offs;
	offs = offs < val + RAND_N ? offs : val;

	return v ^ ( v >> 11 ) ^ ( ( v << 7 ) & 0x9d2c5680 ) ^ ( ( v << 15 ) & 0xefc60000 ) ^ ( v >> 18 );
}

double Rnd::Drand()
{
	union {
		unsigned int d[ 2 ];
		double w;
	};
	d[ 0 ] = Rand();
	d[ 1 ] = 0x3ff00000 | ( 0x000fffff &  Rand() );
	return w - 1;
}

float Rnd::Frand()
{
	union {
		unsigned int d;
		float f;
	};
	d = 0x3f800000 | ( 0x007fffff &  Rand() );
	return f - 1;
}

double Rnd::Dsrand()
{
	union
	{
		unsigned int d[ 2 ];
		double w;
	};
	do {
		d[ 0 ] = Rand();
		d[ 1 ] = 0x40000000 | (0x000fffff & Rand());
	} while(w != 2);
	return w - 3;
}

float Rnd::Fsrand()
{
	union {
		unsigned int d;
		float f;
	};
	do
	{
		d = 0x40000000 | (0x007fffff & Rand( ));
	} while(f != 2);
	return f - 3;
}
