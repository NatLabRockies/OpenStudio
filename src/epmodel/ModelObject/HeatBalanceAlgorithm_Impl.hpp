/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATBALANCEALGORITHM_IMPL_HPP
#define EPMODEL_HEATBALANCEALGORITHM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HeatBalanceAlgorithm_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HeatBalanceAlgorithm_Impl() override = default;

  std::string algorithm() const;
  bool isAlgorithmDefaulted() const;
  double surfaceTemperatureUpperLimit() const;
  bool isSurfaceTemperatureUpperLimitDefaulted() const;
  double minimumSurfaceConvectionHeatTransferCoefficientValue() const;
  bool isMinimumSurfaceConvectionHeatTransferCoefficientValueDefaulted() const;
  double maximumSurfaceConvectionHeatTransferCoefficientValue() const;
  bool isMaximumSurfaceConvectionHeatTransferCoefficientValueDefaulted() const;

  bool setAlgorithm(const std::string& algorithm);
  void resetAlgorithm();
  bool setSurfaceTemperatureUpperLimit(double surfaceTemperatureUpperLimit);
  void resetSurfaceTemperatureUpperLimit();
  bool setMinimumSurfaceConvectionHeatTransferCoefficientValue(double minimumSurfaceConvectionHeatTransferCoefficientValue);
  void resetMinimumSurfaceConvectionHeatTransferCoefficientValue();
  bool setMaximumSurfaceConvectionHeatTransferCoefficientValue(double maximumSurfaceConvectionHeatTransferCoefficientValue);
  void resetMaximumSurfaceConvectionHeatTransferCoefficientValue();

 private:
  std::vector<std::string> algorithmValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
