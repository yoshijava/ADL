#include "Vector.h"
#include <cstdio>
#include <climits>

void lshift_v_my_isa_impl(Var_v<int> &x, Var_v<int> y, Var<int> z)
{
    for(int i=0; i<NUM_VEC_LANES; i++) {
        x.val[i] = y.val[i] << z.val;
        printf("v_lshift_%d %s[%d]=0x%08x, %s[%d]=0x%08x\n", z.val, x.name, i, x.val[i], y.name, i, y.val[i]);
    }
}
