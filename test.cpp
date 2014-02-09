#include "test.hpp"

//need definition before used by sample class.
class implement {
    public:
    void method(){}
};


sample::sample(){}
sample::~sample(){}

void sample::func() {
    pvalue->method();
}
