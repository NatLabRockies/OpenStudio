/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALSTORAGEPCM_HPP
#define EPMODEL_THERMALSTORAGEPCM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermalStoragePCM_Impl;
  }

  class EPMODEL_API ThermalStoragePCM : public ModelObject
  {
   public:
    explicit ThermalStoragePCM(const Model& model);

    virtual ~ThermalStoragePCM() override = default;
    ThermalStoragePCM(const ThermalStoragePCM& other) = default;
    ThermalStoragePCM(ThermalStoragePCM&& other) = default;
    ThermalStoragePCM& operator=(const ThermalStoragePCM&) = default;
    ThermalStoragePCM& operator=(ThermalStoragePCM&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: IDD-derived naming is preserved because no openstudio::model counterpart exists for ThermalStorage:PCM.
    // - Field Mapping: Scalar APIs map directly to Tank Capacity, Heat Loss Rate, Use Side Design Flow Rate, and Plant Side
    //   Design Flow Rate fields in EnergyPlus.
    // - Field Mapping: Availability Schedule Name, plant/use node names, and PCM Material Name remain relationship/object-list
    //   fields that are intentionally excluded from this scalar scaffold.
    boost::optional<double> tankCapacity() const;
    bool setTankCapacity(double tankCapacity);
    bool isTankCapacityAutosized() const;
    void autosizeTankCapacity();

    boost::optional<double> heatLossRate() const;
    bool setHeatLossRate(double heatLossRate);
    bool isHeatLossRateDefaulted() const;
    void resetHeatLossRate();

    boost::optional<double> useSideDesignFlowRate() const;
    bool setUseSideDesignFlowRate(double useSideDesignFlowRate);
    bool isUseSideDesignFlowRateAutosized() const;
    void autosizeUseSideDesignFlowRate();

    boost::optional<double> plantSideDesignFlowRate() const;
    bool setPlantSideDesignFlowRate(double plantSideDesignFlowRate);
    bool isPlantSideDesignFlowRateAutosized() const;
    void autosizePlantSideDesignFlowRate();

   protected:
    using ImplType = detail::ThermalStoragePCM_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermalStoragePCM(std::shared_ptr<detail::ThermalStoragePCM_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
