#include "include.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <math.h>
#include <ndarrayobject.h>
#include <string>
#include <sstream>


extern "C" {
	static PyObject * 
			render(PyObject *, PyObject *args ) {
		int a = 0;
		return PyFloat_FromDouble(0);
	};

	static PyObject * 
			update(PyObject *, PyObject *args) {
		int a = 0;
		return PyFloat_FromDouble(0);
	};

	static PyObject * 
			create(PyObject *, PyObject *args) {
		int a = 0;
		return PyFloat_FromDouble(0);
	};

	static PyObject * 
			JPC_free(PyObject *, PyObject *args) {
		int a = 0;
		return PyFloat_FromDouble(0);
	};
	static PyObject * Mesh_add_triangle(PyObject *self, PyObject *args) {
		printf("Funktions start\n");
		PyArrayObject *arr;
		
		if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &arr)) {
			printf("hier ist irgendwas falsch mit den argumenten");
			return NULL;
		}


		int size = PyArray_SIZE(arr);
		std::cout <<"Size: "<< size <<"\n";

		Py_INCREF(Py_None);
		printf("So gut wie am Ende");
		return Py_None;
	};
	static PyObject *
		example_wrapper(PyObject *dummy, PyObject *args)
	{
		PyObject *arg1 = NULL, *arg2 = NULL, *out = NULL;
		PyObject *arr1 = NULL, *arr2 = NULL, *oarr = NULL;

		if (!PyArg_ParseTuple(args, "OOO!", &arg1, &arg2,
			&PyArray_Type, &out)) return NULL;

		arr1 = PyArray_FROM_OTF(arg1, NPY_DOUBLE, NPY_IN_ARRAY);
		if (arr1 == NULL) return NULL;
		arr2 = PyArray_FROM_OTF(arg2, NPY_DOUBLE, NPY_IN_ARRAY);
		if (arr2 == NULL) goto fail;
		oarr = PyArray_FROM_OTF(out, NPY_DOUBLE, NPY_INOUT_ARRAY);
		if (oarr == NULL) goto fail;

		/* code that makes use of arguments */
		/* You will probably need at least
		   nd = PyArray_NDIM(<..>)    -- number of dimensions
		   dims = PyArray_DIMS(<..>)  -- npy_intp array of length nd
										 showing length in each dim.
		   dptr = (double *)PyArray_DATA(<..>) -- pointer to data.

		   If an error occurs goto fail.
		 */

		Py_DECREF(arr1);
		Py_DECREF(arr2);
		Py_DECREF(oarr);
		Py_INCREF(Py_None);
		return Py_None;

	fail:
		Py_XDECREF(arr1);
		Py_XDECREF(arr2);
		printf("flasche lol");
		//PyArray_XDECREF_ERR(oarr);
		return NULL;
	}

}

PyMethodDef JPCEngineMethods[] =
{
	{ "render",  render, METH_VARARGS,
	"rendert das Bild" },
	{ "update",  update, METH_VARARGS,
	"updatet die Daten vorm Render." },
	{ "create",  create, METH_VARARGS,
	"erzeugt die Engine" },
	{ "free",  JPC_free, METH_VARARGS,
	"beendet die Engine" },
	{"mesh_add_triangle",Mesh_add_triangle, METH_VARARGS, 
	{"fuegt ein Mesh aus Dreiecken hinzu"}},
	{"test",example_wrapper,METH_VARARGS,{"test"}},

	{NULL,0,NULL,NULL}

};

static struct PyModuleDef JPCEnginemodule = {
	PyModuleDef_HEAD_INIT,
	"_JPCEngine",   /* name of module */
	"Die C++ JPCEngine", /* module documentation, may be NULL */
	-1,       /* size of per-interpreter state of the module,
			  or -1 if the module keeps state in global variables. */
	JPCEngineMethods
};

PyMODINIT_FUNC
PyInit__JPCEngine(void)
{
	return PyModule_Create(&JPCEnginemodule);
}
