#include "include.h"
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
