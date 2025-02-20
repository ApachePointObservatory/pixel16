from distutils.core import setup, Extension

setup(name="pixel16", version="1.0",
      ext_modules=[Extension("pixel16", ["pixel16.c"])])
