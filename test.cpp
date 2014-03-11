#include "test.hpp"
#include <iostream>

//need definition before used by sample class.
class implement {
    public:
    implement():val(0){}
    implement(int v):val(v){}
    void method(){}
    int val;
};


sample::sample(){}

void sample::func() {
    pvalue->method();


    //test
    (*pvalue).method();
    pvalue.get();

    sample s;
    swap(pvalue, s.pvalue);
    pvalue = gununu::make_pimpl<implement>();
    if (pvalue) {}
    pvalue = gununu::pimpl<implement>(implement(3));
    std::cout << pvalue->val;
}
