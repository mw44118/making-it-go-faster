#include <Python.h>

static PyObject *pr_isprime(PyObject *self, PyObject *args){
    int n, input;

    /* Set the required parameters for this function.  */
    if (!PyArg_ParseTuple(args, "i", &input))
      return NULL;

    if (input < 1) {
        return Py_BuildValue("i", 0);
    }

    n = input - 1;

    while (n > 1){
        if (input%n == 0) return Py_BuildValue("i", 0);;
        n--;
    }

    return Py_BuildValue("i", 1);
}

/* This is the method table */
static PyMethodDef PrMethods[] = {

    {"isprime", pr_isprime, METH_VARARGS, "Check if prime."},

    {NULL, NULL, 0, NULL} /* Sentinel */

};

PyMODINIT_FUNC
initbogus(void){
    (void) Py_InitModule("bogus", PrMethods);
}
