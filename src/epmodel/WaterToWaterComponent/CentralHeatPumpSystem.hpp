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
    // - API: Preserves openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: controlMethod and ancillaryPower map directly to E+ CentralHeatPumpSystem ControlMethod/AncillaryPower.
    // - Field Mapping: AncillaryOperationScheduleName, node fields, and module extensibles are relationship-like and intentionally excluded.
    // - TODO(parity): Add non-scalar loop/module/schedule behavior incrementally after scalar saturation.
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
