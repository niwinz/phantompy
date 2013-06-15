#!/usr/bin/env python
# -*- coding: utf-8 -*-

from distutils.core import setup
from distutils.spawn import find_executable
import distutils.command.build

import subprocess
import shutil
import shlex
import os.path

from os.path import join
import glob


class build(distutils.command.build.build):
    def run(self):
        result = distutils.command.build.build.run(self)
        cwd = os.path.dirname(os.path.abspath(__file__))
        new_module_dir = join(cwd, 'build', 'lib', 'phantompy')

        self._compile_phantompy(cwd)

        for filename in glob.glob(os.path.join(cwd, 'build', '_phantompy*')):
            if os.path.isfile(filename) and not os.path.islink(filename):
                shutil.copy(filename, os.path.join(new_module_dir, '_phantompy.so'))

        return result

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
    version = "0.9",
    description = "Headless WebKit engine for python build on top of Qt5 and Webkit",
    long_description = "",
    keywords = 'webkit, headless, qt, engine',
    author = 'Andrey Antukh',
    author_email = 'niwi@niwi.be',
    url = 'https://github.com/niwibe/phantompy',
    license = 'BSD',
    zip_safe = False,
    packages = [
        "phantompy",
    ],
    cmdclass={
        'build': build,
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
