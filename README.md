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
