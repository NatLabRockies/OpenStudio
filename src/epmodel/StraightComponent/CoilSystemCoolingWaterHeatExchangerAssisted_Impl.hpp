/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGWATERHEATEXCHANGERASSISTED_IMPL_HPP
#define EPMODEL_COILSYSTEMCOOLINGWATERHEATEXCHANGERASSISTED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API CoilSystemCoolingWaterHeatExchangerAssisted_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilSystemCoolingWaterHeatExchangerAssisted_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  // Scalar-only parity surface: relationship fields remain excluded by contract.
  std::string heatExchangerObjectType() const;
  bool setHeatExchangerObjectType(const std::string& heatExchangerObjectType);

  std::string coolingCoilObjectType() const;
  bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

  std::vector<std::string> heatExchangerObjectTypeValues() const;
  std::vector<std::string> coolingCoilObjectTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
