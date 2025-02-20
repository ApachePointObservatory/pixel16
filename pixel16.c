#include "Python.h"


static void 
do_uflip(unsigned short *usdata, int cnt)
{
  while (cnt > 0) {
    usdata[--cnt] ^= 0x8000;
  }
}

static void 
do_byteswap(unsigned short *usdata, int cnt)
{
  unsigned char t;

  while (cnt-- > 0) {
    unsigned char *cp = (unsigned char *)&(usdata[cnt]);

    t = *cp;
    *cp = *(cp+1);
    *(cp+1) = t;
  }
}

static PyObject *
uflip(PyObject *self, PyObject *args)
{
  PyObject *so;
  char *p;
  int len, ret;

  if (!PyArg_ParseTuple(args, "S", &so))
    return NULL;

  ret = PyString_AsStringAndSize(so, &p, &len);
  if (len % 2 == 1) {
    PyErr_Format(PyExc_TypeError, "array must contain an even number of bytes");
    return NULL;
  }

  do_uflip((unsigned short *)p, len/2);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *
byteswap(PyObject *self, PyObject *args)
{
  PyObject *so;
  char *p;
  int len, ret;

  if (!PyArg_ParseTuple(args, "S", &so))
    return NULL;

  ret = PyString_AsStringAndSize(so, &p, &len);
  if (len % 2 == 1) {
    PyErr_Format(PyExc_TypeError, "array must contain an even number of bytes");
    return NULL;
  }

  do_byteswap((unsigned short *)p, len/2);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef Pixel16Methods[] = 
  {
    { "uflip", uflip, METH_VARARGS, "flip the sign bit of an array of short integers." },
    { "byteswap", byteswap, METH_VARARGS, "swap the bytes of an array of short integers." },
    { NULL, NULL, 0, NULL }
  };

void initpixel16(void)
{
  (void)Py_InitModule("pixel16", Pixel16Methods);
}


