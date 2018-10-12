#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
namespace py = pybind11;


int size(py::array_t<int> arr) {
	py::buffer_info info = arr.request();
	int d = info.ndim;
	return d;
	};


PYBIND11_MODULE(_JPCEngine, m) {
	m.doc() = "pybind11 example plugin"; // optional module docstring

	m.def("size", &size, "ndim of numpy array");
}