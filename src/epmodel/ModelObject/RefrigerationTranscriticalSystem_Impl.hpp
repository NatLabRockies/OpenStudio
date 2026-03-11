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

  namespace detail {

    class EPMODEL_API RefrigerationTranscriticalSystem_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RefrigerationTranscriticalSystem_Impl() override = default;

      double receiverPressure() const;
      bool isReceiverPressureDefaulted() const;

      double subcoolerEffectiveness() const;
      bool isSubcoolerEffectivenessDefaulted() const;

      std::string refrigerationSystemWorkingFluidType() const;

      double sumUASuctionPipingforMediumTemperatureLoads() const;
      bool isSumUASuctionPipingforMediumTemperatureLoadsDefaulted() const;

      double sumUASuctionPipingforLowTemperatureLoads() const;
      bool isSumUASuctionPipingforLowTemperatureLoadsDefaulted() const;

      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;

      bool setReceiverPressure(double receiverPressure);
      void resetReceiverPressure();

      bool setSubcoolerEffectiveness(double subcoolerEffectiveness);
      void resetSubcoolerEffectiveness();

      bool setRefrigerationSystemWorkingFluidType(const std::string& refrigerationSystemWorkingFluidType);

      bool setSumUASuctionPipingforMediumTemperatureLoads(double sumUASuctionPipingforMediumTemperatureLoads);
      void resetSumUASuctionPipingforMediumTemperatureLoads();

      bool setSumUASuctionPipingforLowTemperatureLoads(double sumUASuctionPipingforLowTemperatureLoads);
      void resetSumUASuctionPipingforLowTemperatureLoads();

      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
