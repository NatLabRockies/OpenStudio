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
    // - Status: Scalar Parity. The scalar control surface is aligned, but module, schedule, and loop-link behavior remains intentionally out of scope.
    // - Canonical Counterpart: openstudio::model::CentralHeatPumpSystem.
    // - Implemented Parity: `controlMethod` and `ancillaryPower` preserve the canonical model scalar API shape.
    // - Documented Delta: Ancillary schedule, node, and module-extensible APIs are omitted because this type still relies on the EnergyPlus-backed module graph for topology.
    // - Field/Storage Mapping: Scalar wrappers map directly to EnergyPlus `CentralHeatPumpSystem` control fields while the module structure remains storage-level connective tissue.
    // - Evidence: `src/model/CentralHeatPumpSystem.hpp`, `src/model/CentralHeatPumpSystem.cpp`, and the matching forward translator for this type.
    // - Remaining Parity Work: Add the omitted loop/module/schedule APIs once the non-scalar water-to-water topology layer is expanded.
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
