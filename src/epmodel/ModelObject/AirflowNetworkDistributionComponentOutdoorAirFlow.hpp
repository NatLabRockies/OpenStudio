/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTOUTDOORAIRFLOW_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTOUTDOORAIRFLOW_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirflowNetworkDistributionComponentOutdoorAirFlow_Impl;
}

class EPMODEL_API AirflowNetworkDistributionComponentOutdoorAirFlow : public ModelObject
{
 public:
  explicit AirflowNetworkDistributionComponentOutdoorAirFlow(const Model& model);

  virtual ~AirflowNetworkDistributionComponentOutdoorAirFlow() override = default;
  AirflowNetworkDistributionComponentOutdoorAirFlow(const AirflowNetworkDistributionComponentOutdoorAirFlow& other) = default;
  AirflowNetworkDistributionComponentOutdoorAirFlow(AirflowNetworkDistributionComponentOutdoorAirFlow&& other) = default;
  AirflowNetworkDistributionComponentOutdoorAirFlow& operator=(const AirflowNetworkDistributionComponentOutdoorAirFlow&) = default;
  AirflowNetworkDistributionComponentOutdoorAirFlow& operator=(AirflowNetworkDistributionComponentOutdoorAirFlow&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions and
  //   airMassFlowExponentWhenNoOutdoorAirFlow map directly to EnergyPlus
  //   AirflowNetwork:Distribution:Component:OutdoorAirFlow scalar fields.
  // - Field Mapping: Outdoor Air Mixer Name and Reference Crack Conditions are relationship-like
  //   object-list fields and are intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirflowNetworkOutdoorAirflow creates
  //   AirflowNetwork:Distribution:Component:OutdoorAirFlow and writes mass-flow crack terms.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
  double airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions() const;
  bool setAirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions(double airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions);

  double airMassFlowExponentWhenNoOutdoorAirFlow() const;
  bool isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted() const;
  bool setAirMassFlowExponentWhenNoOutdoorAirFlow(double airMassFlowExponentWhenNoOutdoorAirFlow);
  void resetAirMassFlowExponentWhenNoOutdoorAirFlow();

 protected:
  using ImplType = detail::AirflowNetworkDistributionComponentOutdoorAirFlow_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirflowNetworkDistributionComponentOutdoorAirFlow(std::shared_ptr<detail::AirflowNetworkDistributionComponentOutdoorAirFlow_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
