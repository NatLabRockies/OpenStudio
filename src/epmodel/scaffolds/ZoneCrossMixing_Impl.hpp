/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECROSSMIXING_IMPL_HPP
#define EPMODEL_ZONECROSSMIXING_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneCrossMixing_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneCrossMixing_Impl() override = default;

      std::vector<std::string> designFlowRateCalculationMethodValues() const;

      std::string designFlowRateCalculationMethod() const;
      bool isDesignFlowRateCalculationMethodDefaulted() const;
      bool setDesignFlowRateCalculationMethod(const std::string& designFlowRateCalculationMethod);
      void resetDesignFlowRateCalculationMethod();

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

      double deltaTemperature() const;
      bool isDeltaTemperatureDefaulted() const;
      bool setDeltaTemperature(double deltaTemperature);
      void resetDeltaTemperature();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
