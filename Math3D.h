#pragma once
#include <math.h>
#include <stdio.h>

#define PI (3.1415926535897932384626433832795)
#define Rad2Deg(x) ((x)*180.0/PI)
#define Deg2Rad(x) ((x)*PI/180.0)
#define EPSILON (1e-34)
#define EPSILON2 (EPSILON*EPSILON)

// 3D vector
struct V3
{
	// we allow two ways of accessing it
	// v.x, v.y, v.z works,
	// but also v.a[0], v.a[1], v.a[2] works 
	union 
	{
		struct{double x,y,z;};
		double a[3];
	};

	// default is a null vector
	V3():x(0),y(0),z(0){}
	
	// standard constructors
	V3(const V3&v):x(v.x),y(v.y),z(v.z){}
	V3(double _x,double _y, double _z):x(_x),y(_y),z(_z){}
	
	// vector norm^2
	double Sz2()const{return x*x+y*y+z*z;}
	
	//vector norm
	double Sz()const{return sqrt(Sz2());}
	
	// returns the vector normalized 
	V3 Norm()const;
	V3 Normalized()const{return Norm();}
	
	// normalizes the vector itself
	void Snm(){*this/=Sz();}
	void SelfNormalize(){Snm();}
	
	// set vector values to this vector
	const V3&operator=(const V3&v){x=v.x;y=v.y;z=v.z;return*this;}
	
	// add vector to this vector
	const V3&operator+=(const V3&v){x+=v.x;y+=v.y;z+=v.z;return*this;}

	// subtract vector from this vector
	const V3&operator-=(const V3&v){x-=v.x;y-=v.y;z-=v.z;return*this;}
	
	// multiplies this vector by a scalar
	const V3&operator*=(double f){x*=f;y*=f;z*=f;return*this;}

	// divides this vector by a scalar
	const V3&operator/=(double f){f=1/f;x*=f;y*=f;z*=f;return*this;}
	
	// returns the opposite vector 
	V3 operator-()const{return V3(-x,-y,-z);}
	
	// returns the vector itself ( just for completeness ) 
	V3 operator+()const{return*this;}
	
	// reciprocal vector - returns v / (Norm(v)^2) so that DotProduct (v, ~v) = 1 
	V3 operator~()const;
	V3 Reciprocal()const{return ~(*this);}
	
	// vector distance to another vector ^2
	double Dist2(const V3&v)const;
	double Distance2(const V3&v) const;

	// vector distance to another vector 
	double Dist(const V3&v) const;
	double Distance(const V3&v) const;

	// epsilon based comparison - should be used normally instead of == or !=
	inline bool Equal(const V3&v) const{ return Dist2(v)<= EPSILON2;}
	inline bool Equal(const V3&v, double epsilon) const{ return Dist2(v)<= epsilon*epsilon;}
	inline bool NotEqual(const V3&v) const{ return Dist2(v) > EPSILON2;}
	inline bool NotEqual(const V3&v, double epsilon) const{ return Dist2(v) > epsilon*epsilon;}

	//special vectors
	// X,Y,Z are the axes, I is 1,1,1
	static V3 X,Y,Z,I;
};

// vector addition
inline V3 operator+(const V3&a,const V3&b){return V3(a.x+b.x,a.y+b.y,a.z+b.z);}

// vector subtraction
inline V3 operator-(const V3&a,const V3&b){return V3(a.x-b.x,a.y-b.y,a.z-b.z);}

// vector scalar multiplication
inline V3 operator*(const V3&v,double f){return V3(v.x*f,v.y*f,v.z*f);}
inline V3 operator*(double f,const V3&v){return V3(v.x*f,v.y*f,v.z*f);}

// vector scalar division
inline V3 operator/(const V3&v,double f){f=1/f;return V3(v.x*f,v.y*f,v.z*f);}

// vector comparison
// !!! CAUTION !!! uses direct floating point comparison
// you most probably want epsilon tolerant versions - Equal or NotEqual 
inline bool operator==(const V3&a,const V3&b){return a.x==b.x&&a.y==b.y&&a.z==b.z;}
inline bool operator!=(const V3&a,const V3&b){return a.x!=b.x||a.y!=b.y||a.z!=b.z;}

// returns normalized vector, the same as above, just another syntax
inline V3 Norm(const V3&v){return v.Norm();}

// vector dot product
inline double Dot(const V3&a,const V3&b){return a.x*b.x+a.y*b.y+a.z*b.z;}
inline double DotProduct(const V3&a,const V3&b){return Dot(a,b);}
inline double operator*(const V3&a,const V3&b){return Dot(a,b);}

