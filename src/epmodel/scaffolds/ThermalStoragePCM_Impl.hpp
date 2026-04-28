/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALSTORAGEPCM_IMPL_HPP
#define EPMODEL_THERMALSTORAGEPCM_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ThermalStoragePCM_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ThermalStoragePCM_Impl() override = default;

      boost::optional<double> tankCapacity() const;
      bool isTankCapacityAutosized() const;
      bool setTankCapacity(double tankCapacity);
      void autosizeTankCapacity();

      boost::optional<double> heatLossRate() const;
      bool isHeatLossRateDefaulted() const;
      bool setHeatLossRate(double heatLossRate);
      void resetHeatLossRate();

      boost::optional<double> useSideDesignFlowRate() const;
      bool isUseSideDesignFlowRateAutosized() const;
      bool setUseSideDesignFlowRate(double useSideDesignFlowRate);
      void autosizeUseSideDesignFlowRate();

      boost::optional<double> plantSideDesignFlowRate() const;
      bool isPlantSideDesignFlowRateAutosized() const;
      bool setPlantSideDesignFlowRate(double plantSideDesignFlowRate);
      void autosizePlantSideDesignFlowRate();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
