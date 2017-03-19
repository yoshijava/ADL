#include <iostream>
#include "Scalar.h"
#include "Vector.h"
#define MY_ISA


using namespace std;

int main(int argc, char *argv[])
{
    DECLARE_I32(result, 0)
    DECLARE_I32(r0, 0x7fffffff)
    DECLARE_I32(r1, 0x1)

    // Normal scalar operations
    ADD_32_SAT(result, r0, r1)
    ADD_32_IMM16(result, r1, 0x1)
    DECLARE_I32(r2, 4)
    MUL_32(result, r2, r2)
    RSHIFT(result, r2, r1)
    LSHIFT(result, r2, r1)

    // Vector lshift
    DECLARE_I32(r3, 1)
    for(int i=0; i<7; i++) {
        LSHIFT_IMM16(r3, r3, 1)
    }

    DECLARE_VEC_I32(v1, 1);
    LSHIFT_VEC(v1, v1, r1)
    cout << "Print vector variable:" << endl;
    cout << "v1 = " << v1 << endl;
    // Operator overload. It calls the underlying saturation add implementation
    // Defined as operator %
    result = r0 % r1;
    cout << "r0 = " << r0 << endl;
    cout << "r1 = " << r1 << endl;
    cout << "r0 % r1 = " << result << endl;

    return 0;
}