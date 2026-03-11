/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONDUCTSIZING_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONDUCTSIZING_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkDistributionDuctSizing_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkDistributionDuctSizing_Impl() override = default;

  std::string ductSizingMethod() const;
  bool isDuctSizingMethodDefaulted() const;
  bool setDuctSizingMethod(const std::string& ductSizingMethod);
  void resetDuctSizingMethod();

  double ductSizingFactor() const;
  bool isDuctSizingFactorDefaulted() const;
  bool setDuctSizingFactor(double ductSizingFactor);
  void resetDuctSizingFactor();

  double maximumAirflowVelocity() const;
  bool isMaximumAirflowVelocityDefaulted() const;
  bool setMaximumAirflowVelocity(double maximumAirflowVelocity);
  void resetMaximumAirflowVelocity();

  boost::optional<double> totalPressureLossAcrossSupplyTrunk() const;
  bool setTotalPressureLossAcrossSupplyTrunk(double totalPressureLossAcrossSupplyTrunk);
  void resetTotalPressureLossAcrossSupplyTrunk();

  boost::optional<double> totalPressureLossAcrossSupplyBranch() const;
  bool setTotalPressureLossAcrossSupplyBranch(double totalPressureLossAcrossSupplyBranch);
  void resetTotalPressureLossAcrossSupplyBranch();

  boost::optional<double> totalPressureLossAcrossReturnTrunk() const;
  bool setTotalPressureLossAcrossReturnTrunk(double totalPressureLossAcrossReturnTrunk);
  void resetTotalPressureLossAcrossReturnTrunk();

  boost::optional<double> totalPressureLossAcrossReturnBranch() const;
  bool setTotalPressureLossAcrossReturnBranch(double totalPressureLossAcrossReturnBranch);
  void resetTotalPressureLossAcrossReturnBranch();

  std::vector<std::string> ductSizingMethodValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
