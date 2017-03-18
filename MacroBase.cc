#include <iostream>
#include "Scalar.h"

#define MY_ISA
#define NUM_VEC_LANES 64

using namespace std;

int main(int argc, char *argv[])
{
    DECLARE_I32(result, 0)
    DECLARE_I32(r0, 0x7fffffff)
    DECLARE_I32(r1, 0x1)

    ADD_SAT32(result, r0, r1)
    ADD_32_IMM16(result, r1, 0x1)

    DECLARE_I32(r2, 4)
    MUL_32(result, r2, r2)
    RSHIFT(result, r2, r1)
    LSHIFT(result, r2, r1)

    DECLARE_I32(r3, 1)
    for(int i=0; i<7; i++) {
        LSHIFT_IMM16(r3, r3, 1)
    }

    return 0;
}