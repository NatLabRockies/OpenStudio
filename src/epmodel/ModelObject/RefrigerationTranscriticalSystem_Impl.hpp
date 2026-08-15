/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONTRANSCRITICALSYSTEM_IMPL_HPP
#define EPMODEL_REFRIGERATIONTRANSCRITICALSYSTEM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  class ThermalZone;

  namespace detail {

    class EPMODEL_API RefrigerationTranscriticalSystem_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RefrigerationTranscriticalSystem_Impl() override = default;

      double receiverPressure() const;
      bool isReceiverPressureDefaulted() const;
      bool setReceiverPressure(double receiverPressure);
      void resetReceiverPressure();

      double subcoolerEffectiveness() const;
      bool isSubcoolerEffectivenessDefaulted() const;
      bool setSubcoolerEffectiveness(double subcoolerEffectiveness);
      void resetSubcoolerEffectiveness();

      std::string refrigerationSystemWorkingFluidType() const;
      bool setRefrigerationSystemWorkingFluidType(const std::string& refrigerationSystemWorkingFluidType);

      double sumUASuctionPipingforMediumTemperatureLoads() const;
      bool isSumUASuctionPipingforMediumTemperatureLoadsDefaulted() const;
      bool setSumUASuctionPipingforMediumTemperatureLoads(double sumUASuctionPipingforMediumTemperatureLoads);
      void resetSumUASuctionPipingforMediumTemperatureLoads();

      boost::optional<ThermalZone> mediumTemperatureSuctionPipingZone() const;
      bool setMediumTemperatureSuctionPipingZone(const ThermalZone& thermalZone);
      void resetMediumTemperatureSuctionPipingZone();

      double sumUASuctionPipingforLowTemperatureLoads() const;
      bool isSumUASuctionPipingforLowTemperatureLoadsDefaulted() const;
      bool setSumUASuctionPipingforLowTemperatureLoads(double sumUASuctionPipingforLowTemperatureLoads);
      void resetSumUASuctionPipingforLowTemperatureLoads();

      boost::optional<ThermalZone> lowTemperatureSuctionPipingZone() const;
      bool setLowTemperatureSuctionPipingZone(const ThermalZone& thermalZone);
      void resetLowTemperatureSuctionPipingZone();

      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