// vector cross product
inline V3 Cross(const V3&a,const V3&b){return V3(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);}
inline V3 CrossProduct(const V3&a,const V3&b){return Cross(a,b);}

// vector distance ^2 Norm(a-b) ^2 , the same as above, just another syntax
inline double Dist2(const V3&a,const V3&b) { return (a-b).Sz2(); } 
inline double Distance2(const V3&a,const V3&b) { return Dist2(a,b); } 

// vector distance Norm(a-b) , the same as above, just another syntax
inline double Dist(const V3&a,const V3&b) { return (a-b).Sz(); } 
inline double Distance(const V3&a,const V3&b) { return Dist(a,b); }

// epsilon based comparison - should be used normally instead of == or != , the same as above, just another syntax
inline bool Equal(const V3&a,const V3&b) { return Dist2(a,b) <= EPSILON2;}
inline bool Equal(const V3&a,const V3&b,double epsilon) { return Dist2(a,b) <= epsilon*epsilon;}
inline bool NotEqual(const V3&a,const V3&b) { return Dist2(a,b) > EPSILON2;}
inline bool NotEqual(const V3&a,const V3&b,double epsilon) { return Dist2(a,b) > epsilon*epsilon;}

//orthogonalizes a triplet of vectors
void Orthogonalize3D( V3 v[ 3 ] );

inline double Angle( const V3 &a, const V3 &b ) { return acos( Dot( a, b ) / (a.Sz() * b.Sz()) ); }

// implementations from above
inline V3 V3::Norm()const{return *this/Sz();}
inline V3 V3::operator~()const{return*this/Sz2();}
inline double V3::Dist2(const V3&v)const { return (*this - v).Sz2(); }
inline double V3::Distance2(const V3&v) const{ return Dist2(v); }
inline double V3::Dist(const V3&v) const { return (*this - v).Sz(); }
inline double V3::Distance(const V3&v) const { return Dist(v); }



struct Q;

// 3D matrix
struct M3
{
	// we allow several ways of accessing it, use which ever you find the most comfortable
	//
	// / aXX,aXY,aXZ \      / a00,a01,a02 \      / m[0][0],m[0][1],m[0][2] \      / f[0],f[1],f[2] \
	//|  aYX,aYY,aYZ  | OR |  a10,a11,a12  | OR |  m[1][0],m[1][1],m[1][2]  | OR |  f[3],f[4],f[5]  |
	// \ aZX,aZY,aZZ /      \ a20,a21,a22 /      \ m[2][0],m[2][1],m[2][2] /      \ f[6],f[7],f[8] /
	//

	union
	{
		struct{double aXX,aXY,aXZ,aYX,aYY,aYZ,aZX,aZY,aZZ;};
		struct{double a00,a01,a02,a10,a11,a12,a20,a21,a22;};
		double m[3][3];
		double f[9];
	};
	
	// default is a null matrix
	M3():a00(0),a01(0),a02(0),a10(0),a11(0),a12(0),a20(0),a21(0),a22(0){}
	
	// standard constructors
	M3(double _a00,double _a01,double _a02,double _a10,double _a11,double _a12,double _a20,double _a21,double _a22):
		a00(_a00),a01(_a01),a02(_a02),a10(_a10),a11(_a11),a12(_a12),a20(_a20),a21(_a21),a22(_a22) {}
	M3(const M3&v):
		a00(v.a00),a01(v.a01),a02(v.a02),a10(v.a10),a11(v.a11),a12(v.a12),a20(v.a20),a21(v.a21),a22(v.a22){}
	
	
	// set matrix values to this matrix
	const M3&operator=(const M3&v)
	{
		a00=v.a00;a01=v.a01;a02=v.a02;a10=v.a10;a11=v.a11;a12=v.a12;a20=v.a20;a21=v.a21;a22=v.a22;
		return *this;
	}

	// add matrix from this matrix
	const M3&operator+=(const M3&v)
	{
		a00+=v.a00;a01+=v.a01;a02+=v.a02;a10+=v.a10;a11+=v.a11;a12+=v.a12;a20+=v.a20;a21+=v.a21;a22+=v.a22;
		return*this;
	}

	// subtract matrix from this matrix
	const M3&operator-=(const M3&v)
	{
		a00-=v.a00;a01-=v.a01;a02-=v.a02;a10-=v.a10;a11-=v.a11;a12-=v.a12;a20-=v.a20;a21-=v.a21;a22-=v.a22;
		return*this;
	}
	
