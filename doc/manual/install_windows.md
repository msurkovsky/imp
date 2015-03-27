Building from source code on Windows {#install_windows}
====================================

We build and test %IMP on
Windows, built with the Microsoft Visual Studio compilers (we use Visual Studio
Express 2010 SP1 for 32-bit Windows, and VS Express 2012 for 64-bit).
One complication is that different packages are compiled
with different versions of Visual Studio, and mixing the different runtimes
(msvc*.dll) can cause odd behavior; therefore, we recommend building most
of the dependencies from source code using the same version of Visual Studio
that you're going to use to build IMP. The basic procedure is as follows:

  - Install Microsoft Visual Studio Express (it is free, but registration with
    Microsoft is required).
  - Get and install [cmake](http://www.cmake.org).
  - Get [Python 2](http://www.python.org) (not Python 3)
    (make sure you get the
    32-bit version if you're going to build IMP for 32-bit Windows).
  - Get and install the
    [zlib package](http://gnuwin32.sourceforge.net/packages/zlib.htm)
    (both the "complete package, except sources" and the "sources" installers).
     - The package without sources can be installed anywhere; we chose the
       default location of `C:\Program Files\GnuWin32`. The sources, however,
       must be installed in a path that doesn't contain spaces (otherwise the
       Boost build will fail). We chose `C:\zlib`.
     - We found that the zconf.h header included with zlib erroneously includes
       unistd.h, which doesn't exist on Windows, so we commented out that line
       (in both packages).
  - Download the [Boost source code](http://www.boost.org)
    (we extracted it into `C:\Program Files\boost_1_53_0`), then
     - Open a Visual Studio Command Prompt, and cd into the directory where
       Boost was extracted
     - Run bootstrap.bat
     - You may need to help the compiler find the zlib header file with
       `set INCLUDE=C:\Program Files\GnuWin32\include`
     - Run `bjam link=shared runtime-link=shared -sNO_ZLIB=0 -sZLIB_SOURCE=C:\zlib\1.2.3\zlib-1.2.3`
  - Get and install [SWIG for Windows](http://www.swig.org)
  - Get the [HDF5 source code](http://www.hdfgroup.org)
     - Make a 'build' subdirectory, then run from a command prompt in
       that subdirectory something similar to
       `cmake.exe -G "Visual Studio 10" -DHDF5_ENABLE_SZIP_SUPPORT:BOOL=OFF -DHDF5_ENABLE_Z_LIB_SUPPORT:BOOL=ON -DHDF5_BUILD_HL_LIB:BOOL=ON -DZLIB_INCLUDE_DIR="C:\Program Files\GnuWin32\include" -DZLIB_LIBRARY="C:\Program Files\GnuWin32\lib\zlib.lib" -DBUILD_SHARED_LIBS:BOOL=ON ..`
     - Open the resulting HDF5 solution file in Visual Studio, change to
       Release configuration, then build the hdf5 project.
  - (Optional) [Build CGAL from source code](http://www.cgal.org/windows_installation.html).
  - (Optional) Download the
    [FFTW DLLs](http://www.fftw.org/install/windows.html) and follow the
    instructions at that website to make .lib import libraries needed for
    Visual Studio.
     - Copy `libfftw3-3.lib` to `fftw3.lib` to help cmake find it
  - (Optional) Get the
    [GSL source code](http://gnuwin32.sourceforge.net/packages/gsl.htm)
    and build it:
     - Open the libgsl project file in the `src\gsl\1.8\gsl-1.8\VC8`
       subdirectory
     - Build in Release-DLL configuration
     - Copy the generated `libgsl.dll` and `libgslcblas.dll` to a suitable
       location (we used `C:\Program Files\gsl-1.8\lib`)
     - Copy the corresponding .lib files, libgsl_dll.lib and libgslcblas_dll.lib
       (we recommend removing the _dll suffix and the lib prefix when you do
       this so that cmake has an easier time finding them, i.e. call them
       gsl.lib and gslcblas.lib).
  - (Optional) Get [numpy and scipy](http://www.scipy.org) to match your
    Python version.
  - (Optional) Get and install
    [libTAU](http://integrativemodeling.org/libTAU.html)
     - Copy `libTAU.lib` to `TAU.lib` to help cmake find it.
  - (Optional) Get the [OpenCV source code](http://opencv.org/)
    and build it by [following these instructions](http://docs.opencv.org/doc/tutorials/introduction/windows_install/windows_install.html)
     - Copy each `opencv_*.lib` to a similar file without the version extension
       (e.g. copy `opencv_ml244.lib` to `opencv_ml.lib`) to help cmake find it
  - Set PATH, INCLUDE, and/or LIB environment variables so that the compiler
    can find all of the dependencies. (We wrote a little batch file.)
  - Set up IMP by running something similar to

     `cmake <imp_source_directory> -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="/DBOOST_ALL_DYN_LINK /EHsc /D_HDF5USEDLL_ /DWIN32 /DGSL_DLL" -G "NMake Makefiles"`

  - Note: if building for 64-bit Windows, you may need to add `/bigobj` to `CMAKE_CXX_CFLAGS`.
  - Then use simply 'nmake' (instead of 'make', as on Linux or Mac) to
    build IMP. (cmake can also generate Visual Studio project files, but
    we recommend nmake.)
  - To use IMP or run tests, first run the setup_environment.bat file to set
    up the environment so all the programs and Python modules can be found.
    (This batch file needs to be run only once, not for each test.)