/**
 *  \file IMP/atom/Copy.h
 *  \brief A decorator for keeping track of copies of a molecule.
 *
 *  Copyright 2007-2019 IMP Inventors. All rights reserved.
 *
 */

#ifndef IMPATOM_COPY_H
#define IMPATOM_COPY_H

#include <IMP/atom/atom_config.h>
#include "../macros.h"

#include "Molecule.h"
#include <IMP/Decorator.h>
#include <vector>
#include <limits>

IMPATOM_BEGIN_NAMESPACE

//! A decorator for keeping track of copies of a molecule.
/** This decorator is for differentiating and keeping track
    of identity when there are multiple copies of
    molecule in the system. It should only be applied to
    Molecule particles.
 */
class IMPATOMEXPORT Copy : public Molecule {
  static void do_setup_particle(Model *m, ParticleIndex pi,
                                int number) {
    m->add_attribute(get_copy_index_key(), pi, number);
    if (!Molecule::get_is_setup(m, pi)) {
      Molecule::setup_particle(m, pi);
    }
  }

 public:
  static IntKey get_copy_index_key();

  IMP_DECORATOR_METHODS(Copy, Molecule);
  /** Create a decorator for the numberth copy. */
  IMP_DECORATOR_SETUP_1(Copy, Int, number);

  static bool get_is_setup(Model *m, ParticleIndex pi) {
    return m->get_has_attribute(get_copy_index_key(), pi);
  }

  int get_copy_index() const {
    return get_particle()->get_value(get_copy_index_key());
  }
};

IMP_DECORATORS(Copy, Copies, ParticlesTemp);

//! Walk up the hierarchy to find the current copy index.
/** \return the copy index, or -1 if there is none.
 */
IMPATOMEXPORT int get_copy_index(Hierarchy h);

IMPATOM_END_NAMESPACE

#endif /* IMPATOM_COPY_H */