	// multiply this matrix by matrix
	inline const M3&operator*=(const M3&m);
	
	// divide this matrix by matrix, in effect computing M*(N^-1)
	inline const M3&operator/=(const M3&m);
	
	// multiply this matrix by scalar
	const M3&operator*=(double a){a00*=a;a01*=a;a02*=a;a10*=a;a11*=a;a12*=a;a20*=a;a21*=a;a22*=a;return*this;}
	
	// divide this matrix by scalar
	const M3&operator/=(double a){a=1/a;a00*=a;a01*=a;a02*=a;a10*=a;a11*=a;a12*=a;a20*=a;a21*=a;a22*=a;return*this;}
	
	// returns negative matrix 
	M3 operator-()const{return M3(-a00,-a01,-a02,-a10,-a11,-a12,-a20,-a21,-a22);}
	
	// returns the vector itself ( just for completeness ) 
	M3 operator+()const{return*this;}
	
	// returns matrix norm ^2
	double Norm2()const{return a00*a00+a01*a01+a02*a02+a10*a10+a11*a11+a12*a12+a20*a20+a21*a21+a22*a22;}
	
	// returns matrix norm
	double Norm()const{return sqrt(a00*a00+a01*a01+a02*a02+a10*a10+a11*a11+a12*a12+a20*a20+a21*a21+a22*a22);}
	
	// returns matrix determinant
	double D()const{return a00*a11*a22+a01*a12*a20+a02*a10*a21-a02*a11*a20-a01*a10*a22-a00*a12*a21;}
	
	//returns inverse matrix
	inline M3 operator!()const
	{
		double I=1/D();
		return M3(I*(a11*a22-a12*a21),I*(a02*a21-a01*a22),I*(a01*a12-a02*a11),
				  I*(a12*a20-a10*a22),I*(a00*a22-a02*a20),I*(a02*a10-a00*a12),
				  I*(a10*a21-a11*a20),I*(a01*a20-a00*a21),I*(a00*a11-a01*a10));
	}
	inline M3 Inv()const {return !(*this);}
	inline M3 Inverse()const {return !(*this);}
	
	//returns transposed matrix
	inline M3 operator~()const {return M3(a00,a10,a20,a01,a11,a21,a02,a12,a22);}
	inline M3 Trans()const {return ~(*this);}
	inline M3 Transpose()const {return ~(*this);}

	// numerically stable rotation matrix to quaternion conversion
	operator Q() const;
	
	// epsilon based comparison - should be used normally instead of == or !=
	bool Equal(const M3&m) const;
	bool Equal(const M3&m, double epsilon) const;
	bool NotEqual(const M3&m) const;
	bool NotEqual(const M3&m, double epsilon) const;

	// unit matrix
	static M3 I;
};

// matrix scalar multiplication
inline M3 operator*(double a,const M3&m)
{
	return M3(m.a00*a,m.a01*a,m.a02*a,m.a10*a,m.a11*a,m.a12*a,m.a20*a,m.a21*a,m.a22*a);
}
inline M3 operator*(const M3&m,double a)
{
	return M3(m.a00*a,m.a01*a,m.a02*a,m.a10*a,m.a11*a,m.a12*a,m.a20*a,m.a21*a,m.a22*a);
}

// matrix scalar multiplication
inline M3 operator/(const M3&m,double a) { return m*(1.0/a); }

// left side vector multiplication V * M
inline V3 operator*(const V3&a,const M3&m)
{
	return V3(a.x*m.a00+a.y*m.a10+a.z*m.a20,a.x*m.a01+a.y*m.a11+a.z*m.a21,a.x*m.a02+a.y*m.a12+a.z*m.a22);
}

// right side vector multiplication  M * V
inline V3 operator*(const M3&m,const V3&a)
{
	return V3(a.x*m.a00+a.y*m.a01+a.z*m.a02,a.x*m.a10+a.y*m.a11+a.z*m.a12,a.x*m.a20+a.y*m.a21+a.z*m.a22);
}

