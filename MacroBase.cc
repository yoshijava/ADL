#include <iostream>

using namespace std;
#define HAVE_ISA

#define DECLARE_U32(x, val) \
    int i_##x = val;

#define ADD32(x, y, z) \
    add32_have_impl(i_##x, i_##y, i_##z);

void add32_have_impl(int x, int y, int z) {
    // HAVE SPU implementation, assuming saturation add
#ifdef HAVE_ISA
    long long result = static_cast<long long>(y) + static_cast<long long>(z);
    cout << result << endl;
    if(result > INT_MAX) {
        x = INT_MAX;
    }
    else if(result < INT_MIN) {
        x = INT_MIN;
    }
    else {
        x = static_cast<int>(result);
    }
#else
    x = y + z;
#endif
    printf("%s, 0x%08x, 0x%08x, 0x%08x\n", "s_addsat.i_i", x, y, z);
}

int main(int argc, char *argv[]) {
    DECLARE_U32(result, 0)
    DECLARE_U32(r0, 0x7fffffff)
    DECLARE_U32(r1, 0x1)
    ADD32(result, r0, r1)
    return 0;
}