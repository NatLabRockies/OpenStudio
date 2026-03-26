/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CENTRALHEATPUMPSYSTEM_IMPL_HPP
#define EPMODEL_CENTRALHEATPUMPSYSTEM_IMPL_HPP

#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CentralHeatPumpSystem_Impl : public WaterToWaterComponent_Impl
    {
     public:
      using WaterToWaterComponent_Impl::WaterToWaterComponent_Impl;
      virtual ~CentralHeatPumpSystem_Impl() override = default;

      unsigned supplyInletPort() const override;
      unsigned supplyOutletPort() const override;
      unsigned demandInletPort() const override;
      unsigned demandOutletPort() const override;
      unsigned tertiaryInletPort() const override;
      unsigned tertiaryOutletPort() const override;

      std::vector<std::string> controlMethodValues() const;

      std::string controlMethod() const;
      bool setControlMethod(const std::string& controlMethod);

      double ancillaryPower() const;
      bool setAncillaryPower(double ancillaryPower);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
