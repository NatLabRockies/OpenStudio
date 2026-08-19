/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERPANELRADIANT_HPP
#define EPMODEL_COILCOOLINGWATERPANELRADIANT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class CoilCoolingWaterPanelRadiant_Impl;
  }

  /** \brief Represents a cooling-coil view of a radiant-convective water panel.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object. EPModel projects <code>OS:Coil:Cooling:Water:Panel:Radiant</code> onto \epobject{group-radiative-convective-units.html#zonehvaccoolingpanelradiantconvectivewater,ZoneHVAC:CoolingPanel:RadiantConvective:Water} parent storage.
   *
   * \par Important behavior
   * This transient child writes its scalar and schedule fields through to parent-owned storage and maps its water
   * ports to the parent's <code>Water Inlet Node Name</code> and <code>Water Outlet Node Name</code> fields.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilCoolingWaterPanelRadiant</code>. <b>Changed:</b> the child is transient and cannot be persisted or placed independently as a plant component. EPModel additionally exposes explicit default-state queries for the parent-backed EnergyPlus fields.
   * \par Known limitations
   * Use the owning parent object for persistence and complete topology.
   */
  class EPMODEL_API CoilCoolingWaterPanelRadiant : public StraightComponent
  {
   public:
    static constexpr bool is_transient = true;  // This is a Transient ModelObject

    explicit CoilCoolingWaterPanelRadiant(const Model& model);

    virtual ~CoilCoolingWaterPanelRadiant() override = default;
    CoilCoolingWaterPanelRadiant(const CoilCoolingWaterPanelRadiant& other) = default;
    CoilCoolingWaterPanelRadiant(CoilCoolingWaterPanelRadiant&& other) = default;
    CoilCoolingWaterPanelRadiant& operator=(const CoilCoolingWaterPanelRadiant&) = default;
    CoilCoolingWaterPanelRadiant& operator=(CoilCoolingWaterPanelRadiant&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> coolingDesignCapacityMethodValues();
    static std::vector<std::string> controlTypeValues();
    static std::vector<std::string> condensationControlTypeValues();

    double ratedInletWaterTemperature() const;
    bool isRatedInletWaterTemperatureDefaulted() const;
    bool setRatedInletWaterTemperature(double ratedInletWaterTemperature);
    void resetRatedInletWaterTemperature();

    double ratedInletSpaceTemperature() const;
    bool isRatedInletSpaceTemperatureDefaulted() const;
    bool setRatedInletSpaceTemperature(double ratedInletSpaceTemperature);
    void resetRatedInletSpaceTemperature();

    double ratedWaterMassFlowRate() const;
    bool isRatedWaterMassFlowRateDefaulted() const;
    bool setRatedWaterMassFlowRate(double ratedWaterMassFlowRate);
    void resetRatedWaterMassFlowRate();

    std::string coolingDesignCapacityMethod() const;
    bool isCoolingDesignCapacityMethodDefaulted() const;
    bool setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod);
    void resetCoolingDesignCapacityMethod();

    boost::optional<double> coolingDesignCapacity() const;
    bool isCoolingDesignCapacityAutosized() const;
    bool setCoolingDesignCapacity(double coolingDesignCapacity);
    void autosizeCoolingDesignCapacity();
    boost::optional<double> autosizedCoolingDesignCapacity() const;

    double coolingDesignCapacityPerFloorArea() const;
    bool setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea);

    double fractionofAutosizedCoolingDesignCapacity() const;
    bool setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity);

    boost::optional<double> maximumChilledWaterFlowRate() const;
    bool isMaximumChilledWaterFlowRateAutosized() const;
    bool setMaximumChilledWaterFlowRate(double maximumChilledWaterFlowRate);
    void autosizeMaximumChilledWaterFlowRate();
    boost::optional<double> autosizedMaximumChilledWaterFlowRate() const;

    std::string controlType() const;
    bool isControlTypeDefaulted() const;
    bool setControlType(const std::string& controlType);
    void resetControlType();

    double coolingControlThrottlingRange() const;
    bool isCoolingControlThrottlingRangeDefaulted() const;
    bool setCoolingControlThrottlingRange(double coolingControlThrottlingRange);
    void resetCoolingControlThrottlingRange();

    boost::optional<Schedule> coolingControlTemperatureSchedule() const;
    bool setCoolingControlTemperatureSchedule(Schedule& coolingControlTemperatureSchedule);
    void resetCoolingControlTemperatureSchedule();

    std::string condensationControlType() const;
    bool isCondensationControlTypeDefaulted() const;
    bool setCondensationControlType(const std::string& condensationControlType);
    void resetCondensationControlType();

    double condensationControlDewpointOffset() const;
    bool isCondensationControlDewpointOffsetDefaulted() const;
    bool setCondensationControlDewpointOffset(double condensationControlDewpointOffset);
    void resetCondensationControlDewpointOffset();

   protected:
    using ImplType = detail::CoilCoolingWaterPanelRadiant_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingWaterPanelRadiant(std::shared_ptr<detail::CoilCoolingWaterPanelRadiant_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
