#ifndef MOHADANGKIM_MARKKOV_MARKKOV
#define MOHADANGKIM_MARKKOV_MARKKOV

#ifndef MARKOV_API
#    ifdef _WIN32
#        if defined(BUILD_SHARED) /* build dll */
#            define MARKOV_API __declspec(dllexport)
#        elif !defined(BUILD_STATIC) /* use dll */
#            define MARKOV_API __declspec(dllimport)
#        else /* static library */
#            define MARKOV_API
#        endif
#    else
#        if __GNUC__ >= 4
#            define MARKOV_API __attribute__((visibility("default")))
#        else
#            define MARKOV_API
#        endif
#    endif
#endif

#include <deque>
#include <map>

#include <vector>
#include <string>
#include <memory>
#include <markov/random/irandom-gen.hh>

namespace mohadangkim {

enum {
	NPREF = 2,// 접두사의 단어 수
	NHASH = 4093,// 상태를 저장할 해시 테이블의 배열 크기
	MAXGEN = 1000,// 생성할 수 있는 최대 단어 수
};

typedef std::deque<std::string> Prefix;

class MARKOV_API Markov {
private:
	std::map<Prefix, std::vector<std::string>> statetab;
	std::unique_ptr<IRandomGen> random_gen_;
	
public:
	Markov(std::unique_ptr<IRandomGen> random_gen);
	virtual ~Markov();
	void add(Prefix& prefix, const std::string& s);
	void build(Prefix& prefix, std::istream& in);
	void generate(int nwordsd, std::ostream& out);
};

extern char* NONWORD;//::일반 단어로 사용하지 못하는 단어

}



#endif