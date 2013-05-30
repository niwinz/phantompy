#!/usr/bin/env python
# -*- coding: utf-8 -*-

from distutils.core import setup, Extension
from distutils.command.build import build
from distutils.command.build_ext import build_ext
from distutils.command.install_lib import install_lib

from distutils import log
from distutils.spawn import find_executable

import subprocess
import shutil
import shlex
import os.path

from os.path import join
import glob

class _install_lib(install_lib):
    build_directory =  "build"
    current_path = os.path.dirname(os.path.abspath(__file__))

    def install(self):
        super(_install_lib, self).install()

        #import pdb; pdb.set_trace()
        #shutil.copy(join(self.current_path, self.build_dir, "_phantompy.so"),
        #                join(self.install_dir, "_phantompy.so"))



class _build_ext(build):
    def run(self):
        cwd = os.path.dirname(os.path.abspath(__file__))
        #new_module_dir = os.path.join(cwd, 'build', 'lib', 'phantompy')

        self._compile_phantompy(cwd)
        for filename in glob.glob(os.path.join(cwd, 'build', '_phantompy*')):
            if os.path.isfile(filename) and not os.path.islink(filename):
                shutil.move(filename, os.path.join(cwd, self.build_lib, "phantompy", '_phantompy.so'))

    def _compile_phantompy(self, cwd):
        retval = subprocess.call(shlex.split('cmake ..'),
                                 cwd=os.path.join(cwd, 'build'))
        if retval:
            raise Exception("CMake Error!")

        retval = subprocess.call(shlex.split('make'),
                                 cwd=os.path.join(cwd, 'build'))

        if retval:
            raise Exception("CMake Error!")


setup(
    name = 'phantompy',
    version = "0.2",
    description = "Headless WebKit engine for python build on top of Qt5 and Webkit",
    long_description = "",
    keywords = 'webkit, headless, qt, engine',
    author = 'Andrey Antukh',
    author_email = 'niwi@niwi.be',
    url = 'https://github.com/niwibe/phantompy',
    license = 'BSD',
    zip_safe = False,
    #ext_modules=[Extension('_phantompy', [], optional=True)],
    packages = [
        "phantompy",
    ],
    cmdclass={
        'build': _build_ext,
        'install_lib': _install_lib,
    },
    classifiers = [
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: BSD License',
        'Operating System :: OS Independent',
        'Programming Language :: Python',
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.2',
        'Programming Language :: Python :: 3.3',
        'Topic :: Internet :: WWW/HTTP',
    ]
)
