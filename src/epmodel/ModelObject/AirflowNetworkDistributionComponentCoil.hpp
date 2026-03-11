/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTCOIL_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTCOIL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirflowNetworkDistributionComponentCoil_Impl;
}

class EPMODEL_API AirflowNetworkDistributionComponentCoil : public ModelObject
{
 public:
  explicit AirflowNetworkDistributionComponentCoil(const Model& model);

  virtual ~AirflowNetworkDistributionComponentCoil() override = default;
  AirflowNetworkDistributionComponentCoil(const AirflowNetworkDistributionComponentCoil& other) = default;
  AirflowNetworkDistributionComponentCoil(AirflowNetworkDistributionComponentCoil&& other) = default;
  AirflowNetworkDistributionComponentCoil& operator=(const AirflowNetworkDistributionComponentCoil&) = default;
  AirflowNetworkDistributionComponentCoil& operator=(AirflowNetworkDistributionComponentCoil&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: airPathLength and airPathHydraulicDiameter map directly to EnergyPlus
  //   AirflowNetwork:Distribution:Component:Coil scalar fields.
  // - Field Mapping: Coil Name and Coil Object Type are relationship-like target-link fields
  //   and are intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirflowNetworkEquivalentDuct writes Coil Name/
  //   Coil Object Type from linked model objects, and writes these two scalar fields directly.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
  double airPathLength() const;
  bool setAirPathLength(double airPathLength);

  double airPathHydraulicDiameter() const;
  bool setAirPathHydraulicDiameter(double airPathHydraulicDiameter);

 protected:
  using ImplType = detail::AirflowNetworkDistributionComponentCoil_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirflowNetworkDistributionComponentCoil(std::shared_ptr<detail::AirflowNetworkDistributionComponentCoil_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
