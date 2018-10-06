#include "test.hpp"
#include <iostream>

//need definition before used by sample class.
class implementation {
    public:
    implementation():val(0){}
    implementation(int v):val(v){}
    void method(){}
    int val;
};


sample::sample(){} //"pimpl<implementation> pvalue" is implicitly created here, so need definition of "implementation" class before this.

void sample::func() {
    pvalue->method();


    //test
    (*pvalue).method();
    pvalue.get();

    sample s;
    swap(pvalue, s.pvalue);
    pvalue = gununu::make_pimpl<implementation>();
    if (pvalue) {}
    pvalue = gununu::pimpl<implementation>(implementation(3));
    std::cout << "value: " << pvalue->val << std::endl;
}
