To fix compilation error with GCC, commented out line 57 of the header file in spot/misc/bitset.hh

It's just some assertions... likely fixed with newer version of GCC (I'm on 10)
Clang throws a lot of errors when trying to compile with libspot
May be better off manually building libspot in the future rather than using the packaged version
