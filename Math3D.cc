#include "Math3D.h"
#include <stdlib.h>
#include <memory.h>

V3 V3::X(1,0,0),V3::Y(0,1,0),V3::Z(0,0,1),V3::I(1,1,1);
M3 M3::I( 1, 0, 0, 0, 1, 0, 0, 0, 1 );

M3::operator Q() const
{
	M3 q = (1.0/3.0) * *this;
	double k[ 16 ] =
		{
			q.a00-q.a11-q.a22, q.a10+q.a01, q.a20+q.a02, q.a21-q.a12,
			q.a10+q.a01, q.a11-q.a00-q.a22, q.a21+q.a12, q.a02-q.a20,
			q.a20+q.a02, q.a21+q.a12, q.a22-q.a00-q.a11, q.a10-q.a01,
			q.a21-q.a12, q.a02-q.a20, q.a10-q.a01, q.a00+q.a11+q.a22,
		},
		a[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 },
		p[16],s[4],d,m;
	int f;
	do
	{
		memcpy(p,a,16*sizeof(double));
		f = -1; m = 0;
		for( int i = 0 ; i < 4 ; i++ )
		{
			for( int j = 0 ; j < 4 ; j++ )
			{
				a[4*i+j] = p[4*i+0]*k[4*0+j] + p[4*i+1]*k[4*1+j] + p[4*i+2]*k[4*2+j] + p[4*i+3]*k[4*3+j]; 
			}
			s[i]= sqrt( a[4*i+0]*a[4*i+0] + a[4*i+1]*a[4*i+1] + a[4*i+2]*a[4*i+2] + a[4*i+3]*a[4*i+3] );
			double l= 1.0 / s[i]; a[4*i+0]*=l; a[4*i+1]*=l; a[4*i+2]*=l; a[4*i+3]*=l;
			if( f == -1 || s[i] > m ) { m=s[f=i]; }
		}
		d = 1 - p[4*f+0]*a[4*f+0] - p[4*f+1]*a[4*f+1] - p[4*f+2]*a[4*f+2] - p[4*f+3]*a[4*f+3];
	}
	while( d > 1e-14 );
	return Q( a[4*f+0], a[4*f+1], a[4*f+2], a[4*f+3] );
}

Q Slerp( const Q &a, const Q &b, double t )
{
	double c=a.w*b.w+a.v*b.v;
	Q sa( c >= 0 ? a.v : -a.v, c >= 0 ? a.w : -a.w );
	c = c >= 0 ? c : -c;
	if(c>=1.0){return b;}
	double s=sqrt(1.0-c*c),i=1-t;
	if(s>1e-8){double p = acos(c),j=1.0/s;i=sin(i*p)*j;t=sin(t*p)*j;}
	return Q(sa.v*i+b.v*t,sa.w*i+b.w*t);
}

void Orthogonalize3D( V3 v[ 3 ] )
{
	v[0]=v[0].Norm();
	v[1]-=v[0]*Dot(v[0],v[1]);
	v[1]=v[1].Norm();
	v[2]-=v[0]*Dot(v[0],v[2]);
	v[2]-=v[1]*Dot(v[1],v[2]);
	v[2]=v[2].Norm();
}

struct EVector
{
	V3 p,q;
	double e,d;
	EVector( double _x, double _y, double _z ) : q(_x,_y,_z), e(0), d(1) {}
	void Multiply(const M3&a){p=q;q=a*q;}
	void Orthogonalize(const EVector&a) { q -= a.q*Dot(a.q, q); }
	void Normalize(){e=q.Sz();q/=e>1e-66?e:1e-66;d=1-Dot(p,q);}
	bool Change(){return d>1e-12;}
};

inline bool SwapBigger(EVector&a,EVector&b){
	if(a.e<b.e){EVector q=b;b=a;a=q;return true;}
	return false;
}

M3 EignenMatrix( const M3 &a, V3 *s )
{

	EVector u(1,0,0),v(0,1,0),w(0,0,1);
	for(int i = 0; (u.Change( ) || v.Change( ) || w.Change( )) && i < 4096; i++)
	{
		u.Multiply( a ); u.Normalize( );
		v.Multiply( a ); v.Orthogonalize( u ); v.Normalize( ); SwapBigger( u, v );
		w.Multiply( a ); w.Orthogonalize( u ); w.Orthogonalize( v ); w.Normalize( ); if(SwapBigger( v, w )) { SwapBigger( u, v ); }
	}
	if( u.e < 1e-34 )
	{
		u.e = v.e= w.e = 0;
		u.q = V3(1,0,0); v.q = V3(0,1,0); w.q = V3(0,0,1);
	}
	else if( v.e < 1e-34 )
	{
		v.e= w.e = 0;
		double vqx=fabs( u.q.x ), vqy=fabs( u.q.y ), vqz=fabs( u.q.z );
		if( vqx > vqy && vqz > vqy )
		{
			v.q = V3( 0, u.q.y > 0 ? -1.0 : 1.0, 0 );
		}
		else if( vqx > vqz )
		{
			v.q = V3( 0, 0, u.q.z > 0 ? -1.0 : 1.0 );
		}
		else
		{
			v.q = V3( u.q.x > 0 ? -1.0 : 1.0, 0, 0 );
		}
		v.Orthogonalize( u ); v.Normalize( );
		w.q=Cross(u.q,v.q); w.Normalize();
	}
	else if( w.e < 1e-34 )
	{
		w.e = 0;
		w.q=Cross(u.q,v.q); w.Normalize();
	}
	if( s ) { s->x=u.e; s->y=v.e; s->z=w.e; }
	return M3( u.q.x,u.q.y,u.q.z, v.q.x,v.q.y,v.q.z, w.q.x,w.q.y,w.q.z );
}

M3 Realign( const M3&s, const M3&t )
{
	M3 d=t*~s,o;

	double *f=&d.a00,*g=&o.a00; int x=0;
	if( fabs(d.a10) > fabs(*f) ) { f=&d.a10;g=&o.a01; x = 1; }
	if( fabs(d.a20) > fabs(*f) ) { f=&d.a20;g=&o.a02; x = 2; }
	*g = *f >= 0 ? 1.0 : -1.0;

	f=&d.a01;g=&o.a10; int y=0;
	if( x != 1 && ( !x || fabs(d.a11) > fabs(*f) ) ) { f=&d.a11;g=&o.a11; y = 1; }
	if( x != 2 && fabs(d.a21) > fabs(*f) ) { f=&d.a21;g=&o.a12; y = 2; }
	*g = *f >= 0 ? 1.0 : -1.0;

	switch(3-x-y)
	{
		case 0: o.a20 = d.a02 >= 0 ? 1.0 : -1.0; break;
		case 1: o.a21 = d.a12 >= 0 ? 1.0 : -1.0; break;
		case 2: o.a22 = d.a22 >= 0 ? 1.0 : -1.0; break;
	}

	return o * t;
}

