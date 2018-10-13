#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <string>
#include <iostream>
#include <typeinfo>
#include "Python_types.hpp"

namespace py = pybind11;


void size(py::array_t<int> arr) {
	py::buffer_info info = arr.request();
	int d = info.ndim;
	if (d > 1) {
		printf("Falsche Dimension");
	}
	int size=info.shape[0];
	int * buffer = (int *)info.ptr;
	std::string el;
	for (int idx = 0; idx < size; idx++) {
		//el = std::to_string(buffer[idx]);
		py::print(buffer[idx]);
		//printf(el.c_str());
	}
	


		
};

struct scene {
private:
	std::string obj_name = "";
public:
	scene(std::string name) {
		obj_name = name;
	}
	std::string get_name() {
		return obj_name;
	}
	std::string name_of_other_class(scene obj) {
		return obj.get_name();
	}
};


PYBIND11_MODULE(_JPCEngine, m) {
	m.doc() = "pybind11 example plugin"; // optional module docstring

	m.def("size", &size, "ndim of numpy array");
	py::class_<scene>(m, "pyScene")
		.def(py::init<std::string>())
		.def("name_of_other_class", &scene::name_of_other_class);
	py::class_<JPC::Triangle_geo>(m, "Triangle_geo")
		.def(py::init< std::string &, py::array_t<float> &, py::array_t<int>&, int&, int&, py::array_t<float>&, py::array_t<float>&>())
		.def("__repr__", &JPC::Triangle_geo::repr)
		;
}