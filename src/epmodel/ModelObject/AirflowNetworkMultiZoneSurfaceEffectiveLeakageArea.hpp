/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONESURFACEEFFECTIVELEAKAGEAREA_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONESURFACEEFFECTIVELEAKAGEAREA_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl;
}

class EPMODEL_API AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea : public ModelObject
{
 public:
  explicit AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea(const Model& model);

  virtual ~AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea() override = default;
  AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea(const AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea& other) = default;
  AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea(AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea&& other) = default;
  AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea& operator=(const AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea&) = default;
  AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea& operator=(AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model AirflowNetworkEffectiveLeakageArea accessor naming for
  //   parity, while this epmodel type wraps the EnergyPlus object directly.
  // - Field Mapping: effectiveLeakageArea, dischargeCoefficient,
  //   referencePressureDifference, and airMassFlowExponent map directly to
  //   AirflowNetwork:MultiZone:Surface:EffectiveLeakageArea scalar fields.
  // - Field Mapping: Name remains provided by base ModelObject naming APIs.
  // - ForwardTranslator evidence: translateAirflowNetworkEffectiveLeakageArea writes the same
  //   four scalar values directly onto AirflowNetwork:MultiZone:Surface:EffectiveLeakageArea.
  // - TODO(parity): Add relationship APIs only if future schema evolution introduces linked fields.
  double effectiveLeakageArea() const;
  bool setEffectiveLeakageArea(double effectiveLeakageArea);

  double dischargeCoefficient() const;
  bool isDischargeCoefficientDefaulted() const;
  bool setDischargeCoefficient(double dischargeCoefficient);
  void resetDischargeCoefficient();

  double referencePressureDifference() const;
  bool isReferencePressureDifferenceDefaulted() const;
  bool setReferencePressureDifference(double referencePressureDifference);
  void resetReferencePressureDifference();

  double airMassFlowExponent() const;
  bool isAirMassFlowExponentDefaulted() const;
  bool setAirMassFlowExponent(double airMassFlowExponent);
  void resetAirMassFlowExponent();

 protected:
  using ImplType = detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea(
    std::shared_ptr<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
