/**
 *  \file IMP/core/RestraintsScoringFunction.h
 *  \brief Storage of a model, its restraints,
 *                         constraints and particles.
 *
 *  Copyright 2007-2019 IMP Inventors. All rights reserved.
 *
 */

#ifndef IMPCORE_RESTRAINTS_SCORING_FUNCTION_H
#define IMPCORE_RESTRAINTS_SCORING_FUNCTION_H

#include <IMP/core/core_config.h>
#include <IMP/ScoringFunction.h>
#include <IMP/Restraint.h>
#include <IMP/internal/RestraintsScoringFunction.h>

IMPCORE_BEGIN_NAMESPACE

/** Create a scoring function on a list of restraints.
*/
class RestraintsScoringFunction :
#if defined(IMP_DOXYGEN) || defined(SWIG)
    public ScoringFunction
#else
    public IMP::internal::RestraintsScoringFunction
#endif
    {
 public:
  RestraintsScoringFunction(const RestraintsAdaptor &rs,
                            double weight = 1.0, double max = NO_MAX,
                            std::string name = "RestraintsScoringFunction%1%")
      : IMP::internal::RestraintsScoringFunction(rs, weight, max, name) {}
  RestraintsScoringFunction(const RestraintsAdaptor &rs,
                            std::string name)
      : IMP::internal::RestraintsScoringFunction(rs, 1.0, NO_MAX, name) {}
#if defined(SWIG)
  void do_add_score_and_derivatives(ScoreAccumulator sa,
                                    const ScoreStatesTemp &ss)
      IMP_OVERRIDE;
  virtual Restraints create_restraints() const IMP_OVERRIDE;
  virtual ModelObjectsTemp do_get_inputs() const IMP_OVERRIDE;
  IMP_OBJECT_METHODS(RestraintsScoringFunction);
#endif
};

IMPCORE_END_NAMESPACE

#endif /* IMPCORE_RESTRAINTS_SCORING_FUNCTION_H */
