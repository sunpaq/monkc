#include "MCContext.h"
#include <math.h>
#include <float.h>

#ifndef MCMath_ 
#define MCMath_

#ifndef MAX
#define MAX(A, B) ((A>B)?A:B)
#endif
#ifndef MIN
#define MIN(A, B) ((A<B)?A:B)
#endif

MCInline double MClognX(double n, double X) {
    //change of base formula
    return (log10(X) / log10(n));
}

MCInline MCBool MCSamefloat(float A, float B) {
    if (fabsf(A-B) < FLT_EPSILON) {
        return true;
    }
    return false;
}

MCInline MCBool MCSamedouble(double A, double B) {
    if (fabs(A-B) < DBL_EPSILON) {
        return true;
    }
    return false;
}

MCInline MCBool MCSamelongdouble(long double A, long double B) {
    if (fabsl(A-B) < LDBL_EPSILON) {
        return true;
    }
    return false;
}

typedef union {
    struct {
        float x;
        float y;
    };
    float v[2];
} MCVector2;

typedef union {
    struct {
        int x;
        int y;
    };
    int v[2];
} MCVector2i;

typedef union {
    struct {
        float x;
        float y;
        float z;
    };
    float v[3];
} MCVector3;

typedef union {
    struct {
        float x;
        float y;
        float z;
        float w;
    };
    float v[4];
} MCVector4, MCQuaternion;



MCInline MCBool MCVector3PositiveNonZero(MCVector3 vec3)
{
    return (vec3.x > 0 || vec3.y > 0 || vec3.z > 0);
}

MCInline MCVector2 MCVector2From3(MCVector3 vec3)
{
    return (MCVector2){vec3.x, vec3.y};
}

MCInline MCVector3 MCVector3From4(MCVector4 vec4)
{
    return (MCVector3){vec4.x, vec4.y, vec4.z};
}

MCInline MCBool MCVector2Equal(MCVector2 v1, MCVector2 v2)
{
    if (MCSamefloat(v1.x, v2.x) && MCSamefloat(v1.y, v2.y)) {
        return true;
    }
    return false;
}

MCInline MCBool MCVector3Equal(MCVector3 v1, MCVector3 v2)
{
    if (MCSamefloat(v1.x, v2.x) && MCSamefloat(v1.y, v2.y) && MCSamefloat(v1.z, v2.z)) {
        return true;
    }
    return false;
}

MCInline MCBool MCVector4Equal(MCVector4 v1, MCVector4 v2)
{
    if (MCSamefloat(v1.x, v2.x) && MCSamefloat(v1.y, v2.y) && MCSamefloat(v1.z, v2.z) && MCSamefloat(v1.w, v2.w)) {
        return true;
    }
    return false;
}



MCInline MCQuaternion MCQuaternionFromVec3(MCVector3 v)
{
    return (MCQuaternion){v.x, v.y, v.z, 0.0f};
}

MCInline MCQuaternion MCQuaternionZero()
{
    return (MCQuaternion){0,0,0,0};
}

//OpenGL use column major storage matrix m21 is 2column 1row
typedef union {
    struct
    {
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
    };
    float m[9];
} __attribute__((aligned(16))) MCMatrix3;

typedef union {
    struct
    {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    };
    float m[16];
} __attribute__((aligned(16))) MCMatrix4;

static const MCMatrix3 MCMatrix3Identity = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};

static const MCMatrix4 MCMatrix4Identity = {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
};

MCInline double MCDegreesToRadians(double degrees) { return degrees * (M_PI / 180); }
MCInline double MCRadiansToDegrees(double radians) { return radians * (180 / M_PI); }
MCInline double MCCircleFacingAngle(double degrees) {
    if (degrees < 180.0)
        return degrees+180.0;
    if (degrees > 180.0)
        return degrees-180.0;
    //degrees == 180.0
    return 0.0;
}

MCInline double MCSinDegrees(double degress)       { return sin(MCDegreesToRadians(degress)); }
MCInline double MCCosDegrees(double degress)       { return cos(MCDegreesToRadians(degress)); }
MCInline double MCTanDegrees(double degress)       { return tan(MCDegreesToRadians(degress)); }

MCInline float MCVector3Length(MCVector3 vector)
{
    return sqrtf(fabs(vector.v[0] * vector.v[0] + vector.v[1] * vector.v[1] + vector.v[2] * vector.v[2]));
}

MCInline MCVector3 MCVector3Normalize(MCVector3 vector)
{
    float l = MCVector3Length(vector);
    float x = vector.v[0] / l;
    float y = vector.v[1] / l;
    float z = vector.v[2] / l;
    
    if (x!=x || y!=y || z!= z) {
        return vector;
    }

    return (MCVector3){x,y,z};
}

