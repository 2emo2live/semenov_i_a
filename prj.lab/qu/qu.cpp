#include <iostream>
#include <cmath>

class Vec2d {
public:
	Vec2d() = default;
	~Vec2d() = default;
	Vec2d operator=(Vec2d rhs);
	Vec2d(double x0, double y0, double x1, double y1);
	double len();
	double x() { return (x1 - x0); };
	double y() { return (y1 - y0); };
/*	double x0() { return x0; };
	double y0() { return y0; };
	double x1() { return x1; };
	double y1() { return y1; };*/

private:
	double x0 = 0;
	double x1 = 0;
	double y0 = 0;
	double y1 = 0;
};

/*Vec2d Vec2d::operator=(Vec2d)
{
	x0 = rhs.x0();
	x1 = rhs.x1();
	y0 = rhs.y0();
	y1 = rhs.y1();
}*/


double scal(Vec2d& v1, Vec2d& v2) {
	return (v1.x() * v2.x() + v1.y() * v2.y());
};

double cos(Vec2d& v1, Vec2d& v2) {
	if ((v1.len() == 0) || (v2.len() == 0)) {
		return 0;
	}
	return (scal(v1, v2) / (v1.len() * v2.len()));
};

Vec2d::Vec2d(double x0, double y0, double x1, double y1)
	: x0(x0), y0(y0), x1(x1), y1(y1)
{
}

double Vec2d::len() {
	return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
}


int main() {
	Vec2d v1 = Vec2d(0, 0, 1, 1);
	std::cout << v1.len() << std::endl;
	Vec2d v2 = Vec2d();
	std::cout << v2.len() << std::endl;
	v2 = Vec2d(2, 2, -1, -1);
	std::cout << v2.len() << std::endl;
	std::cout << scal(v1, v2) << std::endl;
	std::cout << cos(v1, v2) << std::endl;
	v1 = Vec2d();
	std::cout << cos(v1, v2) << std::endl;
	return 0;
}