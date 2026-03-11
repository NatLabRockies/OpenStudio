/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONESURFACECRACK_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONESURFACECRACK_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkMultiZoneSurfaceCrack_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkMultiZoneSurfaceCrack_Impl() override = default;

  double airMassFlowCoefficientatReferenceConditions() const;
  bool setAirMassFlowCoefficientatReferenceConditions(double airMassFlowCoefficientatReferenceConditions);

  double airMassFlowExponent() const;
  bool isAirMassFlowExponentDefaulted() const;
  bool setAirMassFlowExponent(double airMassFlowExponent);
  void resetAirMassFlowExponent();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
