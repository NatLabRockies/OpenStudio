/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTHEATEXCHANGER_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTHEATEXCHANGER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirflowNetworkDistributionComponentHeatExchanger_Impl;
}

class EPMODEL_API AirflowNetworkDistributionComponentHeatExchanger : public ModelObject
{
 public:
  explicit AirflowNetworkDistributionComponentHeatExchanger(const Model& model);

  virtual ~AirflowNetworkDistributionComponentHeatExchanger() override = default;
  AirflowNetworkDistributionComponentHeatExchanger(const AirflowNetworkDistributionComponentHeatExchanger& other) = default;
  AirflowNetworkDistributionComponentHeatExchanger(AirflowNetworkDistributionComponentHeatExchanger&& other) = default;
  AirflowNetworkDistributionComponentHeatExchanger& operator=(const AirflowNetworkDistributionComponentHeatExchanger&) = default;
  AirflowNetworkDistributionComponentHeatExchanger& operator=(AirflowNetworkDistributionComponentHeatExchanger&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: airPathLength and airPathHydraulicDiameter map directly to EnergyPlus
  //   AirflowNetwork:Distribution:Component:HeatExchanger scalar fields.
  // - Field Mapping: HeatExchanger Name and HeatExchanger Object Type are relationship-like
  //   target-link fields and are intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirflowNetworkEquivalentDuct writes HeatExchanger Name/
  //   HeatExchanger Object Type from linked model objects and writes these two scalar fields directly.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
  double airPathLength() const;
  bool setAirPathLength(double airPathLength);

  double airPathHydraulicDiameter() const;
  bool setAirPathHydraulicDiameter(double airPathHydraulicDiameter);

 protected:
  using ImplType = detail::AirflowNetworkDistributionComponentHeatExchanger_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirflowNetworkDistributionComponentHeatExchanger(std::shared_ptr<detail::AirflowNetworkDistributionComponentHeatExchanger_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
