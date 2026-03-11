/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORINTEGRALCOLLECTORSTORAGE_IMPL_HPP
#define EPMODEL_SOLARCOLLECTORINTEGRALCOLLECTORSTORAGE_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API SolarCollectorIntegralCollectorStorage_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~SolarCollectorIntegralCollectorStorage_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  std::string bottomSurfaceBoundaryConditionsType() const;
  bool isBottomSurfaceBoundaryConditionsTypeDefaulted() const;

  boost::optional<double> maximumFlowRate() const;
  bool setMaximumFlowRate(double maximumFlowRate);
  void resetMaximumFlowRate();

  std::vector<std::string> bottomSurfaceBoundaryConditionsTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
