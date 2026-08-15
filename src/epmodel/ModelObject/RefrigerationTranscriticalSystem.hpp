/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONTRANSCRITICALSYSTEM_HPP
#define EPMODEL_REFRIGERATIONTRANSCRITICALSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ThermalZone;

  namespace detail {
    class RefrigerationTranscriticalSystem_Impl;
  }

  class EPMODEL_API RefrigerationTranscriticalSystem : public ModelObject
  {
   public:
    explicit RefrigerationTranscriticalSystem(const Model& model);

    virtual ~RefrigerationTranscriticalSystem() override = default;
    RefrigerationTranscriticalSystem(const RefrigerationTranscriticalSystem& other) = default;
    RefrigerationTranscriticalSystem(RefrigerationTranscriticalSystem&& other) = default;
    RefrigerationTranscriticalSystem& operator=(const RefrigerationTranscriticalSystem&) = default;
    RefrigerationTranscriticalSystem& operator=(RefrigerationTranscriticalSystem&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> refrigerationSystemWorkingFluidTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar controls and the two optional suction-piping ThermalZone relationships are aligned.
    // - Canonical Counterpart: openstudio::model::RefrigerationTranscriticalSystem.
    // - Implemented Parity: The selected scalar methods and both optional suction-piping zone relationships preserve the canonical
    //   public signatures. Zone setters validate the configured object list and do not couple the related UA scalars.
    // - Field/Storage Mapping: Scalars and both zone relationships map directly to EnergyPlus Refrigeration:TranscriticalSystem fields;
    //   the zone fields use the configured ZoneNames object list.
    // - Canonicalization: Blank zone fields are valid and require no repair. Unresolved imported references remain untouched until an
    //   explicit typed setter or reset; ordinary APIs assume canonical state.
    // - Evidence: `src/model/RefrigerationTranscriticalSystem.hpp`, `src/model/RefrigerationTranscriticalSystem.cpp`,
    //   `resources/energyplus/ProposedEnergy+.idd`, and `src/epmodel/test/RefrigerationTranscriticalSystem_GTest.cpp`.
    // - Remaining Parity Work: Refrigerated case/walk-in lists, compressor lists, the gas cooler relationship, and object-level clone
    //   behavior remain deferred.
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

   protected:
    using ImplType = detail::RefrigerationTranscriticalSystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RefrigerationTranscriticalSystem(std::shared_ptr<detail::RefrigerationTranscriticalSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
