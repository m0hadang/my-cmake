#include <istream>
#include <markov/markov.hh>

using namespace mohadangkim;

const char* Markov::NONWORD = "\n";//일반 단어로 사용하지 못하는 단어

Markov::Markov(std::unique_ptr<IRandomGen> random_gen) :
  random_gen_(std::move(random_gen)) {
}

void Markov::add(Prefix& prefix, const std::string& s) {
  if (prefix.size() == NPREF) {
    statetab[prefix].emplace_back(s);
    prefix.pop_front();
  }
  prefix.emplace_back(s);
}

void Markov::build(Prefix& prefix, std::istream& in) {
  for (int i = 0; i < NPREF; ++i) {
    add(prefix, NONWORD);
  }
  std::string buf;
  while (in >> buf) {
    add(prefix, buf);
  }
  add(prefix, NONWORD);
}

void Markov::generate(int nwordsd, std::ostream& out) {
  Prefix prefix;
  for (int i = 0; i < NPREF; ++i) {
    add(prefix, NONWORD);
  }

  for (int i = 0; i < nwordsd; ++i) {
    std::vector<std::string>& suf = statetab[prefix];
    const std::string& w = suf[random_gen_->rand() % suf.size()];
    if (w == NONWORD) {
      break;
    }

    out << w << " ";
    prefix.pop_front();
    prefix.push_back(w);
  }
  out << "(end)";
}