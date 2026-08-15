/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONSYSTEM_HPP
#define EPMODEL_REFRIGERATIONSYSTEM_HPP

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
    class RefrigerationSystem_Impl;
  }

  class EPMODEL_API RefrigerationSystem : public ModelObject
  {
   public:
    explicit RefrigerationSystem(const Model& model);

    virtual ~RefrigerationSystem() override = default;
    RefrigerationSystem(const RefrigerationSystem& other) = default;
    RefrigerationSystem(RefrigerationSystem&& other) = default;
    RefrigerationSystem& operator=(const RefrigerationSystem&) = default;
    RefrigerationSystem& operator=(RefrigerationSystem&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> refrigerationSystemWorkingFluidTypeValues();
    static std::vector<std::string> suctionTemperatureControlTypeValues();
    static std::vector<std::string> intercoolerTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The selected scalar controls and optional suction-piping ThermalZone relationship are aligned.
    // - Canonical Counterpart: openstudio::model::RefrigerationSystem.
    // - Implemented Parity: The selected scalar methods and suction-piping zone preserve the canonical public signatures. The zone
    //   setter validates the configured object list and does not couple Sum UA Suction Piping.
    // - Field/Storage Mapping: Scalars and the zone map directly to EnergyPlus Refrigeration:System fields; choice helpers mirror IDD
    //   key lookups, and the zone field uses the configured ZoneNames object list.
    // - Canonicalization: A blank zone field is valid and requires no repair. Unresolved imported references remain untouched until an
    //   explicit typed setter or reset; ordinary APIs assume canonical state.
    // - Evidence: `src/model/RefrigerationSystem.hpp`, `src/model/RefrigerationSystem.cpp`,
    //   `resources/energyplus/ProposedEnergy+.idd`, and `src/epmodel/test/RefrigerationSystem_GTest.cpp`.
    // - Remaining Parity Work: Refrigerated load and transfer lists, condenser/compressor references, subcoolers, full family removal,
    //   and object-level clone behavior remain a separate refrigeration architecture phase.
    double minimumCondensingTemperature() const;
    bool setMinimumCondensingTemperature(double minimumCondensingTemperature);

    std::string refrigerationSystemWorkingFluidType() const;
    bool setRefrigerationSystemWorkingFluidType(const std::string& refrigerationSystemWorkingFluidType);

    std::string suctionTemperatureControlType() const;
    bool setSuctionTemperatureControlType(const std::string& suctionTemperatureControlType);
    bool isSuctionTemperatureControlTypeDefaulted() const;
    void resetSuctionTemperatureControlType();

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    bool isEndUseSubcategoryDefaulted() const;
    void resetEndUseSubcategory();

    std::string intercoolerType() const;
    bool setIntercoolerType(const std::string& intercoolerType);
    bool isIntercoolerTypeDefaulted() const;
    void resetIntercoolerType();

    double sumUASuctionPiping() const;
    bool setSumUASuctionPiping(double sumUASuctionPiping);
    bool isSumUASuctionPipingDefaulted() const;
    void resetSumUASuctionPiping();

    boost::optional<ThermalZone> suctionPipingZone() const;
    bool setSuctionPipingZone(const ThermalZone& thermalZone);
    void resetSuctionPipingZone();

    double shellandCoilIntercoolerEffectiveness() const;
    bool setShellandCoilIntercoolerEffectiveness(double shellandCoilIntercoolerEffectiveness);
    bool isShellandCoilIntercoolerEffectivenessDefaulted() const;
    void resetShellandCoilIntercoolerEffectiveness();

   protected:
    using ImplType = detail::RefrigerationSystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RefrigerationSystem(std::shared_ptr<detail::RefrigerationSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONSYSTEM_HPP
