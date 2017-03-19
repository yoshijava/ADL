#ifndef SCALAR_H_
#define SCALAR_H_
#include <iostream>

#define DECLARE_I32(x, val) Var<int> x(#x, val);
#define ADD_32(x, y, z) add_32_my_isa_impl(x, y, z);
#define ADD_32_IMM16(x, y, z) add_32_imm16_my_isa_impl(x, y, z);
#define ADD_32_SAT(x, y, z) add_32_sat_my_isa_impl(x, y, z);
#define RSHIFT(x, y, z) rshift_my_isa_impl(x, y, z);
#define LSHIFT(x, y, z) lshift_my_isa_impl(x, y, z);
#define LSHIFT_IMM16(x, y, z) lshift_imm16_my_isa_impl(x, y, z);
#define MUL_32(x, y, z) mul_32_my_isa_impl(x, y, z);

template <typename T>
class Var
{
public:
    T val;
    const char *name;
    Var(const char *name, T val)
    {
        this->name = name;
        this->val = val;
    }

    // this add function is defined as normal add
    inline friend Var<T> operator+(Var<T> &lhs, const Var<T> &rhs)
    {
        Var<T> result("result", 0);
        add_32_my_isa_impl(result, lhs, rhs);
        return result;
    }

    inline friend Var<T> operator*(Var<T> &lhs, const Var<T> &rhs)
    {
        Var<T> result("result", 0);
        mul_32_my_isa_impl(result, lhs, rhs);
        return result;
    }

    // saturation add, defined as 
    inline friend Var<T> operator%(Var<T> lhs, const Var<T> rhs)
    {
        Var<T> result("result", 0);
        add_32_sat_my_isa_impl(result, lhs, rhs);
        return result;
    }

    inline friend std::ostream& operator<<(std::ostream& os, const Var<T> &obj)
    {
        os << obj.val;
        return os;
    }
};

void lshift_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z);
void lshift_imm16_my_isa_impl(Var<int> &x, Var<int> y, short z);
void rshift_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z);
void mul_32_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z);
void add_32_imm16_my_isa_impl(Var<int> &x, Var<int> y, int z);
void add_32_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z);
void add_32_sat_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z);
#endif