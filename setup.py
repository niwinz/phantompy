#!/usr/bin/env python
# -*- coding: utf-8 -*-

from setuptools import setup, find_packages

setup(
    name = 'phantompy',
    version = "0.1",
    description = "Headless WebKit engine for python build on top of Qt5 and Webkit",
    long_description = "",
    keywords = 'webkit, headless, qt, engine',
    author = 'Andrey Antukh',
    author_email = 'niwi@niwi.be',
    url = 'https://github.com/niwibe/phantompy',
    license = 'BSD',
    include_package_data = True,
    packages = find_packages(),
    install_requires=[
        "distribute"
    ],
    classifiers = [
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: BSD License',
        'Operating System :: OS Independent',
        'Programming Language :: Python',
        #'Programming Language :: Python :: 2',
        #'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.2',
        'Programming Language :: Python :: 3.3',
        'Topic :: Internet :: WWW/HTTP',
    ]
)
