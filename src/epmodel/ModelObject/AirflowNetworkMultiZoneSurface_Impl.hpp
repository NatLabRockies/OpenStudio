/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONESURFACE_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONESURFACE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkMultiZoneSurface_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkMultiZoneSurface_Impl() override = default;

  double windowDoorOpeningFactororCrackFactor() const;
  bool isWindowDoorOpeningFactororCrackFactorDefaulted() const;
  bool setWindowDoorOpeningFactororCrackFactor(double windowDoorOpeningFactororCrackFactor);
  void resetWindowDoorOpeningFactororCrackFactor();

  std::string ventilationControlMode() const;
  bool isVentilationControlModeDefaulted() const;
  bool setVentilationControlMode(const std::string& ventilationControlMode);
  void resetVentilationControlMode();

  double minimumVentingOpenFactor() const;
  bool isMinimumVentingOpenFactorDefaulted() const;
  bool setMinimumVentingOpenFactor(double minimumVentingOpenFactor);
  void resetMinimumVentingOpenFactor();

  double indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor() const;
  bool isIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted() const;
  bool setIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor(
    double indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor);
  void resetIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor();

  double indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor() const;
  bool isIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted() const;
  bool setIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor(
    double indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor);
  void resetIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor();

  double indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor() const;
  bool isIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted() const;
  bool setIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor(
    double indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor);
  void resetIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor();

  double indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor() const;
  bool isIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted() const;
  bool setIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor(
    double indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor);
  void resetIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor();

  std::string equivalentRectangleMethod() const;
  bool isEquivalentRectangleMethodDefaulted() const;
  bool setEquivalentRectangleMethod(const std::string& equivalentRectangleMethod);
  void resetEquivalentRectangleMethod();

  double equivalentRectangleAspectRatio() const;
  bool isEquivalentRectangleAspectRatioDefaulted() const;
  bool setEquivalentRectangleAspectRatio(double equivalentRectangleAspectRatio);
  void resetEquivalentRectangleAspectRatio();

  std::vector<std::string> ventilationControlModeValues() const;
  std::vector<std::string> equivalentRectangleMethodValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
