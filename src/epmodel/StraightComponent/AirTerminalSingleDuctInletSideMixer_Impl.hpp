/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTINLETSIDEMIXER_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTINLETSIDEMIXER_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class ZoneHVACAirDistributionUnit;

  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctInletSideMixer_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctInletSideMixer_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;
      bool removeFromLoop() override;
      std::vector<openstudio::IdfObject> remove() override;

      boost::optional<ZoneHVACAirDistributionUnit> zoneHVACAirDistributionUnit() const;

      std::string perPersonVentilationRateMode() const;
      bool setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode);
      unsigned secondaryAirInletPort() const;
      boost::optional<Node> secondaryAirInletNode() const;

      std::vector<std::string> perPersonVentilationRateModeValues() const;

     protected:
      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
