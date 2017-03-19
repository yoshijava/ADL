#include "Vector.h"
#include <cstdio>
#include <climits>
using namespace std;
void lshift_v_my_isa_impl(Var_v<int> &x, Var_v<int> y, Var<int> z)
{
    for(int i=0; i<NUM_VEC_LANES; i++) {
        x.val[i] = y.val[i] << z.val;
        // TODO change to the following cout in the future
        printf("v_lshift_%d %s[%d]=0x%08x, %s[%d]=0x%08x\n", z.val, x.name, i, x.val[i], y.name, i, y.val[i]);
    }
    // cout << x.name << " = " << x << ", ";
    // cout << y.name << " = " << y << ", ";
    // cout << z.name << " = " << z << ", " << endl;
}

void add_32_vec_sat_my_isa_impl(Var_v<int> &x, Var_v<int> y, Var_v<int> z) {
    long long result = 0;
    for(int i=0; i<NUM_VEC_LANES; i++) {
        result = y.val[i] + z.val[i];
        if(result > INT_MAX) {
            x.val[i] = INT_MAX;
        }
        else if(result < INT_MIN) {
            x.val[i] = INT_MIN;
        }
        else {
            x.val[i] = static_cast<int>(result);
        }
    }
    cout << "s_add_sat.i_i ";
    cout << x.name << " = " << x << ", ";
    cout << y.name << " = " << y << ", ";
    cout << z.name << " = " << z << ", " << endl;
}