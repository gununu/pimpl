#include "../pimpl.hpp"


class implementation; //declaration only

class sample {
    public:
    sample(); //Define this constructor body to a cpp file, unless constructing the pimpl with a pimpl_noinit argument.

    gununu::pimpl<implementation> pvalue;

    // If you want to use the pimpl object, define a function body at a cpp file.
    void func();
};
