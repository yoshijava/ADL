#include "Scalar.h"
#include <cstdio>
#include <climits>

void lshift_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    x.val = y.val << z.val;
    printf("s_lshift_%d %s=0x%08x, %s=0x%08x\n", z.val, x.name, x.val, y.name, y.val);
}

void lshift_imm16_my_isa_impl(Var<int> &x, Var<int> y, short z)
{
    x.val = y.val << z;
    printf("s_lshift_%d %s=0x%08x, %s=0x%08x\n", z, x.name, x.val, y.name, y.val);
}

void rshift_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    x.val = y.val >> z.val;
    printf("s_rshift_%d %s=0x%08x, %s=0x%08x\n", z.val, x.name, x.val, y.name, y.val);
}

void mul_32_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    x.val = y.val * z.val;
    printf("s_mul.i_i, %s=0x%08x, %s=0x%08x, %s=0x%08x\n", x.name, x.val, y.name, y.val, z.name, z.val);
}

void add_32_imm16_my_isa_impl(Var<int> &x, Var<int> y, int z)
{
    x.val = y.val + static_cast<short>(z);
    printf("s_add.i_imm16, %s=0x%08x, %s=0x%08x, 0x%08x\n", x.name, x.val, y.name, y.val, z);
}

void add_32_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    x.val = y.val + z.val;
    printf("s_add.i_i, %s=0x%08x, %s=0x%08x, %s=0x%08x\n", x.name, x.val, y.name, y.val, z.name, z.val);
}

void add_32_sat_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
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
