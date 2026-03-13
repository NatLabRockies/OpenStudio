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

      bool addToNode(Node& node) override;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      std::vector<std::string> heatExchangerObjectTypeValues() const;
      std::vector<std::string> coolingCoilObjectTypeValues() const;

      // Scalar-only parity surface: relationship fields remain excluded by contract.
      /** @name Heat exchanger object type */
      //@{
      std::string heatExchangerObjectType() const;
      bool setHeatExchangerObjectType(const std::string& heatExchangerObjectType);
      //@}

      /** @name Cooling coil object type */
      //@{
      std::string coolingCoilObjectType() const;
      bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);
      //@}
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
