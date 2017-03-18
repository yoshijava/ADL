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

void lshift_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z);
void rshift_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z);
void mul32_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z);
void add_32_imm16_my_isa_impl(Var<int> &x, Var<int> y, int z);
void add_32_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z);
void add_sat32_my_isa_impl(Var<int> &x, Var<int> y, Var<int> z);