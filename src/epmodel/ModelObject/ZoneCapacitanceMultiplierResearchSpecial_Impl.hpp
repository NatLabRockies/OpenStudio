/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONECAPACITANCEMULTIPLIERRESEARCHSPECIAL_IMPL_HPP
#define EPMODEL_ZONECAPACITANCEMULTIPLIERRESEARCHSPECIAL_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneCapacitanceMultiplierResearchSpecial_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneCapacitanceMultiplierResearchSpecial_Impl() override = default;

      double temperatureCapacityMultiplier() const;
      bool isTemperatureCapacityMultiplierDefaulted() const;
      bool setTemperatureCapacityMultiplier(double temperatureCapacityMultiplier);
      void resetTemperatureCapacityMultiplier();

      double humidityCapacityMultiplier() const;
      bool isHumidityCapacityMultiplierDefaulted() const;
      bool setHumidityCapacityMultiplier(double humidityCapacityMultiplier);
      void resetHumidityCapacityMultiplier();

      double carbonDioxideCapacityMultiplier() const;
      bool isCarbonDioxideCapacityMultiplierDefaulted() const;
      bool setCarbonDioxideCapacityMultiplier(double carbonDioxideCapacityMultiplier);
      void resetCarbonDioxideCapacityMultiplier();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONECAPACITANCEMULTIPLIERRESEARCHSPECIAL_IMPL_HPP
