/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONESURFACECRACK_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONESURFACECRACK_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirflowNetworkMultiZoneSurfaceCrack_Impl;
}

class EPMODEL_API AirflowNetworkMultiZoneSurfaceCrack : public ModelObject
{
 public:
  explicit AirflowNetworkMultiZoneSurfaceCrack(const Model& model);

  virtual ~AirflowNetworkMultiZoneSurfaceCrack() override = default;
  AirflowNetworkMultiZoneSurfaceCrack(const AirflowNetworkMultiZoneSurfaceCrack& other) = default;
  AirflowNetworkMultiZoneSurfaceCrack(AirflowNetworkMultiZoneSurfaceCrack&& other) = default;
  AirflowNetworkMultiZoneSurfaceCrack& operator=(const AirflowNetworkMultiZoneSurfaceCrack&) = default;
  AirflowNetworkMultiZoneSurfaceCrack& operator=(AirflowNetworkMultiZoneSurfaceCrack&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: airMassFlowCoefficientatReferenceConditions and airMassFlowExponent map
  //   directly to EnergyPlus AirflowNetwork:MultiZone:Surface:Crack scalar fields.
  // - Field Mapping: Name remains provided by base ModelObject naming APIs.
  // - Field Mapping: Reference Crack Conditions is a relationship-like object-list field and is
  //   intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirflowNetworkCrack writes Name, Air Mass Flow
  //   Coefficient at Reference Conditions, Air Mass Flow Exponent, and optional Reference Crack
  //   Conditions directly to AirflowNetwork:MultiZone:Surface:Crack.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
  double airMassFlowCoefficientatReferenceConditions() const;
  bool setAirMassFlowCoefficientatReferenceConditions(double airMassFlowCoefficientatReferenceConditions);

  double airMassFlowExponent() const;
  bool isAirMassFlowExponentDefaulted() const;
  bool setAirMassFlowExponent(double airMassFlowExponent);
  void resetAirMassFlowExponent();

 protected:
  using ImplType = detail::AirflowNetworkMultiZoneSurfaceCrack_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirflowNetworkMultiZoneSurfaceCrack(std::shared_ptr<detail::AirflowNetworkMultiZoneSurfaceCrack_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