// matrix multiplication
inline M3 operator*(const M3&a,const M3&b)
{
	return M3(a.a00*b.a00+a.a01*b.a10+a.a02*b.a20,
			  a.a00*b.a01+a.a01*b.a11+a.a02*b.a21,
			  a.a00*b.a02+a.a01*b.a12+a.a02*b.a22,
			  a.a10*b.a00+a.a11*b.a10+a.a12*b.a20,
			  a.a10*b.a01+a.a11*b.a11+a.a12*b.a21,
			  a.a10*b.a02+a.a11*b.a12+a.a12*b.a22,
			  a.a20*b.a00+a.a21*b.a10+a.a22*b.a20,
			  a.a20*b.a01+a.a21*b.a11+a.a22*b.a21,
			  a.a20*b.a02+a.a21*b.a12+a.a22*b.a22);
}

// matrix division, in effect computing A*(B^-1)
inline M3 operator/(const M3&a,const M3&b) { return a*!b;}

// matrix addition
inline M3 operator+(const M3&a,const M3&b)
{
	return M3(a.a00+b.a00, a.a01+b.a01, a.a02+b.a02,
			  a.a10+b.a10, a.a11+b.a11, a.a12+b.a12,
			  a.a20+b.a20, a.a21+b.a21, a.a22+b.a22);
}

// matrix subtraction
inline M3 operator-(const M3&a,const M3&b)
{
	return M3(a.a00-b.a00, a.a01-b.a01, a.a02-b.a02,
			  a.a10-b.a10, a.a11-b.a11, a.a12-b.a12,
			  a.a20-b.a20, a.a21-b.a21, a.a22-b.a22);
}

// matrix comparison
// !!! CAUTION !!! uses direct floating point comparison
// you most probably want epsilon tolerant versions - Equal or NotEqual 
inline bool operator==(const M3&a,const M3&b)
{
	return a.a00==b.a00&&a.a01==b.a01&&a.a02==b.a02&&
		   a.a10==b.a10&&a.a11==b.a11&&a.a12==b.a12&&
		   a.a20==b.a20&&a.a21==b.a21&&a.a22==b.a22;
}
inline bool operator!=(const M3&a,const M3&b)
{
	return a.a00!=b.a00||a.a01!=b.a01||a.a02!=b.a02||
		   a.a10!=b.a10||a.a11!=b.a11||a.a12!=b.a12||
		   a.a20!=b.a20||a.a21!=b.a21||a.a22!=b.a22;
}

// epsilon based comparison - should be used normally instead of == or != , the same as above, just another syntax
inline bool Equal(const M3&a,const M3&b) { return (a-b).Norm2() <= EPSILON2;}
inline bool Equal(const M3&a,const M3&b,double epsilon) { return (a-b).Norm2() <= epsilon*epsilon;}
inline bool NotEqual(const M3&a,const M3&b) { return (a-b).Norm2() > EPSILON2;}
inline bool NotEqual(const M3&a,const M3&b,double epsilon) { return (a-b).Norm2() > epsilon*epsilon;}

// implementation of the above
inline const M3&M3::operator*=(const M3&m){*this=*this*m;return*this;}
inline const M3&M3::operator/=(const M3&m){*this=*this/m;return*this;}
inline bool M3::Equal(const M3&m) const{ return (*this - m).Norm2() <= EPSILON2; }
inline bool M3::Equal(const M3&m, double epsilon) const{ return (*this - m).Norm2() <= epsilon*epsilon; }
inline bool M3::NotEqual(const M3&m) const{ return (*this - m).Norm2() > EPSILON2; }
inline bool M3::NotEqual(const M3&m, double epsilon) const{ return (*this - m).Norm2() > epsilon*epsilon; }


// returns the matrix of M3's eignenvectors, and optionally gives the eingnenvalues 
M3 EignenMatrix( const M3 &a, V3 *s = 0 );

// swaps rotation matrix t axes so that it represents the shortest arc rotation to s
M3 Realign( const M3&s, const M3&t );

// quaternion
struct Q
{
	V3 v; double w;
	
	// default is an unit quaternion
	Q() : w( 1 ) {}
	
	//standard constructors
	Q( double _x, double _y, double _z, double _w ) : v(_x, _y, _z), w(_w) { Normalize(); }
	Q( const V3 &_v, double _w ) : v(_v), w(_w) { Normalize(); }
	Q( const Q &q ) : v(q.v), w( q.w ) {}
	
	// set quaternion values to this quaternion
	const Q&operator=(const Q&q){ v = q.v; w = q.w; return *this;}
	
	// multiply this quaternion by quaternion
	const Q&operator*=(const Q&q);

	// returns the opposite quaternion 
	Q operator-() const { return Q(-v,w); }
	
