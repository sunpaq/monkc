/*
Copyright (c) <2013>, <Sun Yuli>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <Monk-C> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef VEC_STACK_SIZE
#define VEC_STACK_SIZE 100
#endif

//the types can not be used in Monk-C method arguments:
//char/signed char/unsigned char(use int)
//short/signed short/unsigned short(use int)
//short int/signed short int/unsigned short int(use int)
//float(use double)

//vectors
typedef struct{
	double x;
}vector_struct;
typedef vector_struct* vector;

typedef struct{
	double x;
	double y;
}vector2_struct;
typedef vector2_struct* vector2;

typedef struct{
	double x;
	double y;
	double z;
}vector3_struct;
typedef vector3_struct* vector3;

typedef struct{
	double x;
	double y;
	double z;
	double t;
}vector4_struct;
typedef vector4_struct* vector4;

vector pushv(double x);
vector2 pushv2(double x, double y);
vector3 pushv3(double x, double y, double z);
vector4 pushv4(double x, double y, double z, double t);

#define popvx(vec) vec->x
#define popvy(vec) vec->y
#define popvz(vec) vec->z
#define popvt(vec) vec->t

//wectors: vectors with long double raw datas
typedef struct{
	long double x;
}wector_struct;
typedef wector_struct* wector;

typedef struct{
	long double x;
	long double y;
}wector2_struct;
typedef wector2_struct* wector2;

typedef struct{
	long double x;
	long double y;
	long double z;
}wector3_struct;
typedef wector3_struct* wector3;

typedef struct{
	long double x;
	long double y;
	long double z;
	long double t;
}wector4_struct;
typedef wector4_struct* wector4;

wector pushw(long double x);
wector2 pushw2(long double x, long double y);
wector3 pushw3(long double x, long double y, long double z);
wector4 pushw4(long double x, long double y, long double z, long double t);

#define popwx(vec) vec->x
#define popwy(vec) vec->y
#define popwz(vec) vec->z
#define popwt(vec) vec->t

