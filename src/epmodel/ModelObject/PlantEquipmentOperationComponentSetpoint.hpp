/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONCOMPONENTSETPOINT_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONCOMPONENTSETPOINT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationComponentSetpoint_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationComponentSetpoint : public ModelObject
  {
   public:
    explicit PlantEquipmentOperationComponentSetpoint(const Model& model);

    virtual ~PlantEquipmentOperationComponentSetpoint() override = default;
    PlantEquipmentOperationComponentSetpoint(const PlantEquipmentOperationComponentSetpoint& other) = default;
    PlantEquipmentOperationComponentSetpoint(PlantEquipmentOperationComponentSetpoint&& other) = default;
    PlantEquipmentOperationComponentSetpoint& operator=(const PlantEquipmentOperationComponentSetpoint&) = default;
    PlantEquipmentOperationComponentSetpoint& operator=(PlantEquipmentOperationComponentSetpoint&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type exposes the first Component entry's simple scalars and keeps IDD-derived naming to honor the contract.
    // - Field Mapping: Component 1 Flow Rate and Operation 1 Type map directly to their EnergyPlus fields in PlantEquipmentOperation:ComponentSetpoint.
    // - Field Mapping: Equipment Object Type/Name and node-setpoint references are relationship-like fields inside the extensible group and intentionally excluded in this scalar-only pass.
    // - TODO(parity): Add typed group helpers once relationship APIs or full extensible handling becomes required.
    boost::optional<double> component1FlowRate() const;
    bool isComponent1FlowRateAutosized() const;
    bool setComponent1FlowRate(double component1FlowRate);
    void autosizeComponent1FlowRate();
    boost::optional<double> autosizedComponent1FlowRate() const;

    std::string component1OperationType() const;
    bool setComponent1OperationType(const std::string& component1OperationType);
    static std::vector<std::string> component1OperationTypeValues();

   protected:
    using ImplType = detail::PlantEquipmentOperationComponentSetpoint_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationComponentSetpoint(std::shared_ptr<detail::PlantEquipmentOperationComponentSetpoint_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
