/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONESURFACE_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONESURFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirflowNetworkMultiZoneSurface_Impl;
}

class EPMODEL_API AirflowNetworkMultiZoneSurface : public ModelObject
{
 public:
  explicit AirflowNetworkMultiZoneSurface(const Model& model);

  virtual ~AirflowNetworkMultiZoneSurface() override = default;
  AirflowNetworkMultiZoneSurface(const AirflowNetworkMultiZoneSurface& other) = default;
  AirflowNetworkMultiZoneSurface(AirflowNetworkMultiZoneSurface&& other) = default;
  AirflowNetworkMultiZoneSurface& operator=(const AirflowNetworkMultiZoneSurface&) = default;
  AirflowNetworkMultiZoneSurface& operator=(AirflowNetworkMultiZoneSurface&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> ventilationControlModeValues();
  static std::vector<std::string> equivalentRectangleMethodValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus AirflowNetwork:MultiZone:Surface scalar fields.
  // - Field Mapping: Name remains provided by base ModelObject naming APIs.
  // - Field Mapping: Surface Name, Leakage Component Name, External Node Name, Ventilation Control Zone
  //   Temperature Setpoint Schedule Name, Venting Availability Schedule Name, and Occupant Ventilation
  //   Control Name are relationship-like object-list links and excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirflowNetworkSurface writes all exposed scalar fields directly.
  // - TODO(parity): Add typed relationship APIs if/when non-scalar parity work is prioritized.
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

 protected:
  using ImplType = detail::AirflowNetworkMultiZoneSurface_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirflowNetworkMultiZoneSurface(std::shared_ptr<detail::AirflowNetworkMultiZoneSurface_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
