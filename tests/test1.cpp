#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <String>

using namespace rui;
using namespace std;

TEST_CASE("Constructors and string conversion") {
    String s = "123"
           , s1("123")
           , s2(std::string("123"))
           , s3(L"123")
           , s4(String("123"))
           ;  

    CHECK(s.str() == "123");
    CHECK(s2.str() == "123");
    CHECK(s3.str() == "123");
    CHECK(s4.str() == "123");
}
