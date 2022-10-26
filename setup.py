from setuptools import setup, Extension

setup(name = "sht31",
      version = "0.1",
      ext_modules = [Extension("sht31", ["I2CBus.cpp", "SHT31.cpp", "SHT31-PythonWrapper.cpp"])]
      );
