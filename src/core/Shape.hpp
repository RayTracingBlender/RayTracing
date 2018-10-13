#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace rt {
	class Shape {
	public:
		Shape() {
			printf("Shape wurde erschafft");
		}

	};
}