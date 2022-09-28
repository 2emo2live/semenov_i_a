#include <complex/complex.h>
#include <iostream>
#include <sstream>

int main() {
	int complete = 0;
	try {
		if (Complex() == Complex(0, 0))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(3) == Complex(3, 0))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(2.1) == Complex(2.1, 0))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(2) == Complex(2 + std::numeric_limits<double>::epsilon(), 0))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(2) == Complex(2 + 2*std::numeric_limits<double>::epsilon(), 0))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(2) != Complex(2 + 3*std::numeric_limits<double>::epsilon(), 0))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(2) == Complex(2 - std::numeric_limits<double>::epsilon(), 0))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(2) == Complex(2 - 2 * std::numeric_limits<double>::epsilon(), 0))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(2) != Complex(2 - 3 * std::numeric_limits<double>::epsilon(), 0))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(1, 2) == Complex(1, 2 + std::numeric_limits<double>::epsilon()))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(1, 2) == Complex(1, 2 + 2 * std::numeric_limits<double>::epsilon()))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(1, 2) != Complex(1, 2 + 3 * std::numeric_limits<double>::epsilon()))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(1, 2) == Complex(1, 2 - std::numeric_limits<double>::epsilon()))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(1, 2) == Complex(1, 2 - 2 * std::numeric_limits<double>::epsilon()))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(1, 2) != Complex(1, 2 - 3 * std::numeric_limits<double>::epsilon()))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(1, 2) != Complex(1, 1))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(1, 2) != Complex())
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		std::cout << "All " << complete << " tests of Complex ctor completed successfully" << std::endl;
	} catch (...){
		std::cout << "Wrong answer on test " << complete + 1 << " in Complex ctor" << std::endl;
	}
	complete = 0;
	try {
		if (Complex(2, 3) + Complex(1, -5) == Complex(3, -2))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(2, 3) + Complex(1, -5) != Complex(3, -1.9))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(2.3, 3) - Complex(0.1, -5) == Complex(2.2, 8))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(2, 3) * Complex(1, -5) == Complex(17, -7))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(2, 3) / Complex(1, -5) == Complex(-0.5, 0.5))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(2, 3) / Complex(7, -9) == Complex(-0.1, 0.3))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(2, 3) / 2 == Complex(1, 1.5))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (1 / Complex(1, -1) == Complex(0.5, 0.5))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (+Complex(2, 3) == Complex(2, 3))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (-Complex(2, 3) == Complex(-2, -3))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		if (Complex(5.1, 3.3) + Complex(1, 3.4) == Complex(5.1 + 1, 3.3 + 3.4))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		std::cout << "All " << complete << " tests of Complex ariphmetic completed successfully" << std::endl;
	}
	catch (...) {
		std::cout << "Wrong answer on test " << complete + 1 << " in Complex ariphmetic" << std::endl;
	}
	complete = 0;
	try {
		std::stringstream strm;
		strm << "{1,5}";
		Complex z;
		strm >> z;
		if (z == Complex(1, 5))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		strm.str("");
		strm << "{1,-5}";
		strm >> z;
		if (z == Complex(1, -5))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		strm.str("");
		strm << "{1.1,5}";
		strm >> z;
		if (z == Complex(1.1, 5))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		strm.str("");
		strm << "{1;5}";
		strm >> z;
		if (strm.fail())
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		strm.clear();
		strm.str("");
		strm << "{-1,5}";
		strm >> z;
		if (z == Complex(-1, 5))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		strm.str("");
		strm << "(1,5)";
		strm >> z;
		if (strm.fail())
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		std::cout << "All " << complete << " tests of Complex input completed successfully" << std::endl;
	}
	catch (...) {
		std::cout << "Wrong answer on test " << complete + 1 << " in Complex input" << std::endl;
	}
	complete = 0;
	try {
		std::stringstream strm;
		strm << Complex();
		Complex z;
		strm >> z;
		if ((z == Complex(0, 0)) && (strm.good()))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		strm.str("");
		z = Complex(1, -1);
		strm << z;
		Complex zz;
		strm >> zz;
		if ((zz == Complex(1, -1)) && (strm.good()))
			complete += 1;
		else
			throw std::logic_error("Wrong answer");
		std::cout << "All " << complete << " tests of Complex output completed successfully" << std::endl;
	}
	catch (...) {
		std::cout << "Wrong answer on test " << complete + 1 << " in Complex output" << std::endl;
	}
}