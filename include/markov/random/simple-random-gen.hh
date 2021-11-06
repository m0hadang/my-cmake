#ifndef MOHADANGKIM_MARKKOV_SIMPLE_RANDOMGEN
#define MOHADANGKIM_MARKKOV_SIMPLE_RANDOMGEN

#include <markov/random/irandom-gen.hh>

namespace mohadangkim {
class SimpleRandomGen : public IRandomGen {
public:
	virtual int rand() override {
    return 1;
  }
};
}

#endif