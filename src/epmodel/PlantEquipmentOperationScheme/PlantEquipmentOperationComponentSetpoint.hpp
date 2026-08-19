/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONCOMPONENTSETPOINT_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONCOMPONENTSETPOINT_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationComponentSetpoint_Impl;
  }

  /** \brief Selects plant equipment for component setpoint operation.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentoperationcomponentsetpoint,PlantEquipmentOperation:ComponentSetpoint}
   *
   * \par Important behavior
   * The public <code>component1...</code> methods address only the first
   * extensible component row. Construction creates that row when needed and
   * initializes its flow rate and operation type.
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for <code>PlantEquipmentOperation:ComponentSetpoint</code>;
   * this wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * Equipment object/name and node-setpoint relationships and additional component rows are not exposed.
   * <code>autosizedComponent1FlowRate()</code> currently returns an empty optional even when the row is marked autosize.
   */
  class EPMODEL_API PlantEquipmentOperationComponentSetpoint : public PlantEquipmentOperationScheme
  {
   public:
    explicit PlantEquipmentOperationComponentSetpoint(const Model& model);

    virtual ~PlantEquipmentOperationComponentSetpoint() override = default;
    PlantEquipmentOperationComponentSetpoint(const PlantEquipmentOperationComponentSetpoint& other) = default;
    PlantEquipmentOperationComponentSetpoint(PlantEquipmentOperationComponentSetpoint&& other) = default;
    PlantEquipmentOperationComponentSetpoint& operator=(const PlantEquipmentOperationComponentSetpoint&) = default;
    PlantEquipmentOperationComponentSetpoint& operator=(PlantEquipmentOperationComponentSetpoint&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<double> component1FlowRate() const;
    bool setComponent1FlowRate(double component1FlowRate);
    bool isComponent1FlowRateAutosized() const;
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
