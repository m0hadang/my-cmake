#ifndef MOHADANGKIM_MARKKOV_IRANDOMGEN
#define MOHADANGKIM_MARKKOV_IRANDOMGEN
namespace mohadangkim {
class IRandomGen {
public:
	virtual int rand() = 0;
};
}
#endif