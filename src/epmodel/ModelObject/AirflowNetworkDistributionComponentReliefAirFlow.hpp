/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTRELIEFAIRFLOW_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTRELIEFAIRFLOW_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirflowNetworkDistributionComponentReliefAirFlow_Impl;
}

class EPMODEL_API AirflowNetworkDistributionComponentReliefAirFlow : public ModelObject
{
 public:
  explicit AirflowNetworkDistributionComponentReliefAirFlow(const Model& model);

  virtual ~AirflowNetworkDistributionComponentReliefAirFlow() override = default;
  AirflowNetworkDistributionComponentReliefAirFlow(const AirflowNetworkDistributionComponentReliefAirFlow& other) = default;
  AirflowNetworkDistributionComponentReliefAirFlow(AirflowNetworkDistributionComponentReliefAirFlow&& other) = default;
  AirflowNetworkDistributionComponentReliefAirFlow& operator=(const AirflowNetworkDistributionComponentReliefAirFlow&) = default;
  AirflowNetworkDistributionComponentReliefAirFlow& operator=(AirflowNetworkDistributionComponentReliefAirFlow&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions and
  //   airMassFlowExponentWhenNoOutdoorAirFlow map directly to EnergyPlus
  //   AirflowNetwork:Distribution:Component:ReliefAirFlow scalar fields.
  // - Field Mapping: Outdoor Air Mixer Name and Reference Crack Conditions are relationship-like
  //   object-list fields and are intentionally excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
  double airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions() const;
  bool setAirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions(double airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions);

  double airMassFlowExponentWhenNoOutdoorAirFlow() const;
  bool isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted() const;
  bool setAirMassFlowExponentWhenNoOutdoorAirFlow(double airMassFlowExponentWhenNoOutdoorAirFlow);
  void resetAirMassFlowExponentWhenNoOutdoorAirFlow();

 protected:
  using ImplType = detail::AirflowNetworkDistributionComponentReliefAirFlow_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirflowNetworkDistributionComponentReliefAirFlow(
    std::shared_ptr<detail::AirflowNetworkDistributionComponentReliefAirFlow_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
