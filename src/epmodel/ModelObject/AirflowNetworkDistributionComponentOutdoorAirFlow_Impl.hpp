/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTOUTDOORAIRFLOW_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTOUTDOORAIRFLOW_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkDistributionComponentOutdoorAirFlow_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkDistributionComponentOutdoorAirFlow_Impl() override = default;

  double airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions() const;
  bool setAirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions(double airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions);

  double airMassFlowExponentWhenNoOutdoorAirFlow() const;
  bool isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted() const;
  bool setAirMassFlowExponentWhenNoOutdoorAirFlow(double airMassFlowExponentWhenNoOutdoorAirFlow);
  void resetAirMassFlowExponentWhenNoOutdoorAirFlow();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
