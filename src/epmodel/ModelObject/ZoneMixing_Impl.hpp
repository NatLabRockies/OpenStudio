/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEMIXING_IMPL_HPP
#define EPMODEL_ZONEMIXING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneMixing_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneMixing_Impl() override = default;

      std::string designFlowRateCalculationMethod() const;

      boost::optional<double> designFlowRate() const;
      bool setDesignFlowRate(double designFlowRate);
      void resetDesignFlowRate();

      boost::optional<double> flowRateperFloorArea() const;
      bool setFlowRateperFloorArea(double flowRateperFloorArea);
      void resetFlowRateperFloorArea();

      boost::optional<double> flowRateperPerson() const;
      bool setFlowRateperPerson(double flowRateperPerson);
      void resetFlowRateperPerson();

      boost::optional<double> airChangesperHour() const;
      bool setAirChangesperHour(double airChangesperHour);
      void resetAirChangesperHour();

      boost::optional<double> deltaTemperature() const;
      bool setDeltaTemperature(double deltaTemperature);
      void resetDeltaTemperature();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
