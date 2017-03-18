#include <iostream>

using namespace std;
#define MY_ISA
#define NUM_VEC_LANES 64

template <typename T>
struct Var
{
    T val;
    const char *name;
    Var(const char *name, T val)
    {
        this->name = name;
        this->val = val;
    }
};

#define DECLARE_I32(x, val) \
    Var<int> i_##x(#x, val);

#define ADD_32(x, y, z) \
    add_32_my_isa_impl(i_##x, i_##y, i_##z);

#define ADD_32_IMM16(x, y, z) \
    add_32_imm16_my_isa_impl(i_##x, i_##y, z);

#define ADD_SAT32(x, y, z) \
    add_sat32_my_isa_impl(i_##x, i_##y, i_##z);

#define RSHIFT(x, y, z) \
    rshift_my_isa_impl(i_##x, i_##y, i_##z);

#define LSHIFT(x, y, z) \
    lshift_my_isa_impl(i_##x, i_##y, i_##z);

#define MUL_32(x, y, z) \
    mul32_my_isa_impl(i_##x, i_##y, i_##z);

void lshift_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    x.val = y.val << z.val;
#ifdef MY_ISA
    printf("s_lshift.%d %s=0x%08x, %s=0x%08x\n", z.val, x.name, x.val, y.name, y.val);
#else
    printf("x86-lshift.%d %s=0x%08x, %s=0x%08x\n", z.val, x.name, x.val, y.name, y.val);
#endif
}

void rshift_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    x.val = y.val >> z.val;
#ifdef MY_ISA
    printf("s_rshift.%d %s=0x%08x, %s=0x%08x\n", z.val, x.name, x.val, y.name, y.val);
#else
    printf("x86-rshift.%d %s=0x%08x, %s=0x%08x\n", z.val, x.name, x.val, y.name, y.val);
#endif
}

void mul32_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    x.val = y.val * z.val;
#ifdef MY_ISA
    printf("s_mul.i_i, %s=0x%08x, %s=0x%08x, %s=0x%08x\n", x.name, x.val, y.name, y.val, z.name, z.val);
#else
    printf("x86-mul, %s=0x%08x, %s=0x%08x, %s=0x%08x\n", x.name, x.val, y.name, y.val, z.name, z.val);
#endif
}

void add_32_imm16_my_isa_impl(Var<int> &x, Var<int> y, int z)
{
    x.val = y.val + static_cast<short>(z);
#ifdef MY_ISA
    printf("s_add.i_i, %s=0x%08x, %s=0x%08x, 0x%08x\n", x.name, x.val, y.name, y.val, z);
#else
    printf("x86-addi, %s=0x%08x, %s=0x%08x, 0x%08x\n", x.name, x.val, y.name, y.val, z);
#endif
}

void add_32_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    x.val = y.val + z.val;
#ifdef MY_ISA
    printf("s_add.i_i, %s=0x%08x, %s=0x%08x, %s=0x%08x\n", x.name, x.val, y.name, y.val, z.name, z.val);
#else
    printf("x86-add, %s=0x%08x, %s=0x%08x, %s=0x%08x\n", x.name, x.val, y.name, y.val, z.name, z.val);
#endif
}

void add_sat32_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z)
{
    // my_isa SPU implementation, assuming saturation add
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
#ifdef MY_ISA
    printf("s_add_sat.i_i, %s=0x%08x, %s=0x%08x, %s=0x%08x\n", x.name, x.val, y.name, y.val, z.name, z.val);
#else
    printf("x86-add-sat, %s=0x%08x, %s=0x%08x, %s=0x%08x\n", x.name, x.val, y.name, y.val, z.name, z.val);
#endif
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