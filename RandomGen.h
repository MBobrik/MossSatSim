#pragma once

class Rnd
{
	static const int RAND_N = 624;
	static const int RAND_M = 397;

	unsigned int val[ 2 * RAND_N ];
	unsigned int *offs;
public:

	// standard ctors and assignments
	Rnd() : offs( 0 ) {}
	const Rnd &operator = (const Rnd &b);
	Rnd( const Rnd &rnd );

	// init by seed
	Rnd( unsigned int seed ) : offs( 0 ) { Seed( seed ); }
	
	// set seed
	void Seed( unsigned int seed );

	// random unsigned int
	unsigned int Rand( );

	// double 0 ... 1, 0 included, 1 excluded
	double Drand();
	// float 0 ... 1, 0 included, 1 excluded
	float Frand();
	// double -1 ... 1, -1 , 1 excluded
	double Dsrand();
	// float -1 ... 1, -1 , 1 excluded
	float Fsrand( );
};




