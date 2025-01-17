/*
*
* Template Numerical Toolkit (TNT)
*
* Mathematical and Computational Sciences Division
* National Institute of Technology,
* Gaithersburg, MD USA
*
*
* This software was developed at the National Institute of Standards and
* Technology (NIST) by employees of the Federal Government in the course
* of their official duties. Pursuant to title 17 Section 105 of the
* United States Code, this software is not subject to copyright protection
* and is in the public domain. NIST assumes no responsibility whatsoever for
* its use by other parties, and makes no guarantees, expressed or implied,
* about its quality, reliability, or any other characteristic.
*
*/

#ifndef IMPALGEBRA_TNT_SUBSCRIPT_H
#define IMPALGEBRA_TNT_SUBSCRIPT_H

//---------------------------------------------------------------------
// This definition describes the default TNT data type used for
// indexing into TNT matrices and vectors.  The data type should
// be wide enough to index into large arrays.  It defaults to an
// "int", but can be overriden at compile time redefining TNT_SUBSCRIPT_TYPE,
// e.g.
//
//      c++ -DTNT_SUBSCRIPT_TYPE='unsigned int'  ...
//
//---------------------------------------------------------------------
//

#ifndef IMPALGEBRA_TNT_SUBSCRIPT_TYPE
#define IMPALGEBRA_TNT_SUBSCRIPT_TYPE int
#endif

IMPALGEBRA_BEGIN_INTERNAL_NAMESPACE
namespace TNT {
typedef IMPALGEBRA_TNT_SUBSCRIPT_TYPE Subscript;
} /* namespace TNT */
IMPALGEBRA_END_INTERNAL_NAMESPACE

// () indexing in TNT means 1-offset, i.e. x(1) and A(1,1) are the
// first elements.  This offset is left as a macro for future
// purposes, but should not be changed in the current release.
//
//
#define IMPALGEBRA_TNT_BASE_OFFSET (1)

#endif /* IMPALGEBRA_TNT_SUBSCRIPT_H */
