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

  class Schedule;

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
      bool addToNode(Node& node) override;
      bool addToTertiaryNode(Node& node) override;

      std::vector<std::string> controlMethodValues() const;

      std::string controlMethod() const;
      bool setControlMethod(const std::string& controlMethod);

      double ancillaryPower() const;
      bool setAncillaryPower(double ancillaryPower);

      boost::optional<Schedule> ancillaryOperationSchedule() const;
      bool setAncillaryOperationSchedule(Schedule& schedule);
      void resetAncillaryOperationSchedule();

      boost::optional<PlantLoop> coolingPlantLoop() const;
      boost::optional<PlantLoop> sourcePlantLoop() const;
      boost::optional<PlantLoop> heatingPlantLoop() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
