/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGDXHEATEXCHANGERASSISTED_IMPL_HPP
#define EPMODEL_COILSYSTEMCOOLINGDXHEATEXCHANGERASSISTED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API CoilSystemCoolingDXHeatExchangerAssisted_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilSystemCoolingDXHeatExchangerAssisted_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      std::vector<std::string> heatExchangerObjectTypeValues() const;
      std::string heatExchangerObjectType() const;
      bool setHeatExchangerObjectType(const std::string& heatExchangerObjectType);

      std::vector<std::string> coolingCoilObjectTypeValues() const;
      std::string coolingCoilObjectType() const;
      bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
