# ADL
Architectural Description Language

This is a repository to practice any programming skill which helps architectural design, especially ISA-related.

# Hiding the details of assembly operations
e.g., 

    DECLARE_I32(result, 0)
    DECLARE_I32(r0, 0x7fffffff)
    DECLARE_I32(r1, 0x1)
    // Operator overload. It calls the underlying saturation add implementation
    // Defined as operator +
    result = r0 + r1;
    cout << "r0 = " << r0 << endl;
    cout << "r1 = " << r1 << endl;
    cout << "r0 + r1 = " << result << endl;
    
Output:

    s_add_sat.i_i, result=0x7fffffff, r0=0x7fffffff, r1=0x00000001
    r0 = 2147483647
    r1 = 1
    r0 + r1 = 2147483647

Example: Saturation add Fibonacci sequence
    void sample2_fibonacci_with_saturation_add()
    {
        DECLARE_I32(r1, 1)
        DECLARE_I32(r2, 1)
        DECLARE_I32(r3, 1)

        for (int i = 0; i < 50; i++)
        {
            r3 = r1 % r2;
            r1 = r2;
            r2 = r3;
            cout << "Value = " << r3 << endl;
        }
    }
    
Output:
    s_add_sat.i_i, result=0x00000002, r1=0x00000001, r2=0x00000001
    Value = 2
    s_add_sat.i_i, result=0x00000003, r2=0x00000001, result=0x00000002
    Value = 3
    s_add_sat.i_i, result=0x00000005, result=0x00000002, result=0x00000003
    Value = 5
    s_add_sat.i_i, result=0x00000008, result=0x00000003, result=0x00000005
    Value = 8
    s_add_sat.i_i, result=0x0000000d, result=0x00000005, result=0x00000008
    ......
    s_add_sat.i_i, result=0x43a53f82, result=0x19d699a5, result=0x29cea5dd
    Value = 1134903170
    s_add_sat.i_i, result=0x6d73e55f, result=0x29cea5dd, result=0x43a53f82
    Value = 1836311903
    s_add_sat.i_i, result=0x7fffffff, result=0x43a53f82, result=0x6d73e55f
    Value = 2147483647
    s_add_sat.i_i, result=0x7fffffff, result=0x6d73e55f, result=0x7fffffff
    Value = 2147483647
    s_add_sat.i_i, result=0x7fffffff, result=0x7fffffff, result=0x7fffffff
    Value = 2147483647
    s_add_sat.i_i, result=0x7fffffff, result=0x7fffffff, result=0x7fffffff
    Value = 2147483647
    s_add_sat.i_i, result=0x7fffffff, result=0x7fffffff, result=0x7fffffff
    Value = 2147483647
    s_add_sat.i_i, result=0x7fffffff, result=0x7fffffff, result=0x7fffffff
    Value = 2147483647
