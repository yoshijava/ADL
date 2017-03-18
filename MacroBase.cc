#include <iostream>

using namespace std;
#define HAVE_ISA

#define DECLARE_I32(x, val) \
    int i_##x = val;

#define ADD_32(x, y, z) \
    add_32_have_impl(i_##x, i_##y, i_##z); \

#define ADD_32_IMM16(x, y, z) \
    add_32_imm16_have_impl(i_##x, i_##y, z); \

#define ADD_SAT32(x, y, z) \
    add_sat32_have_impl(i_##x, i_##y, i_##z); \

#define RSHIFT(x, y, z) \
    rshift_have_impl(i_##x, i_##y, i_##z); \

#define LSHIFT(x, y, z) \
    lshift_have_impl(i_##x, i_##y, i_##z); \

#define MUL_32(x, y, z) \
    mul32_have_impl(i_##x, i_##y, i_##z);

void lshift_have_impl(int &x, int y, int z) {
    x = y << z;
    printf("s_lshift.%d 0x%08x, 0x%08x\n", z, x, y);
}

void rshift_have_impl(int &x, int y, int z) {
    x = y >> z;
    printf("s_rshift.%d 0x%08x, 0x%08x\n", z, x, y);
}

void mul32_have_impl(int &x, int y, int z) {
    x = y * z;
    printf("s_mul.i_i, 0x%08x, 0x%08x, 0x%08x\n", x, y, z);
}

void add_32_imm16_have_impl(int &x, int y, int z) {
    x = y + static_cast<short>(z);
    printf("s_add.i_i, 0x%08x, 0x%08x, 0x%08x\n", x, y, z);
}

void add_32_have_impl(int &x, int y, int z) {
    x = y + z;
    printf("s_add.i_i, 0x%08x, 0x%08x, 0x%08x\n", x, y, z);
}

void add_sat32_have_impl(int &x, int y, int z) {
    // HAVE SPU implementation, assuming saturation add
    long long result = static_cast<long long>(y) + static_cast<long long>(z);
    if(result > INT_MAX) {
        x = INT_MAX;
    }
    else if(result < INT_MIN) {
        x = INT_MIN;
    }
    else {
        x = static_cast<int>(result);
    }
    printf("s_add_sat.i_i, 0x%08x, 0x%08x, 0x%08x\n", x, y, z);
}

int main(int argc, char *argv[]) {
    DECLARE_I32(result, 0)
    DECLARE_I32(r0, 0x7fffffff)
    DECLARE_I32(r1, 0x1)

    ADD_SAT32(result, r0, r1)
    ADD_32_IMM16(result, r1, 0x1)

    DECLARE_I32(r2, 2)
    MUL_32(result, result, r2)
    RSHIFT(result, result, r2)
    LSHIFT(result, result, r2)
    return 0;
}