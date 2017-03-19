#ifndef VECTOR_H
#define VECTOR_H
#include "Scalar.h"

#define NUM_VEC_LANES 4
#define DECLARE_VEC_I32(x, val) Var_v<int> x(#x, val);
// #define ADD_32(x, y, z) add_32_my_isa_impl(x, y, z);
// #define ADD_32_IMM16(x, y, z) add_32_imm16_my_isa_impl(x, y, z);
// #define ADD_SAT32(x, y, z) add_sat32_my_isa_impl(x, y, z);
// #define RSHIFT(x, y, z) rshift_my_isa_impl(x, y, z);
#define LSHIFT_VEC(x, y, z) lshift_v_my_isa_impl(x, y, z);
// #define LSHIFT_IMM16(x, y, z) lshift_imm16_my_isa_impl(x, y, z);
// #define MUL_32(x, y, z) mul32_my_isa_impl(x, y, z);

template <typename T>
class Var_v
{
public:
    T val[NUM_VEC_LANES];
    const char *name;
    Var_v(const char *name, T val)
    {
        this->name = name;
        for(int i=0; i<NUM_VEC_LANES; i++) {
            this->val[i] = val;
        }
    }

    inline friend std::ostream& operator<<(std::ostream& os, const Var_v<T> &obj)
    {
        os << "[";
        for(int i=0; i<NUM_VEC_LANES-1; i++) {
            os << obj.val[i] << ", ";
        }
        os << obj.val[NUM_VEC_LANES-1] << "]";
        return os;
    }
};

void lshift_v_my_isa_impl(Var_v<int> &x, Var_v<int> y, Var<int> z);
#endif