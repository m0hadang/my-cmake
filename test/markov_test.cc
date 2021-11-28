#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <markov/markov.hh>
#include <markov/random/simple-random-gen.hh>

using namespace std;
using namespace mohadangkim;
using ::testing::Return;

extern char* NONWORD;
using ::NONWORD;

class RandomGenMock : public IRandomGen {
public:
	MOCK_METHOD(int, rand, (), (override));
};

inline unique_ptr<RandomGenMock> GetRandomMock() {
	unique_ptr<RandomGenMock> random_gen_mock = std::make_unique<RandomGenMock>();
	EXPECT_CALL(*random_gen_mock, rand)
		.WillRepeatedly(Return(1));

	return random_gen_mock;
}

TEST(RANDOM_GEN, rand) {
	unique_ptr<RandomGenMock> random_gen_mock = GetRandomMock();
	std::cout << random_gen_mock->rand() << std::endl;
	std::cout << random_gen_mock->rand() << std::endl;
	std::cout << random_gen_mock->rand() << std::endl;
}

TEST(MARKOV, add1) {
	Markov markov(GetRandomMock());
	Prefix prefix;
	markov.add(prefix, "abc");
	EXPECT_STREQ(prefix[0].c_str(), "abc");
	EXPECT_EQ(prefix.size(), 1);
}
TEST(MARKOV, add2) {
	Prefix prefix;
	RandomGenMock random_gen_mock;
	Markov markov(GetRandomMock());

	markov.add(prefix, "abc");
	markov.add(prefix, "def");
	EXPECT_STREQ(prefix[0].c_str(), "abc");
	EXPECT_STREQ(prefix[1].c_str(), "def");
	EXPECT_EQ(prefix.size(), 2);
}
TEST(MARKOV, add3) {
	Prefix prefix;
	RandomGenMock random_gen_mock;
	Markov markov(GetRandomMock());

	markov.add(prefix, "abc");
	markov.add(prefix, "def");
	markov.add(prefix, "123");
	EXPECT_STREQ(prefix[0].c_str(), "def");
	EXPECT_STREQ(prefix[1].c_str(), "123");
	EXPECT_EQ(prefix.size(), 2);
}
TEST(MARKOV, build0) {
	Prefix prefix;
	RandomGenMock random_gen_mock;
	Markov markov(GetRandomMock());

	std::stringstream stm;
	markov.build(prefix, stm);

	int i = 0;
	for (i = 0; i < NPREF - 1; ++i) {
		EXPECT_STREQ(prefix[i].c_str(), ::NONWORD);
	}
	EXPECT_STREQ(prefix[i].c_str(), ::NONWORD);

	EXPECT_EQ(prefix.size(), NPREF);
}
TEST(MARKOV, build1) {
	Prefix prefix;
	RandomGenMock random_gen_mock;
	Markov markov(GetRandomMock());

	std::stringstream stm;
	stm << "abc" << std::endl;
	markov.build(prefix, stm);

	EXPECT_STREQ(prefix[0].c_str(), "abc");
	EXPECT_STREQ(prefix[1].c_str(), ::NONWORD);
	EXPECT_EQ(prefix.size(), 2);
}
TEST(MARKOV, build2) {
	Prefix prefix;
	RandomGenMock random_gen_mock;
	Markov markov(GetRandomMock());

	std::stringstream stm;
	stm << "abc" << " " << "def" << std::endl;
	markov.build(prefix, stm);

	EXPECT_STREQ(prefix[0].c_str(), "def");
	EXPECT_STREQ(prefix[1].c_str(), ::NONWORD);
	EXPECT_EQ(prefix.size(), 2);
}
TEST(MARKOV, build3) {
	Prefix prefix;
	RandomGenMock random_gen_mock;
	Markov markov(GetRandomMock());

	std::stringstream stm;
	stm <<
		"abc" << " " <<
		"def" << " " <<
		"123" << std::endl;

	markov.build(prefix, stm);

	EXPECT_STREQ(prefix[0].c_str(), "123");
	EXPECT_STREQ(prefix[1].c_str(), ::NONWORD);
	EXPECT_EQ(prefix.size(), 2);
}

TEST(MARKOV, generate) {
	Prefix prefix;
	RandomGenMock random_gen_mock;
	Markov markov(GetRandomMock());

	std::stringstream stm;
	stm <<
		"1" << " " <<
		"2" << " " <<
		"3" << std::endl;

	markov.build(prefix, stm);

	std::stringstream out;
	markov.generate(10, out);	
	EXPECT_STREQ(out.str().c_str(), "1 2 3 (end)");
}
