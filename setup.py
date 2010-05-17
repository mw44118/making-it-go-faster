# vim: set expandtab ts=4 sw=4 filetype=python:

from distutils.core import setup, Extension

module = Extension('bogus', sources = ['bogus.c'])

setup(
    name='Bogus',
    version='1.0',
    ext_modules=[module])

