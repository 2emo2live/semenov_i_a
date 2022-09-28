#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <bitseti/bitseti.h>
#include <bitset/bitset.h>
#include <iostream>
#include <sstream>
#include <vector>

TEST_CASE("[bitset] - Bitset ctor") {
    Bitset b = Bitset();
    CHECK((b.size() == 0));
    CHECK((Bitset(1) == Bitset(1, 0)));
    CHECK_THROWS(Bitset(-1));
    CHECK_THROWS(Bitset(-1, 1));
    CHECK_THROWS(Bitset(-14, 0));
}

TEST_CASE("[bitset] - Bitset operator=") {
    std::vector <Bitset> test{ Bitset(),
                               Bitset(1, 0),
                               Bitset(15, 1) };
    for (int i = 0; i < test.size(); i++) {
        Bitset a = test[i];
        CHECK_EQ(a, test[i]);
        Bitset b;
        b = test[i];
        CHECK_EQ(b, test[i]);
    }
}

TEST_CASE("[bitset] - Bitset comparison") {
    Bitset a = Bitset(10, 1);
    Bitset b = Bitset(10, 1);
    CHECK(a == b);
    a[2] = 0;
    CHECK(a != b);
    a[2] = 1;
    CHECK(a == b);
    b.resize(11);
    CHECK(a != b);
    b.resize(9);
    CHECK(a != b);
}

TEST_CASE("[bitset] - Bitset indexation") {
    Bitset a = Bitset(134, 0);
    CHECK_THROWS(a[-1]);
    CHECK_THROWS(a[134]);
    CHECK_THROWS(a[143]);
    CHECK(a[1] == 0);
    CHECK(a[0] == 0);
    CHECK(a[133] == 0);
    a[7] = 1;
    CHECK(a[7] == 1);
}

TEST_CASE("[bitset] - binary operations") {
    Bitset a = Bitset(10, 0);
    Bitset b = Bitset(11, 1);
    CHECK_THROWS(a & b);
    CHECK_THROWS(a | b);
    CHECK_THROWS(a ^ b);
    b = Bitset(10, 1);
    CHECK_EQ(a & b, Bitset(10, 0));
    CHECK_EQ(a | b, Bitset(10, 1));
    CHECK_EQ(a ^ b, Bitset(10, 1));
    a = Bitset(10, 1);
    CHECK_EQ(a & b, Bitset(10, 1));
    CHECK_EQ(a | b, Bitset(10, 1));
    CHECK_EQ(a ^ b, Bitset(10, 0));
    a = Bitset(10, 0);
    b = Bitset(10, 0);
    CHECK_EQ(a & b, Bitset(10, 0));
    CHECK_EQ(a | b, Bitset(10, 0));
    CHECK_EQ(a ^ b, Bitset(10, 0));
    a[0] = 1;
    b[7] = 1;
    Bitset c = Bitset(10, 0);
    c[0] = 1;
    c[7] = 1;
    CHECK_EQ(a & b, Bitset(10, 0));
    CHECK_EQ(a | b, c);
    CHECK_EQ(a ^ b, c);
}

TEST_CASE("[bitset] - resize") {
    Bitset b = Bitset(248, 1);
    b.resize(348, 0);
    CHECK(b.size() == 348);
    for (int i = 347; i > 247; i--)
        CHECK(b[i] == 0);
    for (int i = 247; i >= 0; i--)
        CHECK(b[i] == 1);
    b.resize(248);
    CHECK(b.size() == 248);
    for (int i = 247; i >= 0; i--)
        CHECK(b[i] == 1);
    b.resize(500, 1);
    CHECK(b.size() == 500);
    for (int i = 499; i >= 0; i--)
        CHECK(b[i] == 1);
    b[32] = 0;
    b.resize(148, 1);
    CHECK(b[32] == 0);
}

TEST_CASE("[bitset] - shifts") {
    Bitset b = Bitset(250, 1);
    b <<= 100;
    for (int i = 249; i > 99; i--)
        CHECK(b[i] == 1);
    for (int i = 99; i >= 0; i--)
        CHECK(b[i] == 0);
    b >>= 200;
    for (int i = 249; i > 49; i--)
        CHECK(b[i] == 0);
    for (int i = 49; i >= 0; i--)
        CHECK(b[i] == 1);
    b = Bitset(300, 1);
    b <<= 300;
    for (int i = 299; i >= 0; i--)
        CHECK(b[i] == 0);
    b[267] = 1;
    b >>= 200;
    CHECK(b[67] == 1);
    b <<= 173;
    CHECK(b[240] == 1);
}

TEST_CASE("[bitset] - output") {
    Bitset b = Bitset(257, 1);
    std::stringstream strm;
    strm << b;
    Bitset a;
    strm >> a;
    CHECK_EQ(a, b);
}

TEST_CASE("[bitset] - input") {
    std::vector<std::string> right{ "10000101001010 ", "1111", "1111111fb", "   1101      ", "1 ", "111101111111111111111111111111111111111111111111111111111111111111111111"};
    std::vector<std::string> wrong{ "adsdad", "22a"};

    std::vector<Bitset> ans{Bitset(14, 0), Bitset(4, 1), Bitset(7, 1), Bitset(4, 1), Bitset(1, 1), Bitset(72, 1)};
    ans[0][1] = 1;
    ans[0][3] = 1;
    ans[0][6] = 1;
    ans[0][8] = 1;
    ans[0][13] = 1;
    ans[3][1] = 0;
    ans[5][67] = 0;

    for (int i = 0; i < right.size(); i++) {
        std::stringstream strm(right[i]);
        Bitset b;
        strm >> b;
        CHECK(b == ans[i]);
        CHECK((((strm.good()) || (strm.eof())) && (strm.bad() == false)));
    }
    std::cout << '!';
    for (int i = 0; i < wrong.size(); i++) {
        std::stringstream strm(wrong[i]);
        Bitset b;
        strm >> b;
        CHECK(b == Bitset());
        CHECK(strm.fail() == true);
    }
}