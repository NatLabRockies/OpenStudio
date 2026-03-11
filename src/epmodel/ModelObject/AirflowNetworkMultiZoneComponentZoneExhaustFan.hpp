/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTZONEEXHAUSTFAN_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTZONEEXHAUSTFAN_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl;
}

class EPMODEL_API AirflowNetworkMultiZoneComponentZoneExhaustFan : public ModelObject
{
 public:
  explicit AirflowNetworkMultiZoneComponentZoneExhaustFan(const Model& model);

  virtual ~AirflowNetworkMultiZoneComponentZoneExhaustFan() override = default;
  AirflowNetworkMultiZoneComponentZoneExhaustFan(const AirflowNetworkMultiZoneComponentZoneExhaustFan& other) = default;
  AirflowNetworkMultiZoneComponentZoneExhaustFan(AirflowNetworkMultiZoneComponentZoneExhaustFan&& other) = default;
  AirflowNetworkMultiZoneComponentZoneExhaustFan& operator=(const AirflowNetworkMultiZoneComponentZoneExhaustFan&) = default;
  AirflowNetworkMultiZoneComponentZoneExhaustFan& operator=(AirflowNetworkMultiZoneComponentZoneExhaustFan&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus
  //   AirflowNetwork:MultiZone:Component:ZoneExhaustFan fields N1/N2.
  // - Field Mapping: Name and Reference Crack Conditions are relationship-like object-list fields
  //   and are intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirflowNetworkZoneExhaustFan writes N1/N2 from linked crack
  //   properties and maps Reference Crack Conditions through a linked reference object name.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
  double airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions() const;
  bool setAirMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions(
    double airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions);

  double airMassFlowExponentWhentheZoneExhaustFanisOff() const;
  bool isAirMassFlowExponentWhentheZoneExhaustFanisOffDefaulted() const;
  bool setAirMassFlowExponentWhentheZoneExhaustFanisOff(double airMassFlowExponentWhentheZoneExhaustFanisOff);
  void resetAirMassFlowExponentWhentheZoneExhaustFanisOff();

 protected:
  using ImplType = detail::AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirflowNetworkMultiZoneComponentZoneExhaustFan(std::shared_ptr<detail::AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
