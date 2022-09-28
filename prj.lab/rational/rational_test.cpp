#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <vector>
#include <string>
#include <rational/rational.h>

TEST_CASE("[rational] - Rational ctor") {
    CHECK((Rational() == Rational(0, 1)));
    CHECK((Rational(3) == Rational(3, 1)));
    CHECK((Rational(4, 8) == Rational(1, 2)));
    CHECK((Rational(4, -8) == Rational(-1, 2)));
    CHECK((Rational(-4, -8) == Rational(1, 2)));
    CHECK_THROWS(Rational(1, 0));
}

TEST_CASE("[rational] - ariphmetic") {
    CHECK(((Rational(1, 2) += Rational(1, 4)) == Rational(3, 4)));
    CHECK((Rational(1, 2) + Rational(-1, 4) == Rational(1, 4)));
    CHECK((Rational(1, 2) + 1 == Rational(3, 2)));
    CHECK((1 + Rational(1, 2) == Rational(3, 2)));
    CHECK((Rational(-1, 2) + 1 == Rational(1, 2)));
    CHECK((-1 + Rational(1, 2) == Rational(-1, 2)));
    CHECK((1 + Rational(-1, 2) == Rational(1, 2)));
    CHECK((Rational(1, 2) - Rational(1, 4) == Rational(1, 4)));
    CHECK((Rational(1, 2) - 1 == Rational(-1, 2)));
    CHECK((1 - Rational(-1, 2) == Rational(3, 2)));
    CHECK((Rational(-1, 2) - 1 == Rational(-3, 2)));
    CHECK((-1 - Rational(1, 2) == Rational(-3, 2)));
    CHECK((Rational(1, 4) - Rational(1, 2) == Rational(-1, 4)));
    CHECK((Rational(1, 4) * Rational(2, 3) == Rational(1, 6)));
    CHECK((Rational(1, 4) * 4 == 1));
    CHECK((4 * Rational(1, 4) == 1));
    CHECK((Rational(1, 4) * (-4) == -1));
    CHECK((Rational(1, 4) * Rational(-2, 3) == Rational(-1, 6)));
    CHECK((Rational(1, 4) / Rational(3, 2) == Rational(1, 6)));
    CHECK((Rational(1, 4) / 2 == Rational(1, 8)));
    CHECK((2 / Rational(1, 4) == 8));
    CHECK((Rational(1, 4) / Rational(-3, 2) == Rational(-1, 6)));
    CHECK((+Rational(1, 2) == Rational(1, 2)));
    CHECK((-Rational(1, 2) == Rational(-1, 2)));
    CHECK_THROWS((Rational(1, 2) / Rational(0, 1)));
    CHECK_THROWS((Rational(1, 2) / 0));
    CHECK_THROWS((Rational(1, 2) / Rational(1, 0)));
}

TEST_CASE("[rational] - comparison") {
    CHECK((Rational(2, 5) > Rational(3, 8)));
    CHECK((Rational(7, 5) > 1));
    CHECK((2 > Rational(7, 5)));
    CHECK((Rational(2, 5) < Rational(3, 2)));
    CHECK((Rational(2, -5) >= -Rational(3, 2)));
    CHECK((-Rational(2, 5) < Rational(2, 10)));
    CHECK((Rational(2, 5) < 2));
    CHECK((1 < Rational(7, 5)));
    CHECK((Rational(2, 5) >= Rational(3, 8)));
    CHECK((Rational(2, 5) >= Rational(2, 5)));
    CHECK((Rational(5, 5) >= 1));
    CHECK((2 >= Rational(2, 5)));
    CHECK((1 <= Rational(7, 5)));
    CHECK((1 <= Rational(5, 5)));
    CHECK((1 >= Rational(5, 5)));
    CHECK((Rational(2, 5) <= Rational(3, 2)));
    CHECK((Rational(2, 5) <= Rational(2, 5)));
    CHECK((Rational(10, 5) <= 2));
}

TEST_CASE("[rational] - input") {
    std::vector<std::string> right{"1/5 ", "2/22", "   1/8      ", "-10/2200 ", "11/1 "};
    std::vector<Rational> ans{Rational(1, 5), Rational(1, 11), Rational(1, 8), Rational(-1, 220), Rational(11, 1)};
    std::vector<std::string> wrong{"1/-2", "1//6 ", "1   /7 ", "1/   9 ", "1/0", "1/0 ", "1.1/5.5 ", "d2fv/wwsa1 ", "11/2s ", "11/s3 ", "11/3s3 ", "1d1/4 ", "1d/88 ", "d2/33 ", "5\t/8", "5/\t18", "5\t/\t18", "5/- 18", "5\n/18", "5/-0 ",  "5\\18 ", "-5/-18 ", "-5/0 ", "0/0 ", "abc ", "5 ", "5 /18 ", "5/ 18 ", "5 / 18 ", "5/ "};

    for (int i = 0; i < right.size(); i++) {
        std::stringstream strm(right[i]);
        Rational z;
        strm >> z;
        CHECK(z == ans[i]);
        CHECK((((strm.good()) || (strm.eof())) && (strm.bad() == false)));
    }
    for (int i = 0; i < wrong.size(); i++) {
        std::stringstream strm(wrong[i]);
        Rational z;
        strm >> z;
        CHECK(z == Rational());
        CHECK(strm.fail() == true);
    }
}