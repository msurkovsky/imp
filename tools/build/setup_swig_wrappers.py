#!/usr/bin/env python

""" Create the swig wrapper files from setup.i-in files.
"""

import os.path
import glob
import sys
import copy
import tools
from optparse import OptionParser

def write_module_cpp(m, contents):
    if m.name == 'kernel':
        contents.append("""%{
#include "IMP.h"
#include "IMP/kernel_config.h"
%}
""")
    else:
        contents.append("""%%{
#include "IMP/%(module)s.h"
#include "IMP/%(module)s/%(module)s_config.h"
%%}
""" % {"module": m.name})
    for macro in m.configured.swig_wrapper_includes:
        contents.append("""%%{
#include <%s>
%%}""" % (macro))


def write_module_swig(m, contents, skip_import=False):
    if m.name == 'kernel':
        contents.append("""%%include "IMP/%s_config.h" """ % m.name)
    else:
        contents.append("""%%include "IMP/%s/%s_config.h" """
                        % (m.name, m.name))
    for macro in m.configured.swig_includes:
        contents.append("%%include \"%s\"" % (macro))
    if not skip_import:
        contents.append("%%import \"IMP_%(module)s.i\"" % {"module": m.name})


def build_wrapper(module, finder, sorted, target):
    if not module.configured.ok:
        return
    contents = []
    swig_module_name = "IMP" if module.name == 'kernel' \
                             else "IMP." + module.name

    contents.append(
"""%%module(directors="1", allprotected="1", moduleimport="import $module") "%s"
%%feature("autodoc", 1);
// Warning 314: 'lambda' is a python keyword, renaming to '_lambda'
%%warnfilter(321,302,314);

%%{
#include <boost/version.hpp>
#if BOOST_VERSION > 103600
#if BOOST_VERSION > 103800
#include <boost/exception/all.hpp>
#else
#include <boost/exception.hpp>
#endif
#endif

#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#include <exception>

#ifdef __cplusplus
extern "C"
#endif

// suppress warning
SWIGEXPORT
#if PY_VERSION_HEX >= 0x03000000
PyObject*
#else
void
#endif
SWIG_init();
%%}
""" % swig_module_name)
        # some of the typemap code ends up before this is swig sees the
        # typemaps first
    all_deps = [x for x in finder.get_dependent_modules([module])
                if x != module]
    for m in reversed(all_deps):
        write_module_cpp(m, contents)

    write_module_cpp(module, contents)
    contents.append("""
%implicitconv;
%include "std_vector.i"
%include "std_string.i"
%include "std_pair.i"


%pythoncode %{
_value_types=[]
_object_types=[]
_raii_types=[]
_plural_types=[]
%}

%include "typemaps.i"

#ifdef NDEBUG
#error "The python wrappers must not be built with NDEBUG"
#endif

""")

    for m in reversed(all_deps):
        write_module_swig(m, contents)

    write_module_swig(module, contents, True)

    contents.append("%%include \"IMP_%s.impl.i\"" % module.name)
    #contents.append(open(os.path.join(module_path, "pyext", "swig.i-in"), "r").read())

    contents.append("""
namespace IMP { %s
const std::string get_module_version();
std::string get_example_path(std::string fname);
std::string get_data_path(std::string fname);
%s }
""" % ('' if module.name == 'kernel' else 'namespace %s {' % module.name,
       '' if module.name == 'kernel' else '}'))
    contents.append("""%pythoncode %{
from . import _version_check
_version_check.check_version(get_module_version())
__version__ = get_module_version()
%}
""")
    g = tools.SWIGFileGenerator()
    g.write(target, "\n".join(contents))


parser = OptionParser()
parser.add_option("--build_dir", help="IMP build directory", default=None)
parser.add_option("-d", "--datapath",
                  dest="datapath", default="", help="Extra data path.")
parser.add_option("-s", "--source",
                  dest="source", help="Where to find IMP source.")
parser.add_option("-m", "--module",
                  dest="module", default="", help="Only run on one module.")


def main():
    (options, args) = parser.parse_args()
    sorted_order = tools.get_sorted_order()

    if options.module != "":
        mf = tools.ModulesFinder(source_dir=options.source,
                                 external_dir=options.build_dir,
                                 module_name=options.module)
        module = mf[options.module]
        build_wrapper(module, mf, sorted_order,
                      os.path.join("swig", "IMP_" + module.name + ".i"))

if __name__ == '__main__':
    main()
