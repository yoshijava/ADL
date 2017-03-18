#include <iostream>
#include "Scalar.h"

#define MY_ISA
#define NUM_VEC_LANES 64

using namespace std;

void lshift_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    x.val = y.val << z.val;
    printf("s_lshift.%d %s=0x%08x, %s=0x%08x\n", z.val, x.name, x.val, y.name, y.val);
}

void rshift_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    x.val = y.val >> z.val;
    printf("s_rshift.%d %s=0x%08x, %s=0x%08x\n", z.val, x.name, x.val, y.name, y.val);
}

void mul32_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    x.val = y.val * z.val;
    printf("s_mul.i_i, %s=0x%08x, %s=0x%08x, %s=0x%08x\n", x.name, x.val, y.name, y.val, z.name, z.val);
}

void add_32_imm16_my_isa_impl(Var<int> &x, Var<int> y, int z)
{
    x.val = y.val + static_cast<short>(z);
    printf("s_add.i_i, %s=0x%08x, %s=0x%08x, 0x%08x\n", x.name, x.val, y.name, y.val, z);
}

void add_32_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    x.val = y.val + z.val;
    printf("s_add.i_i, %s=0x%08x, %s=0x%08x, %s=0x%08x\n", x.name, x.val, y.name, y.val, z.name, z.val);
}

void add_sat32_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    // my_isa saturation add
    long long result = static_cast<long long>(y.val) + static_cast<long long>(z.val);
    if (result > INT_MAX)
    {
        x.val = INT_MAX;
    }
    else if (result < INT_MIN)
    {
        x.val = INT_MIN;
    }
    else
    {
        x.val = static_cast<int>(result);
    }
    printf("s_add_sat.i_i, %s=0x%08x, %s=0x%08x, %s=0x%08x\n", x.name, x.val, y.name, y.val, z.name, z.val);
}

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

    return 0;
}