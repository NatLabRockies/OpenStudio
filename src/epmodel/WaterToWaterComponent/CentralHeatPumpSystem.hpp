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

  /** \brief Represents a central heat pump system serving cooling, source, and heating plant loops.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-equipment.html#centralheatpumpsystem,CentralHeatPumpSystem}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CentralHeatPumpSystem</code>.
   *
   * - <b>Not yet available:</b> Module management methods
   *   <code>modules()</code>, <code>addModule(...)</code>,
   *   <code>removeModule(...)</code>, and <code>removeAllModules()</code>.
   *
   * \par Known limitations
   * The EPModel wrapper exposes the system-level fields and three plant-loop
   * views, but not the Model module-list graph.
   */
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
