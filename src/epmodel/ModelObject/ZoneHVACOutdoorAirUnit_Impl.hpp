/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACOUTDOORAIRUNIT_IMPL_HPP
#define EPMODEL_ZONEHVACOUTDOORAIRUNIT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACOutdoorAirUnit_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACOutdoorAirUnit_Impl() override = default;

      boost::optional<double> outdoorAirFlowRate() const;
      bool isOutdoorAirFlowRateAutosized() const;
      bool setOutdoorAirFlowRate(double outdoorAirFlowRate);
      void autosizeOutdoorAirFlowRate();

      boost::optional<double> exhaustAirFlowRate() const;
      bool isExhaustAirFlowRateAutosized() const;
      bool setExhaustAirFlowRate(double exhaustAirFlowRate);
      void autosizeExhaustAirFlowRate();
      void resetExhaustAirFlowRate();

      std::string supplyFanPlacement() const;
      bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
      bool isSupplyFanPlacementDefaulted() const;
      void resetSupplyFanPlacement();

      std::string unitControlType() const;
      bool setUnitControlType(const std::string& unitControlType);
      bool isUnitControlTypeDefaulted() const;
      void resetUnitControlType();

      std::vector<std::string> supplyFanPlacementValues() const;
      std::vector<std::string> unitControlTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
