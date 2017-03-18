#include <iostream>
// #include <string>

using namespace std;

#define DECLARE_U32(x, val) \
    int i_##x = val;

#define ADD32(x, y, z) \
    i_##x = i_##y + i_##z; \
    add32_have_impl(i_##x, i_##y, i_##z); // HAVE
    

void add32_have_impl(int x, int y, int z) {
    // HAVE SPU implementation
    printf("%s, 0x%08x, 0x%08x, 0x%08x\n", "s_add.i_i", x, y, z);
}

void add32_x86_impl(int x, int y, int z) {
    // x86 implementation
    printf("%s, 0x%08x, 0x%08x, 0x%08x\n", "ADD", x, y, z);
}

int main(int argc, char *argv[]) {
    DECLARE_U32(result, 0)
    DECLARE_U32(r0, 1)
    DECLARE_U32(r1, 2)
    ADD32(result, r0, r1)
    return 0;
}