MCInline MCVector3 MCVector3Make(float x, float y, float z) {
    return (MCVector3){x, y, z};
}

MCInline MCVector4 MCVector4Make(float x, float y, float z, float w) {
    return (MCVector4){x, y, z, w};
}

MCInline MCVector3 MCVector3MakeReverse(float x, float y, float z) {
    return (MCVector3){-x, -y, -z};
}

MCInline MCVector3 MCVector3Reverse(MCVector3 vtx) {
    return (MCVector3){-vtx.x, -vtx.y, -vtx.z};
}

MCInline MCVector3 MCVector3Middle(MCVector3 v1, MCVector3 v2) {
    return (MCVector3){(v1.x+v2.x)/2.0f, (v1.y+v2.y)/2.0f, (v1.z+v2.z)/2.0f};
}

MCInline MCVector3 MCVector3Add(MCVector3 v1, MCVector3 v2) {
    return (MCVector3){v1.x+v2.x, v1.y+v2.y, v1.z+v2.z};
}

MCInline MCVector3 MCVector3Sub(MCVector3 v1, MCVector3 v2) {
    //the same as add -v2
    return (MCVector3){v1.x-v2.x, v1.y-v2.y, v1.z-v2.z};
}

MCInline double MCVector3Dot(MCVector3 v1, MCVector3 v2) {
    return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

MCInline MCVector3 MCVector3Cross(MCVector3 v1, MCVector3 v2) {
    return (MCVector3){v1.y*v2.z - v2.y*v1.z,
        v2.x*v1.z - v1.x*v2.z,
        v1.x*v2.y - v2.x*v1.y};
}

MCInline MCQuaternion MCQuaternionGProduct(MCQuaternion p, MCQuaternion q)
{
    float pscalar = p.w;
    float qscalar = q.w;
    
    MCVector3 pvector = (MCVector3){p.x, p.y, p.z};
    MCVector3 qvector = (MCVector3){q.x, q.y, q.z};
    MCVector3 pxq = MCVector3Cross(pvector, qvector);
    
    return (MCQuaternion) {
        pscalar * qvector.x + qscalar * pvector.x + pxq.x,
        pscalar * qvector.y + qscalar * pvector.y + pxq.y,
        pscalar * qvector.z + qscalar * pvector.z + pxq.z,
        pscalar * qscalar - MCVector3Dot(pvector, qvector)
    };
}

MCInline MCQuaternion MCQuaternionArrayGProduct(MCQuaternion p, MCQuaternion* qarray, int count)
{
    if (count < 1) {
        return p;
    }
    MCQuaternion q = p;
    for (int i=0; i<count; i++) {
        q = MCQuaternionGProduct(q, qarray[i]);
    }
    return q;
}

MCInline MCQuaternion MCQuaternionConjugate(MCQuaternion q)
{
    return (MCQuaternion) { -q.x, -q.y, -q.z, q.w };
}

MCInline MCQuaternion MCQuaternionFromAxisAngle_Radian(MCVector3 axis, double radian)
{
    double r = radian / 2.0f;
    return (MCQuaternion) {
        axis.x * sin(r),
        axis.y * sin(r),
        axis.z * sin(r),
        cos(r)
    };
}

MCInline MCQuaternion MCQuaternionSwapYZ(MCQuaternion* q)
{
    MCVector3 axis = (MCVector3){q->x, q->y, q->z};
    double radian = q->w;
    
    double r = radian / 2.0f;
    return (MCQuaternion) {
        axis.x * sin(r),
        axis.z * sin(r),
        axis.y * sin(r),
        cos(r)
    };
}

MCInline MCQuaternion MCQuaternionFromAxisAngle(MCVector3 axis, double tht)
{
    return MCQuaternionFromAxisAngle_Radian(axis, MCDegreesToRadians(tht));
}

MCInline MCQuaternion MCQuaternionByEuler_Radian(double row, double yaw, double pitch)
{
    //roll yaw pitch => +z +y +x
    MCQuaternion R = MCQuaternionFromAxisAngle_Radian(MCVector3Make(0.0, 0.0, 1.0), row);
    MCQuaternion Y = MCQuaternionFromAxisAngle_Radian(MCVector3Make(0.0, 1.0, 0.0), yaw);
    MCQuaternion P = MCQuaternionFromAxisAngle_Radian(MCVector3Make(1.0, 0.0, 0.0), pitch);
    
    MCQuaternion qarray[2] = {Y, P};
    
    return MCQuaternionArrayGProduct(R, qarray, 2);
}

MCInline MCQuaternion MCQuaternionByAxisAngles(double x, double y, double z)
{
    //roll yaw pitch => +z +y +x
    return MCQuaternionByEuler_Radian(MCDegreesToRadians(z),
                                      MCDegreesToRadians(y),
                                      MCDegreesToRadians(x));
}

MCInline MCVector3 MCVector3RotateByQuaternion(MCVector3 v, MCQuaternion q)
{
    MCQuaternion r1 = MCQuaternionGProduct(q, (MCQuaternion){v.x, v.y, v.z, 0.0f});
    MCQuaternion r2 = MCQuaternionGProduct(r1, MCQuaternionConjugate(q));
    return (MCVector3){r2.x, r2.y, r2.z};
}

MCInline MCVector3 MCVector3RotateByAxisAngles(MCVector3 v, double z, double y, double x)
{
    return MCVector3RotateByQuaternion(v, MCQuaternionByAxisAngles(z,y,x));
}

MCInline MCVector3 MCNormalOfTriangle(MCVector3 v1, MCVector3 v2, MCVector3 v3) {
    return MCVector3Cross(MCVector3Sub(v2, v1), MCVector3Sub(v3, v1));
}

MCInline MCBool MCMatrix3Equal(const MCMatrix3* l, const MCMatrix3* r)
{
    for (int i=0; i<9; i++) {
        if(!MCSamefloat(l->m[i], r->m[i]))
            return false;
    }
    return true;
}

MCInline MCBool MCMatrix4Equal(const MCMatrix4* l, const MCMatrix4* r)
{
    for (int i=0; i<16; i++) {
        if(!MCSamefloat(l->m[i], r->m[i]))
            return false;
    }
    return true;
}

MCInline MCMatrix3* MCMatrix3Copy(float* src, MCMatrix3* dst)
{
    if (src && dst) {
        for (int i=0; i<9; i++) {
            dst->m[i] = src[i];
        }
        return dst;
    }
    return null;
}

MCInline MCMatrix4* MCMatrix4CopyDiff(float* src, MCMatrix4* dst, float delta)
{
    if (src && dst) {
        for (int i=0; i<16; i++) {
            if (fabs(dst->m[i] - src[i]) > delta) {
                dst->m[i] = src[i];
            }
        }
        return dst;
    }
    return null;
}

MCInline MCMatrix4* MCMatrix4Copy(float* src, MCMatrix4* dst)
{
    if (src && dst) {
        for (int i=0; i<16; i++) {
            dst->m[i] = src[i];
        }
        return dst;
    }
    return null;
}

MCInline MCMatrix4* MCMatrix4CopyDouble(double* src, MCMatrix4* dst)
{
    if (src && dst) {
        for (int i=0; i<16; i++) {
            dst->m[i] = (float)src[i];
        }
        return dst;
    }
    return null;
}

//column major data order!
MCInline MCMatrix4 MCMatrix4Make(float* data)
{
    MCMatrix4 mat;
    MCMatrix4Copy(data, &mat);
    return mat;
}

MCInline MCMatrix4 MCMatrix4MakeDouble(double* data)
{
    MCMatrix4 mat;
    MCMatrix4CopyDouble(data, &mat);
    return mat;
}

MCInline MCMatrix3 MCMatrix3Multiply(MCMatrix3 l, MCMatrix3 r)
{
    MCMatrix3 m;
    
    m.m[0] = l.m[0] * r.m[0] + l.m[3] * r.m[1] + l.m[6] * r.m[2];
    m.m[3] = l.m[0] * r.m[3] + l.m[3] * r.m[4] + l.m[6] * r.m[5];
    m.m[6] = l.m[0] * r.m[6] + l.m[3] * r.m[7] + l.m[6] * r.m[8];

    m.m[1] = l.m[1] * r.m[0] + l.m[4] * r.m[1] + l.m[7] * r.m[2];
    m.m[4] = l.m[1] * r.m[3] + l.m[4] * r.m[4] + l.m[7] * r.m[5];
    m.m[7] = l.m[1] * r.m[6] + l.m[4] * r.m[7] + l.m[7] * r.m[8];
    
    m.m[2] = l.m[2] * r.m[0] + l.m[5] * r.m[1] + l.m[8] * r.m[2];
    m.m[5] = l.m[2] * r.m[3] + l.m[5] * r.m[4] + l.m[8] * r.m[5];
    m.m[8] = l.m[2] * r.m[6] + l.m[5] * r.m[7] + l.m[8] * r.m[8];
    
    return m;
}

//OpenGL use column-order save matrix
MCInline MCMatrix4 MCMatrix4Multiply(MCMatrix4 l, MCMatrix4 r)
{
    MCMatrix4 m;
    
    m.m[0]  = l.m[0] * r.m[0]  + l.m[4] * r.m[1]  + l.m[8] * r.m[2]   + l.m[12] * r.m[3];
    m.m[4]  = l.m[0] * r.m[4]  + l.m[4] * r.m[5]  + l.m[8] * r.m[6]   + l.m[12] * r.m[7];
    m.m[8]  = l.m[0] * r.m[8]  + l.m[4] * r.m[9]  + l.m[8] * r.m[10]  + l.m[12] * r.m[11];
    m.m[12] = l.m[0] * r.m[12] + l.m[4] * r.m[13] + l.m[8] * r.m[14]  + l.m[12] * r.m[15];
    
    m.m[1]  = l.m[1] * r.m[0]  + l.m[5] * r.m[1]  + l.m[9] * r.m[2]   + l.m[13] * r.m[3];
    m.m[5]  = l.m[1] * r.m[4]  + l.m[5] * r.m[5]  + l.m[9] * r.m[6]   + l.m[13] * r.m[7];
    m.m[9]  = l.m[1] * r.m[8]  + l.m[5] * r.m[9]  + l.m[9] * r.m[10]  + l.m[13] * r.m[11];
    m.m[13] = l.m[1] * r.m[12] + l.m[5] * r.m[13] + l.m[9] * r.m[14]  + l.m[13] * r.m[15];
    
    m.m[2]  = l.m[2] * r.m[0]  + l.m[6] * r.m[1]  + l.m[10] * r.m[2]  + l.m[14] * r.m[3];
    m.m[6]  = l.m[2] * r.m[4]  + l.m[6] * r.m[5]  + l.m[10] * r.m[6]  + l.m[14] * r.m[7];
    m.m[10] = l.m[2] * r.m[8]  + l.m[6] * r.m[9]  + l.m[10] * r.m[10] + l.m[14] * r.m[11];
    m.m[14] = l.m[2] * r.m[12] + l.m[6] * r.m[13] + l.m[10] * r.m[14] + l.m[14] * r.m[15];
    
    m.m[3]  = l.m[3] * r.m[0]  + l.m[7] * r.m[1]  + l.m[11] * r.m[2]  + l.m[15] * r.m[3];
    m.m[7]  = l.m[3] * r.m[4]  + l.m[7] * r.m[5]  + l.m[11] * r.m[6]  + l.m[15] * r.m[7];
    m.m[11] = l.m[3] * r.m[8]  + l.m[7] * r.m[9]  + l.m[11] * r.m[10] + l.m[15] * r.m[11];
    m.m[15] = l.m[3] * r.m[12] + l.m[7] * r.m[13] + l.m[11] * r.m[14] + l.m[15] * r.m[15];
    
    return m;
}

MCInline MCVector3 MCVector3MultiplyMat3(MCVector3 vec3, MCMatrix3 mat3)
{
    MCVector3 v;
    v.x = vec3.x * mat3.m00 + vec3.y * mat3.m10 + vec3.z * mat3.m20;
    v.y = vec3.x * mat3.m01 + vec3.y * mat3.m11 + vec3.z * mat3.m21;
    v.z = vec3.x * mat3.m02 + vec3.y * mat3.m12 + vec3.z * mat3.m22;
    return v;
}

//Prime
utility(MCMath, MCBool, isPrime, int a);
//Power of two
utility(MCMath, MCBool, isPowerOfTwo, unsigned a);

utility(MCMath, void, bye, voida);
utility(MCMath, int, addInteger2, int a, int b);

utility(MCMath, void, sortInt, int* sorted, size_t count);
utility(MCMath, void, sortLong, long* sorted, size_t count);
utility(MCMath, void, sortSizet, size_t* sorted, size_t count);

utility(MCMath, int, accumulateMaxi, int* result, int value);
utility(MCMath, int, accumulateMini, int* result, int value);

utility(MCMath, double, accumulateMaxd, double* result, double value);
utility(MCMath, double, accumulateMind, double* result, double value);

//Chebyshev distance
utility(MCMath, unsigned, chebyshevDiatance, MCVector2i A, MCVector2i B);
//Factorial
utility(MCMath, unsigned, factorialOf, unsigned N);
//Permutation
utility(MCMath, unsigned, KpermutationsOfN, unsigned K, unsigned N);
//Combination
utility(MCMath, unsigned, KcombinationsOfN, unsigned K, unsigned N);



#endif
