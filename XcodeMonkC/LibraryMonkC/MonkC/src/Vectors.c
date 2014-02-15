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

#include "monkc.h"

/*
	Vector implements (floating point)
*/

static int current_vector = 0;
static int current_vector2 = 0;
static int current_vector3 = 0;
static int current_vector4 = 0;

static vector_struct vector_stack[VEC_STACK_SIZE];
static vector2_struct vector2_stack[VEC_STACK_SIZE];
static vector3_struct vector3_stack[VEC_STACK_SIZE];
static vector4_struct vector4_stack[VEC_STACK_SIZE];

void _init_vector_stack()
{
	vector_struct v1 = {0.0f};
	vector2_struct v2 = {0.0f, 0.0f};
	vector3_struct v3 = {0.0f, 0.0f, 0.0f};
	vector4_struct v4 = {0.0f, 0.0f, 0.0f, 0.0f};

	int i;
	for (i = 0; i < VEC_STACK_SIZE; i++)
	{
		vector_stack[i] = v1;
		vector2_stack[i] = v2;
		vector3_stack[i] = v3;
		vector4_stack[i] = v4;
	}
}

vector pushv(double x)
{
	if(current_vector >= VEC_STACK_SIZE)
		current_vector=0;

	vector_struct v1 = {x};

	vector_stack[current_vector]=v1;
	vector ret = &vector_stack[current_vector];
	current_vector++;
	return ret;
}

vector2 pushv2(double x, double y)
{
	if(current_vector2 >= VEC_STACK_SIZE)
		current_vector2=0;

	vector2_struct v2 = {x, y};

	vector2_stack[current_vector2]=v2;
	vector2 ret = &vector2_stack[current_vector2];
	current_vector2++;
	return ret;
}

vector3 pushv3(double x, double y, double z)
{
	if(current_vector3 >= VEC_STACK_SIZE)
		current_vector3=0;

	vector3_struct v3 = {x, y, z};

	vector3_stack[current_vector3]=v3;
	vector3 ret = &vector3_stack[current_vector3];
	current_vector3++;
	return ret;
}

vector4 pushv4(double x, double y, double z, double t)
{
	if(current_vector4 >= VEC_STACK_SIZE)
		current_vector4=0;

	vector4_struct v4 = {x, y, z, t};

	vector4_stack[current_vector4]=v4;
	vector4 ret = &vector4_stack[current_vector4];
	current_vector4++;
	return ret;
}

//wector is vector with long double raw data inside
static int current_wector = 0;
static int current_wector2 = 0;
static int current_wector3 = 0;
static int current_wector4 = 0;

static wector_struct wector_stack[VEC_STACK_SIZE];
static wector2_struct wector2_stack[VEC_STACK_SIZE];
static wector3_struct wector3_stack[VEC_STACK_SIZE];
static wector4_struct wector4_stack[VEC_STACK_SIZE];

void _init_wector_stack()
{
	wector_struct v1 = {0.0f};
	wector2_struct v2 = {0.0f, 0.0f};
	wector3_struct v3 = {0.0f, 0.0f, 0.0f};
	wector4_struct v4 = {0.0f, 0.0f, 0.0f, 0.0f};

	int i;
	for (i = 0; i < VEC_STACK_SIZE; i++)
	{
		wector_stack[i] = v1;
		wector2_stack[i] = v2;
		wector3_stack[i] = v3;
		wector4_stack[i] = v4;
	}
}

wector pushw(long double x)
{
	if(current_wector >= VEC_STACK_SIZE)
		current_wector=0;

	wector_struct v1 = {x};

	wector_stack[current_wector]=v1;
	wector ret = &wector_stack[current_wector];
	current_wector++;
	return ret;
}

wector2 pushw2(long double x, long double y)
{
	if(current_wector2 >= VEC_STACK_SIZE)
		current_wector2=0;

	wector2_struct v2 = {x, y};

	wector2_stack[current_wector2]=v2;
	wector2 ret = &wector2_stack[current_wector2];
	current_wector2++;
	return ret;
}

wector3 pushw3(long double x, long double y, long double z)
{
	if(current_wector3 >= VEC_STACK_SIZE)
		current_wector3=0;

	wector3_struct v3 = {x, y, z};

	wector3_stack[current_wector3]=v3;
	wector3 ret = &wector3_stack[current_wector3];
	current_wector3++;
	return ret;
}

wector4 pushw4(long double x, long double y, long double z, long double t)
{
	if(current_wector4 >= VEC_STACK_SIZE)
		current_wector4=0;

	wector4_struct v4 = {x, y, z, t};

	wector4_stack[current_wector4]=v4;
	wector4 ret = &wector4_stack[current_wector4];
	current_wector4++;
	return ret;
}
