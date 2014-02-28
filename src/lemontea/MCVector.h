/*
 Vectors.h
 */
#ifndef VEC_STACK_SIZE
#define VEC_STACK_SIZE 100
#endif



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

extern void _init_vector_stack();
extern void _init_wector_stack();
