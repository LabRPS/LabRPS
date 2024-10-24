#! python
# -*- coding: utf-8 -*-
# (c) 2013 Werner Mayer LGPL
#
# Utility to search for source, header and Python files with a missing license text

import codecs, os

ext=[".cpp", ".cxx", ".cc", ".c", ".hpp", ".hxx", ".hh", ".h", ".inl", ".inc", ".py"]
flt=['__init__.py', '_rc.py',
     'CxxDebug.hxx',
     'IndirectPythonInterface.hxx',
     ('thumbs%sIExtractImage.h')%(os.path.sep),
    #('src%sTools')%(os.path.sep),
    ('src%sTools%sembedded')%(os.path.sep,os.path.sep),
    ('App%skdl_cp')%(os.path.sep),
    ('3rdParty%satlas')%(os.path.sep),
    ('Mod%sGDML')%(os.path.sep),
    ('boost%snumeric%sbindings')%(os.path.sep,os.path.sep),
    ('salomesmesh%sinc')%(os.path.sep),
    ('App%sCore%stritritest.h')%(os.path.sep,os.path.sep)
    ]
    # A note to tritritest.h
    # tritritest.h has no licensing information, but Tomas Moller replied
    # the following, when asked about it:
    #
    # The code is free to use for anyone and any projects, but I give no
    # warranties.
    #
    # See: http://anonscm.debian.org/gitweb/?p=debian-science/packages/labrps.git;a=blob;f=debian/copyright
lic=['LGPL',
     'GNU Library',
     'GNU Lesser',
     'Permission to copy, use, modify',
     'Permission to use, copy, modify',
     'Distributed under the Boost Software License',
     'Redistribution  and  use  in  source  and  binary  forms',
     'Redistribution and use in source and binary forms',
     'it under the same terms as Python itself',
     'As a special exception, you may create a larger work that contains',
     'Permission is hereby granted, free of charge, to any person obtaining',
     'Permission is granted to anyone to use this software',
     'This file was automatically generated by SWIG'
    ]

def startProcessing():
    fn = os.path.realpath(__file__)
    # get path of parent directory
    fn = os.path.dirname(fn)
    fn = os.path.dirname(fn)
    global ext
    global flt
    traverse(fn, ext, flt)

def traverse(path, ext, flt):
    for r,d,f in os.walk(path):
        for i in f:
            fn = os.path.join(r,i)
            # filter out some file names
            stop = False
            for j in flt:
                if fn.find(j) >= 0:
                    stop=True
                    break
            if stop:
                continue
            bn = os.path.basename(fn).lower()
            for j in ext:
                if bn.endswith(j):
                    parsefile(fn)
                    break

def parsefile(fn):
    data = codecs.open(fn,'r','utf-8')
    try:
        lines = data.readlines()
        data.close()

        global lic
        for i in lines:
            for j in lic:
                if i.find(j) >= 0:
                    return

        print ("Missing license text in file %s") % (fn)
    except Exception:
        pass

if __name__ == "__main__":
    startProcessing()
