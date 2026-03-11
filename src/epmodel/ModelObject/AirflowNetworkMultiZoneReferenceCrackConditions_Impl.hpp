/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONEREFERENCECRACKCONDITIONS_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONEREFERENCECRACKCONDITIONS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkMultiZoneReferenceCrackConditions_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkMultiZoneReferenceCrackConditions_Impl() override = default;

  double referenceTemperature() const;
  bool setReferenceTemperature(double referenceTemperature);

  double referenceBarometricPressure() const;
  bool isReferenceBarometricPressureDefaulted() const;
  bool setReferenceBarometricPressure(double referenceBarometricPressure);
  void resetReferenceBarometricPressure();

  double referenceHumidityRatio() const;
  bool isReferenceHumidityRatioDefaulted() const;
  bool setReferenceHumidityRatio(double referenceHumidityRatio);
  void resetReferenceHumidityRatio();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
