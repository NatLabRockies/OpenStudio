/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CENTRALHEATPUMPSYSTEM_HPP
#define EPMODEL_CENTRALHEATPUMPSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class CentralHeatPumpSystem_Impl;
  }

  class EPMODEL_API CentralHeatPumpSystem : public WaterToWaterComponent
  {
   public:
    explicit CentralHeatPumpSystem(const Model& model);

    virtual ~CentralHeatPumpSystem() override = default;
    CentralHeatPumpSystem(const CentralHeatPumpSystem& other) = default;
    CentralHeatPumpSystem(CentralHeatPumpSystem&& other) = default;
    CentralHeatPumpSystem& operator=(const CentralHeatPumpSystem&) = default;
    CentralHeatPumpSystem& operator=(CentralHeatPumpSystem&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlMethodValues();

    // Schema Alignment Notes:
    // - Status: Near Parity. The scalar, ancillary-schedule, and three-loop convenience surface is aligned, while the module-list graph remains outside current epmodel scope.
    // - Canonical Counterpart: openstudio::model::CentralHeatPumpSystem.
    // - Implemented Parity: `controlMethod`, `ancillaryPower`, ancillary-operation schedule, cooling/source/heating loop conveniences, and three-loop attachment behavior preserve the main canonical wrapper behavior that epmodel can support directly.
    // - Documented Delta: Module-list/module-object APIs remain omitted because epmodel does not yet model `CentralHeatPumpSystemModule` or `ModelObjectList`.
    // - Field/Storage Mapping: Scalar and schedule wrappers map directly to EnergyPlus `CentralHeatPumpSystem` fields while the three loop ports continue to use the shared water-to-water topology layer.
    // - Evidence: `src/model/CentralHeatPumpSystem.hpp`, `src/model/CentralHeatPumpSystem.cpp`, and the matching forward translator for this type.
    // - Remaining Parity Work: Add the omitted module-list graph only once epmodel gains the missing supporting object families.
    /** @name ControlMethod */
    //@{
    std::string controlMethod() const;
    bool setControlMethod(const std::string& controlMethod);
    //@}

    /** @name AncillaryPower */
    //@{
    double ancillaryPower() const;
    bool setAncillaryPower(double ancillaryPower);
    //@}

    boost::optional<Schedule> ancillaryOperationSchedule() const;
    bool setAncillaryOperationSchedule(Schedule& schedule);
    void resetAncillaryOperationSchedule();

    boost::optional<PlantLoop> coolingPlantLoop() const;
    boost::optional<PlantLoop> sourcePlantLoop() const;
    boost::optional<PlantLoop> heatingPlantLoop() const;

   protected:
    using ImplType = detail::CentralHeatPumpSystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CentralHeatPumpSystem(std::shared_ptr<detail::CentralHeatPumpSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
