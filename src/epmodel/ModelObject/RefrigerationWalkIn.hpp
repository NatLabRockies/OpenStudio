/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONWALKIN_HPP
#define EPMODEL_REFRIGERATIONWALKIN_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RefrigerationWalkIn_Impl;
  }

  /** \brief RefrigerationWalkIn.
   *
   * \par EnergyPlus object
   * \epobject{group-refrigeration.html#refrigerationwalkin,Refrigeration:WalkIn}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::RefrigerationWalkIn</code>. The exposed scalar walk-in fields are available. Model's schedules, defrost-cycle parameters, and zone-boundary relationship APIs are not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API RefrigerationWalkIn : public ModelObject
  {
   public:
    explicit RefrigerationWalkIn(const Model& model);

    virtual ~RefrigerationWalkIn() override = default;
    RefrigerationWalkIn(const RefrigerationWalkIn& other) = default;
    RefrigerationWalkIn(RefrigerationWalkIn&& other) = default;
    RefrigerationWalkIn& operator=(const RefrigerationWalkIn&) = default;
    RefrigerationWalkIn& operator=(RefrigerationWalkIn&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> defrostTypeValues();
    static std::vector<std::string> defrostControlTypeValues();
    double ratedCoilCoolingCapacity() const;
    bool setRatedCoilCoolingCapacity(double ratedCoilCoolingCapacity);

    double operatingTemperature() const;
    bool setOperatingTemperature(double operatingTemperature);

    double ratedCoolingSourceTemperature() const;
    bool setRatedCoolingSourceTemperature(double ratedCoolingSourceTemperature);

    double ratedTotalHeatingPower() const;
    bool setRatedTotalHeatingPower(double ratedTotalHeatingPower);

    double ratedCoolingCoilFanPower() const;
    bool setRatedCoolingCoilFanPower(double ratedCoolingCoilFanPower);
    bool isRatedCoolingCoilFanPowerDefaulted() const;
    void resetRatedCoolingCoilFanPower();

    double ratedCirculationFanPower() const;
    bool setRatedCirculationFanPower(double ratedCirculationFanPower);
    bool isRatedCirculationFanPowerDefaulted() const;
    void resetRatedCirculationFanPower();

    double ratedTotalLightingPower() const;
    bool setRatedTotalLightingPower(double ratedTotalLightingPower);

    std::string defrostType() const;
    bool setDefrostType(const std::string& defrostType);
    bool isDefrostTypeDefaulted() const;
    void resetDefrostType();

    std::string defrostControlType() const;
    bool setDefrostControlType(const std::string& defrostControlType);
    bool isDefrostControlTypeDefaulted() const;
    void resetDefrostControlType();

    boost::optional<double> defrostPower() const;
    bool setDefrostPower(double defrostPower);
    void resetDefrostPower();

    boost::optional<double> temperatureTerminationDefrostFractiontoIce() const;
    bool setTemperatureTerminationDefrostFractiontoIce(double temperatureTerminationDefrostFractiontoIce);
    void resetTemperatureTerminationDefrostFractiontoIce();

    double averageRefrigerantChargeInventory() const;
    bool setAverageRefrigerantChargeInventory(double averageRefrigerantChargeInventory);
    bool isAverageRefrigerantChargeInventoryDefaulted() const;
    void resetAverageRefrigerantChargeInventory();

    double insulatedFloorSurfaceArea() const;
    bool setInsulatedFloorSurfaceArea(double insulatedFloorSurfaceArea);

    double insulatedFloorUValue() const;
    bool setInsulatedFloorUValue(double insulatedFloorUValue);
    bool isInsulatedFloorUValueDefaulted() const;
    void resetInsulatedFloorUValue();

   protected:
    using ImplType = detail::RefrigerationWalkIn_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RefrigerationWalkIn(std::shared_ptr<detail::RefrigerationWalkIn_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONWALKIN_HPP
