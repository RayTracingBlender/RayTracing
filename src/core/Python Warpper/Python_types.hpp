#include<string>
#include "../Shape.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>


#ifndef PYTHONTYPES_H
#define PYTHONTYPES_H

namespace py = pybind11;

namespace JPC {
	class Triangle_geo {
	private:
		std::string name;
		rt::Shape shape;
	public:
		Triangle_geo(std::string Name, py::array_t<float> &transform, py::array_t<int> &Quad_Ind,int &nQuads, int &nverts, py::array_t<float> &P, py::array_t<float> &N) {
			//transfrom, QuadesIndices, nverts, P, N
			name = Name;
			shape=add_Triangle(transform, Quad_Ind, nQuads, nverts, P, N);
		}
		rt::Shape add_Triangle(py::array_t<float> &transform, py::array_t<int> &Quad_Ind, int &nQuads,
			int &nverts, py::array_t<float> &P, py::array_t<float> &N);
		rt::Shape get_shape() {
			return shape;
		}
		std::string repr() {
			return name;
		}
	};

	class Light {

	};
}
#endif