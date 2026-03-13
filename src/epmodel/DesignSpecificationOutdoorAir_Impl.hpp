/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNSPECIFICATIONOUTDOORAIR_IMPL_HPP
#define EPMODEL_DESIGNSPECIFICATIONOUTDOORAIR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API DesignSpecificationOutdoorAir_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~DesignSpecificationOutdoorAir_Impl() override = default;

      // Outdoor air method
      std::string outdoorAirMethod() const;
      bool setOutdoorAirMethod(const std::string& value);

      // Outdoor air flow per person
      double outdoorAirFlowperPerson() const;
      bool setOutdoorAirFlowperPerson(double value);

      // Outdoor air flow per floor area
      double outdoorAirFlowperFloorArea() const;
      bool setOutdoorAirFlowperFloorArea(double value);

      // Outdoor air flow rate
      double outdoorAirFlowRate() const;
      bool setOutdoorAirFlowRate(double value);

      // Outdoor air flow air changes per hour
      double outdoorAirFlowAirChangesperHour() const;
      bool setOutdoorAirFlowAirChangesperHour(double value);

      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
