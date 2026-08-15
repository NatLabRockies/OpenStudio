/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNSPECIFICATIONOUTDOORAIR_IMPL_HPP
#define EPMODEL_DESIGNSPECIFICATIONOUTDOORAIR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Schedule;

  namespace detail {

    class EPMODEL_API DesignSpecificationOutdoorAir_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~DesignSpecificationOutdoorAir_Impl() override = default;

      // Outdoor air method
      std::string outdoorAirMethod() const;
      bool isOutdoorAirMethodDefaulted() const;
      bool setOutdoorAirMethod(const std::string& value);
      void resetOutdoorAirMethod();

      // Outdoor air flow per person
      double outdoorAirFlowperPerson() const;
      bool isOutdoorAirFlowperPersonDefaulted() const;
      bool setOutdoorAirFlowperPerson(double value);
      void resetOutdoorAirFlowperPerson();

      // Outdoor air flow per floor area
      double outdoorAirFlowperFloorArea() const;
      bool isOutdoorAirFlowperFloorAreaDefaulted() const;
      bool setOutdoorAirFlowperFloorArea(double value);
      void resetOutdoorAirFlowperFloorArea();

      // Outdoor air flow rate
      double outdoorAirFlowRate() const;
      bool isOutdoorAirFlowRateDefaulted() const;
      bool setOutdoorAirFlowRate(double value);
      void resetOutdoorAirFlowRate();

      // Outdoor air flow air changes per hour
      double outdoorAirFlowAirChangesperHour() const;
      bool isOutdoorAirFlowAirChangesperHourDefaulted() const;
      bool setOutdoorAirFlowAirChangesperHour(double value);
      void resetOutdoorAirFlowAirChangesperHour();

      boost::optional<Schedule> outdoorAirFlowRateFractionSchedule() const;
      bool setOutdoorAirFlowRateFractionSchedule(Schedule& schedule);
      void resetOutdoorAirFlowRateFractionSchedule();

      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
