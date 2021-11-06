#include <iostream>
#include <memory>
#include <sstream>
#include <markov/markov.hh>
#include <markov/random/simple-random-gen.hh>

using namespace std;
using namespace mohadangkim;

int main() {
  Markov markov(std::make_unique<SimpleRandomGen>());
  Prefix prefix;
  std::stringstream stm;
  stm
    << "Show your flowcharts and conceal your tables and I will be "
    << "mystified. Show your tables and your flowcharts will be "
    << "obvious";

  markov.build(prefix, stm);
  markov.generate(MAXGEN, cout);
  return 0;
}