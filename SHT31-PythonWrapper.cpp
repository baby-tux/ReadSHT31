#include <Python.h>
#include "SHT31.hpp"


static PyObject * readValues(PyObject * self, PyObject * args)
{
  int busId;

  // parse arguments
  if (!PyArg_ParseTuple(args, "i", &busId)) {
    return NULL;
  }

  // open bus and run the actual function
  lr::SHT31 shtAccess(lr::SHT31::Address0, busId, false);
  if (hasError(shtAccess.openBus())) {
    return NULL;
  }
  const auto readResult = shtAccess.readValues();
  if (hasError(readResult)) {
    return NULL;
  }
  // Get the values
  const auto [temperature, humidity] = readResult.getValue();

  // build the resulting tuble into a Python object.
  PyObject * ret = Py_BuildValue("dd", temperature, humidity);
  
  // Close the bus.
  shtAccess.closeBus();

  return ret;
}

static PyObject * readStatus(PyObject * self, PyObject * args)
{
  int busId;

  // parse arguments
  if (!PyArg_ParseTuple(args, "i", &busId)) {
    return NULL;
  }

  // open bus and run the actual function
  lr::SHT31 shtAccess(lr::SHT31::Address0, busId, false);
  if (hasError(shtAccess.openBus())) {
    return NULL;
  }
  const auto readResult = shtAccess.readStatus();
  if (hasError(readResult)) {
    return NULL;
  }
  // Get the value
  const auto status = readResult.getValue();

  // build the resulting tuble into a Python object.
  PyObject * ret = Py_BuildValue("i", status);
  
  // Close the bus.
  shtAccess.closeBus();

  return ret;
}

static PyObject * controlHeater(PyObject * self, PyObject * args)
{
  int busId, enabled;

  // parse arguments
  if (!PyArg_ParseTuple(args, "ip", &busId, &enabled)) {
    return NULL;
  }

  // open bus and run the actual function
  lr::SHT31 shtAccess(lr::SHT31::Address0, busId, false);
  if (hasError(shtAccess.openBus())) {
    return NULL;
  }
  const auto readResult = shtAccess.controlHeater(enabled);
  if (hasError(readResult)) {
    return NULL;
  }
 
  // Close the bus.
  shtAccess.closeBus();

  Py_RETURN_NONE;
}

static PyObject * getSerialNumber(PyObject * self, PyObject * args)
{
  int busId;

  // parse arguments
  if (!PyArg_ParseTuple(args, "i", &busId)) {
    return NULL;
  }

  // open bus and run the actual function
  lr::SHT31 shtAccess(lr::SHT31::Address0, busId, false);
  if (hasError(shtAccess.openBus())) {
    return NULL;
  }
  const auto readResult = shtAccess.readSerialNumber();
  if (hasError(readResult)) {
    return NULL;
  }
  // Get the value
  const auto serial = readResult.getValue();

  // build the resulting tuble into a Python object.
  PyObject * ret = Py_BuildValue("i", serial);
  
  // Close the bus.
  shtAccess.closeBus();

  return ret;
}

static PyObject * softReset(PyObject * self, PyObject * args)
{
  int busId;

  // parse arguments
  if (!PyArg_ParseTuple(args, "i", &busId)) {
    return NULL;
  }

  // open bus and run the actual function
  lr::SHT31 shtAccess(lr::SHT31::Address0, busId, false);
  if (hasError(shtAccess.openBus())) {
    return NULL;
  }
  const auto readResult = shtAccess.softReset();
  if (hasError(readResult)) {
    return NULL;
  }
 
  // Close the bus.
  shtAccess.closeBus();

  Py_RETURN_NONE;
}

// Exported methods are collected in a table
PyMethodDef method_table[] = {
    {"read_values", (PyCFunction) readValues, METH_VARARGS, "Reads temperature/humidity values."},
    {"read_status", (PyCFunction) readStatus, METH_VARARGS, "Reads the sensor status."},
    {"control_heater", (PyCFunction) controlHeater, METH_VARARGS, "Enables or disables the heater."},
    {"reset", (PyCFunction) softReset, METH_VARARGS, "Resets the sensor."},
    {"get_serial_number", (PyCFunction) getSerialNumber, METH_VARARGS, "Gets the serial number."},
    {NULL, NULL, 0, NULL} // Sentinel value ending the table
};

// A struct contains the definition of a module
PyModuleDef sht31_module = {
    PyModuleDef_HEAD_INIT,
    "sht31", // Module name
    "A simple Python library to read a SHT31 sensor over the I2C bus",
    -1,   // Optional size of the module state memory
    method_table,
    NULL, // Optional slot definitions
    NULL, // Optional traversal function
    NULL, // Optional clear function
    NULL  // Optional module deallocation function
};

// The module init function
PyMODINIT_FUNC PyInit_sht31(void) {
    return PyModule_Create(&sht31_module);
}