	// renormalizes a denormalized quaternion
	void Normalize() { double f = 1.0 / sqrt( v.Sz2() + w * w ); v *= f; w *= f; }
	
	// "raw" distance^2 that does not take the quaternion degeneracy into account
	// and can be thus higher than one if one of the quaternions is in the minus world phantom zone
	// while the other is not
	double Rdst2(const Q&q)const;

	// distance^2 that does take degeneracy into account
	double Dist2(const Q&q)const;

	// distance that does take degeneracy into account
	double Dist(const Q&q)const;

	// epsilon based comparison - should be used normally instead of == or !=
	inline bool Equal(const Q&q) const{ return Dist2(q) <= EPSILON2;}
	inline bool Equal(const Q&q, double epsilon) const{ return Dist2(q) <= epsilon*epsilon;}
	inline bool NotEqual(const Q&q) const{ return Dist2(q) > EPSILON2;}
	inline bool NotEqual(const Q&q, double epsilon) const{ return Dist2(q) > epsilon*epsilon;}

	// converts to rotation matrix
	operator M3() const
	{ 
		return M3(
			1-2*(v.y*v.y+v.z*v.z),   2*(v.x*v.y-  w*v.z),   2*(v.x*v.z+  w*v.y),
			  2*(v.x*v.y+  w*v.z), 1-2*(v.x*v.x+v.z*v.z),   2*(v.y*v.z-  w*v.x),
			  2*(v.x*v.z-  w*v.y),   2*(v.y*v.z+  w*v.x), 1-2*(v.x*v.x+v.y*v.y) );
	}
};

// quaternion initialized by angle instead of the w parameter
struct QAngle:public Q
{
	//same Q constructors, just using angle to initialize the quaternion instead of the w component directly
	QAngle(const V3&_v,double _a) : Q(_v.Norm()*sin(_a*0.5),cos(_a*0.5)){}
	QAngle( double _x, double _y,double _z,double _a) : Q(V3(_x,_y,_z).Norm()*sin(_a*0.5),cos(_a*0.5)){}
};

// quaternion dot product
inline double Dot(const Q&a, const Q&b) { return a.v*b.v+a.w*b.w; }
inline double DotProduct(const Q&a, const Q&b) { return Dot(a,b); }

// "raw" distance^2 that does not take the quaternion degeneracy into account
// and can be thus higher than one if one of the quaternions is in the minus world phantom zone
// while the other is not
inline double Rdst2(const Q&a, const Q&b) { return 2 *( 1 - Dot(a,b) ); }

// distance^2 that does take degeneracy into account
inline double Dist2(const Q&a, const Q&b) { return 2 *( 1 - fabs( Dot(a,b) ) ); }

// distance that does take degeneracy into account
inline double Dist(const Q&a, const Q&b) { double f = Dist2(a,b) ; return f > 0 ? sqrt(f) : 0; }

// quaternion comparison
// !!! CAUTION !!! uses direct floating point comparison
// you most probably want epsilon tolerant versions - Equal or NotEqual 
inline bool operator==(const Q&a,const Q&b){ return a.v==b.v&&a.w==b.w; }
inline bool operator!=(const Q&a,const Q&b){ return a.v!=b.v||a.w!=b.w; }
inline Q operator *(const Q&a,const Q&b) { return Q( Cross(a.v,b.v)+a.w*b.v+b.w*a.v,a.w*b.w-a.v*b.v); }

// epsilon based comparison - should be used normally instead of == or != , the same as above, just another syntax
inline bool Equal(const Q&a,const Q&b) { return Dist2(a,b) <= EPSILON2;}
inline bool Equal(const Q&a,const Q&b,double epsilon) { return Dist2(a,b) <= epsilon*epsilon;}
inline bool NotEqual(const Q&a,const Q&b) { return Dist2(a,b) > EPSILON2;}
inline bool NotEqual(const Q&a,const Q&b,double epsilon) { return Dist2(a,b) > epsilon*epsilon;}

// spherical interpolation between a and b, t = 0 is a t = 1 is b
Q Slerp( const Q &a, const Q &b, double t );

// implementation of the above
inline double Q::Rdst2( const Q&q )const { return  2 * (1 - Dot(*this,q)); }
inline double Q::Dist2( const Q&q )const { return 2 * (1 - fabs( Dot(*this,q) )); }
inline double Q::Dist( const Q&q )const { double f = Dist2(q); return f > 0 ? sqrt( f ) : 0; }
inline const Q&Q::operator*=(const Q&v){*this=*this*v;Normalize();return*this;}


