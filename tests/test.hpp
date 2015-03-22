#include "../pimpl.hpp"


class implement; //declaration only

class sample {
    public:
    sample(); //need separation of constructor when without pimpl_noinit argument.

    gununu::pimpl<implement> pvalue;

    void func();
};
