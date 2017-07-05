#include "MCMath.h"

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