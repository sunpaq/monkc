#include "MCMath.h"
#include "MCBits.h"

utility(MCMath, void, bye, voida)
{
	debug_log("%s\n", "MCMath bye bye");
}

utility(MCMath, int, addInteger2, int a, int b)
{
	return a + b;
}

utility(MCMath, void, sortInt, int* sorted, size_t count)
{
    for (int n=0; n<count-1; n++) {
        int temp;
        if (sorted[n+1] < sorted[n]) {
            //swap
            temp = sorted[n];
            sorted[n] = sorted[n+1];
            sorted[n+1] = temp;
        }
    }
}

utility(MCMath, void, sortLong, long* sorted, size_t count)
{
    for (int n=0; n<count-1; n++) {
        long temp;
        if (sorted[n+1] < sorted[n]) {
            //swap
            temp = sorted[n];
            sorted[n] = sorted[n+1];
            sorted[n+1] = temp;
        }
    }
}

utility(MCMath, void, sortSizet, size_t* sorted, size_t count)
{
    size_t trycount = count-1;
    while (trycount--) {
        for (int n=0; n<count-1; n++) {
            size_t temp;
            if (sorted[n+1] < sorted[n]) {
                //swap
                temp = sorted[n];
                sorted[n] = sorted[n+1];
                sorted[n+1] = temp;
            }
        }
    }
}

utility(MCMath, int, accumulateMaxi, int* result, int value)
{
    if (value > *result) {
        *result = value;
    }
    return *result;
}

utility(MCMath, int, accumulateMini, int* result, int value)
{
    if (value < *result) {
        *result = value;
    }
    return *result;
}

utility(MCMath, double, accumulateMaxd, double* result, double value)
{
    if (value > *result) {
        *result = value;
    }
    return *result;
}

utility(MCMath, double, accumulateMind, double* result, double value)
{
    if (value < *result) {
        *result = value;
    }
    return *result;
}

utility(MCMath, MCBool, isPrime, int a)
{
    for(int i=2;i<=sqrt(a);i++)
        if(a%i==0)
            return false;
    return true;
}

utility(MCMath, MCBool, isPowerOfTwo, unsigned a)
{
    return (MCBitsSetBitNum(a) == 1);
}

utility(MCMath, unsigned, chebyshevDiatance, MCVector2i A, MCVector2i B)
{
    return MAX(abs(B.x - A.x), abs(B.y - A.y));
}

utility(MCMath, unsigned, factorialOf, unsigned N)
{
    unsigned res = 1;
    for (unsigned i=N; i>0; i--)
        res *= i;
    return res;
}

utility(MCMath, unsigned, KpermutationsOfN, unsigned K, unsigned N)
{
    //P(n,k) = n! / (n-k)!
    unsigned res = 1;
    for (unsigned i=N; i>N-K; i--) {
        res *= i;
    }
    return res;
}

utility(MCMath, unsigned, KcombinationsOfN, unsigned K, unsigned N)
{
    //C(n,k) = P(n,k) / k! = n! / k! * (n-k)!
    return MCMath_KpermutationsOfN(K, N) / MCMath_factorialOf(K);
}


