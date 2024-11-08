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
#include "Vec3.h"
#include "Vec3f.h"
#include "Quaternion.h"


Vec3::Vec3(Vec3f vecf){
    x  = vecf.x;
    y  = vecf.y;
    z  = vecf.z;
}

void Vec3::serialize(){

}

void Vec3::Rotate(Vec3 const &R, double Angle){
	//rotate the vector around R with an angle Angle
    Quaternion qt;
    qt.set(Angle, R);
    qt.conj(x,y,z);
}

void Vec3::Rotate(Vec3 &O, Vec3 const &R, double Angle){

    Quaternion qt;
    qt.set(Angle, R);
    Vec3 OP;
	OP.x = x-O.x;
	OP.y = y-O.y;
	OP.z = z-O.z;
    qt.conj(OP);
	x = O.x + OP.x;
	y = O.y + OP.y;
	z = O.z + OP.z;
}

void Vec3::RotateN(Vec3 n, double NTilt){

    Vec3 r;
    n.Normalize();
    r=Vec3(x,y,z);
    r = n*(n.dot(r))+(n*r)*n*cos(NTilt/180*PI_)+(n*r)*sin(NTilt/180*PI_);
    x=r.x;
    y=r.y;
    z=r.z;
}

void Vec3::RotateX(Vec3 const &O, double XTilt){

    Vec3 OP;
	OP.x = x-O.x;
	OP.y = y-O.y;
	OP.z = z-O.z;
		
	XTilt *=PI_/180.0;
	y = O.y + OP.y * cos(XTilt) - OP.z * sin(XTilt);
	z = O.z + OP.y * sin(XTilt) + OP.z * cos(XTilt);
}

void Vec3::RotateY(Vec3 const &O, double YTilt){

    Vec3 OP;
	OP.x = x-O.x;
	OP.y = y-O.y;
	OP.z = z-O.z;
		
	YTilt *=PI_/180.0;

	x = O.x + OP.x * cos(YTilt) + OP.z * sin(YTilt);
	z = O.z - OP.x * sin(YTilt) + OP.z * cos(YTilt);
}

void Vec3::RotateZ(Vec3 const &O, double ZTilt){

    Vec3 OP;
	OP.x = x-O.x;
	OP.y = y-O.y;
	OP.z = z-O.z;
	
	ZTilt *=PI_/180.0;

    x = O.x + OP.x * cos(ZTilt) + OP.y * sin(ZTilt);
    y = O.y - OP.x * sin(ZTilt) + OP.y * cos(ZTilt);
}

void Vec3::RotZ(double ZTilt){

    Vec3 OP;
    OP.x = x;
    OP.y = y;

    x =  OP.x * cos(ZTilt) - OP.y * sin(ZTilt);
    y =  OP.x * sin(ZTilt) + OP.y * cos(ZTilt);
}

void Vec3::RotX(double XTilt){

    Vec3 OP;
    OP.y = y;
    OP.z = z;

    y = OP.y * cos(XTilt) - OP.z * sin(XTilt);
    z = OP.y * sin(XTilt) + OP.z * cos(XTilt);
}

void Vec3::RotY(double YTilt){

    Vec3 OP;
    OP.x = x;
    OP.z = z;

    x =  OP.x * cos(YTilt) + OP.z * sin(YTilt);
    z = -OP.x * sin(YTilt) + OP.z * cos(YTilt);
}

void  Vec3::RotateY(double YTilt){

	YTilt *=PI_/180.0;

	double xo = x;
	double zo = z;
	x =  xo * cos(YTilt) + zo * sin(YTilt);
	z = -xo * sin(YTilt) + zo * cos(YTilt);
}
