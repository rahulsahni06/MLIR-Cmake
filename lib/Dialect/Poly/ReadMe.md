The expected way to set up the C++ interface to the tablegen files is:

1. For every `.h.inc` file, we should create the corresponding `.h` and include the `.h.inc` file by defining the appropriate macros
2. For every `.cpp.inc` file, we should create the corresponding `.cpp` and include the `.cpp.inc` file by defining the appropriate macros. And the `.cpp` file should include the corresponding `.h` file