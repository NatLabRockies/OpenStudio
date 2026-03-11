/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONDUCTVIEWFACTORS_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONDUCTVIEWFACTORS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkDistributionDuctViewFactors_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkDistributionDuctViewFactors_Impl() override = default;

  double ductSurfaceExposureFraction() const;
  bool isDuctSurfaceExposureFractionDefaulted() const;
  bool setDuctSurfaceExposureFraction(double ductSurfaceExposureFraction);
  void resetDuctSurfaceExposureFraction();

  double ductSurfaceEmittance() const;
  bool isDuctSurfaceEmittanceDefaulted() const;
  bool setDuctSurfaceEmittance(double ductSurfaceEmittance);
  void resetDuctSurfaceEmittance();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
