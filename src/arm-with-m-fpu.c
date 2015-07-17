char *xml =                                                                     \
"<?xml version=\"1.0\"?>"                                                       \
                                                                                \
"<!DOCTYPE target SYSTEM \"gdb-target.dtd\">"                                   \
"<target>"                                                                      \
"   <!DOCTYPE feature SYSTEM \"gdb-target.dtd\">"                               \
"   <feature name=\"org.gnu.gdb.arm.m-profile\">"                               \
"        <reg name=\"r0\" bitsize=\"32\" type=\"uint32\"/>"                     \
"        <reg name=\"r1\" bitsize=\"32\" type=\"uint32\"/>"                     \
"        <reg name=\"r2\" bitsize=\"32\" type=\"uint32\"/>"                     \
"        <reg name=\"r3\" bitsize=\"32\" type=\"uint32\"/>"                     \
"        <reg name=\"r4\" bitsize=\"32\" type=\"uint32\"/>"                     \
"        <reg name=\"r5\" bitsize=\"32\" type=\"uint32\"/>"                     \
"        <reg name=\"r6\" bitsize=\"32\" type=\"uint32\"/>"                     \
"        <reg name=\"r7\" bitsize=\"32\" type=\"uint32\"/>"                     \
"        <reg name=\"r8\" bitsize=\"32\" type=\"uint32\"/>"                     \
"        <reg name=\"r9\" bitsize=\"32\" type=\"uint32\"/>"                     \
"        <reg name=\"r10\" bitsize=\"32\" type=\"uint32\"/>"                    \
"        <reg name=\"r11\" bitsize=\"32\" type=\"uint32\"/>"                    \
"        <reg name=\"r12\" bitsize=\"32\" type=\"uint32\"/>"                    \
"        <reg name=\"sp\" bitsize=\"32\" type=\"data_ptr\"/>"                   \
"        <reg name=\"lr\" bitsize=\"32\" type=\"uint32\"/>"                     \
"        <reg name=\"pc\" bitsize=\"32\" type=\"code_ptr\"/>"                   \
"        <reg name=\"xpsr\" bitsize=\"32\" type=\"uint32\" regnum=\"25\"/>"     \
"    </feature>"                                                                \
                                                                                \
"    <!DOCTYPE feature SYSTEM \"gdb-target.dtd\">"                              \
"    <feature name=\"org.gnu.gdb.arm.vfp\">"                                    \
"        <reg name=\"d0\" bitsize=\"32\" type=\"ieee_double\"/>"                \
"        <reg name=\"d1\" bitsize=\"32\" type=\"ieee_double\"/>"                \
"        <reg name=\"d2\" bitsize=\"32\" type=\"ieee_double\"/>"                \
"        <reg name=\"d3\" bitsize=\"32\" type=\"ieee_double\"/>"                \
"        <reg name=\"d4\" bitsize=\"32\" type=\"ieee_double\"/>"                \
"        <reg name=\"d5\" bitsize=\"32\" type=\"ieee_double\"/>"                \
"        <reg name=\"d6\" bitsize=\"32\" type=\"ieee_double\"/>"                \
"        <reg name=\"d7\" bitsize=\"32\" type=\"ieee_double\"/>"                \
"        <reg name=\"d8\" bitsize=\"32\" type=\"ieee_double\"/>"                \
"        <reg name=\"d9\" bitsize=\"32\" type=\"ieee_double\"/>"                \
"        <reg name=\"d10\" bitsize=\"32\" type=\"ieee_double\"/>"               \
"        <reg name=\"d11\" bitsize=\"32\" type=\"ieee_double\"/>"               \
"        <reg name=\"d12\" bitsize=\"32\" type=\"ieee_double\"/>"               \
"        <reg name=\"d13\" bitsize=\"32\" type=\"ieee_double\"/>"               \
"        <reg name=\"d14\" bitsize=\"32\" type=\"ieee_double\"/>"               \
"        <reg name=\"d15\" bitsize=\"32\" type=\"ieee_double\"/>"               \
                                                                                \
"        <reg name=\"fpscr\" bitsize=\"32\" type=\"int\" group=\"float\"/>"     \
"    </feature>"                                                                \
"</target>"
