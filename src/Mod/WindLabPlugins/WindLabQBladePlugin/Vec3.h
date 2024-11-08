/**********************************************************************

    Copyright (C) 2016 David Marten <david.marten@qblade.org>

    This program is licensed under the Academic Public License
    (APL) v1.0; You can use, redistribute and/or modify it in
    non-commercial academic environments under the terms of the
    APL as published by the QBlade project; See the file 'LICENSE'
    for details; Commercial use requires a commercial license
    (contact info@qblade.org).

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

***********************************************************************/

#include <math.h>

#ifndef VEC3_H
#define VEC3_H

class Vec3f;

class Vec3
{
public: 
	double x;
	double y;
	double z;

    void serialize();

    Vec3(){
		x  = 0.0;
		y  = 0.0;
		z  = 0.0;
    }

    Vec3(double const &xi, double const &yi, double const &zi){
		x  = xi;
		y  = yi;
		z  = zi;
	}

    Vec3(Vec3f vecf);

	//inline operators
    bool operator ==(Vec3 const &V){
		//used only to compare point positions
		return (V.x-x)*(V.x-x) + (V.y-y)*(V.y-y) + (V.z-z)*(V.z-z)<0.000000001;
	}
	
    void operator =(Vec3 const &T){
		x = T.x;
		y = T.y;
		z = T.z;
	}
	
    void operator+=(Vec3 const &T){
		x += T.x;
		y += T.y;
		z += T.z;
	}
	
    void operator-=(Vec3 const &T){
		x -= T.x;
		y -= T.y;
		z -= T.z;
	}

    void operator*=(double const &d){
		x *= d;
		y *= d;
		z *= d;
	}
				   
    Vec3 operator *(double const &d){
        Vec3 T(x*d, y*d, z*d);
		return T;
	}
	
    Vec3 operator *(Vec3 const &T){
        Vec3 C;
		C.x =  y*T.z - z*T.y;
		C.y = -x*T.z + z*T.x;
		C.z =  x*T.y - y*T.x;
		return C;
	}
	
    Vec3 operator /(double const &d){
        Vec3 T(x/d, y/d, z/d);
		return T;
	}
	
    Vec3 operator +(Vec3 const &V){
        Vec3 T(x+V.x, y+V.y, z+V.z);
		return T;
	}
	
    Vec3 operator -(Vec3 const &V){
        Vec3 T(x-V.x, y-V.y, z-V.z);
		return T;
	}

    void Copy(Vec3 const &V){
		x = V.x;
		y = V.y;
		z = V.z;
	}
	
    void Set(double const &x0, double const &y0, double const &z0){
		x = x0;
		y = y0;
		z = z0;
	}
	
    void Set(Vec3 const &V){
		x = V.x;
		y = V.y;
		z = V.z;
	}

    void Normalize(){
		double abs = VAbs();
		if(abs< 1.e-10) return;
		x/=abs;
		y/=abs;
		z/=abs;
	}
		
    double VAbs(){
		return sqrt(x*x+y*y+z*z);
	}
	
    double dot(Vec3 const &V){
		return x*V.x + y*V.y + z*V.z;
	}
	
    bool IsSame(Vec3 const &V){
        return (V.x-x)*(V.x-x) + (V.y-y)*(V.y-y) + (V.z-z)*(V.z-z) < 1e-20;
	}

    void Translate(Vec3 const &T){
		x += T.x;
		y += T.y;
		z += T.z;
	}

    void Rotate(Vec3 const &R, double Angle);
    void Rotate(Vec3 &O, Vec3 const &R, double Angle);
    void RotateN(Vec3 n, double NTilt);
    void RotateX(Vec3 const &O, double XTilt);
    void RotateY(Vec3 const &O, double YTilt);
    void RotateZ(Vec3 const &O, double ZTilt);
    void RotateY(double YTilt);
    void RotX(double YTilt);
    void RotY(double YTilt);
    void RotZ(double ZTilt);


};

#endif //VEC3_H
