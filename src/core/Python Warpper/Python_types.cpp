#include "Python_types.hpp"
#include "../transform.hpp"
#include "../geometry.hpp"
#include <vector>

namespace py = pybind11;
namespace JPC {
	rt::Shape Triangle_geo::add_Triangle(py::array_t<float> &transform, py::array_t<int> &Quad_Ind,int &nQuads, int &nverts, py::array_t<float> &P, py::array_t<float> &N) {
		//transfrom, QuadesIndices, nverts, P, N
		
		py::print("add_triangle");
		py::buffer_info trans = transform.request();
		float *t = static_cast<float*>(trans.ptr);
		rt::Matrix4x4 transmat=rt::Matrix4x4(t[0], t[1], t[2], t[3], 
											t[4], t[5], t[6], t[7],
											t[8], t[9], t[10], t[11],
											t[12], t[13],t[14],t[15]);
		rt::Transform retTrans=rt::Transform(transmat);
		


		//Quad Ind
		py::buffer_info bQuad_Ind = Quad_Ind.request();

		int* qind = static_cast<int*>(bQuad_Ind.ptr);
		
		//End Variable
		std::vector<int> Tris_ind;
		int nTirs = 0;

		for (int i = 0; i < bQuad_Ind.size; i += 4) {
			//wenn es sich um ein Dreieck handelt
			if (qind[i + 3] == 0) {
				//Es handelt sich um ein Dreieck
				nTirs++;
				Tris_ind.push_back(qind[i]);
				Tris_ind.push_back(qind[i + 1]);
				Tris_ind.push_back(qind[i + 2]);

			}
			else
			{
				nTirs += 2;
				//erstes Dreieck
				Tris_ind.push_back(qind[i]);
				Tris_ind.push_back(qind[i + 1]);
				Tris_ind.push_back(qind[i + 2]);

				//zweites Dreieck
				Tris_ind.push_back(qind[i + 1]);
				Tris_ind.push_back(qind[i + 2]);
				Tris_ind.push_back(qind[i + 3]);
			}
		}

		//Vertices Positions

		py::buffer_info bVerts = P.request();

		float* verts = static_cast<float*>(bVerts.ptr);

		//finale Output Position
		std::vector<rt::Point3<float>> P_array;


		for (int i = 0; i < bVerts.size; i += 3) {
			P_array.push_back(rt::Point3<float>( verts[i], verts[i+1], verts[i+2])
			);

		}


		//Normals
		py::buffer_info bNormals = N.request();

		float* norms = static_cast<float*>(bNormals.ptr);

		std::vector<rt::Vector3<float>> normals;
		for (int i = 0; i < bNormals.size; i += 3) {
			normals.push_back(rt::Vector3<float>(norms[i], norms[i + 1], norms[i + 2]));
		}
		py::print(nTirs);

		return rt::Shape();


	}
}