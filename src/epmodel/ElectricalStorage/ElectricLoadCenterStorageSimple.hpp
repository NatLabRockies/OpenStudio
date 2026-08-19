/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERSTORAGESIMPLE_HPP
#define EPMODEL_ELECTRICLOADCENTERSTORAGESIMPLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ElectricLoadCenterStorageSimple_Impl;
  }

  /** \brief Represents a simple electrical storage device.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#electricloadcenterstoragesimple,ElectricLoadCenter:Storage:Simple}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ElectricLoadCenterStorageSimple</code>.
   *
   * - <b>Not yet available:</b> <code>availabilitySchedule()</code>,
   *   <code>isAvailabilityScheduleDefaulted()</code>,
   *   <code>setAvailabilitySchedule(...)</code>, and
   *   <code>resetAvailabilitySchedule()</code>.
   * - <b>Not yet available:</b> The Model ElectricalStorage relationship
   *   methods <code>electricLoadCenterDistribution()</code>,
   *   <code>thermalZone()</code>, <code>setThermalZone(...)</code>, and
   *   <code>resetThermalZone()</code>.
   *
   * \par Known limitations
   * Assign schedule, electric-load-center, and thermal-zone relationships
   * through lower-level object references when needed.
   */
  class EPMODEL_API ElectricLoadCenterStorageSimple : public ModelObject
  {
   public:
    explicit ElectricLoadCenterStorageSimple(const Model& model);

    virtual ~ElectricLoadCenterStorageSimple() override = default;
    ElectricLoadCenterStorageSimple(const ElectricLoadCenterStorageSimple& other) = default;
    ElectricLoadCenterStorageSimple(ElectricLoadCenterStorageSimple&& other) = default;
    ElectricLoadCenterStorageSimple& operator=(const ElectricLoadCenterStorageSimple&) = default;
    ElectricLoadCenterStorageSimple& operator=(ElectricLoadCenterStorageSimple&&) = default;

    static IddObjectType iddObjectType();

    double radiativeFractionforZoneHeatGains() const;
    bool isRadiativeFractionforZoneHeatGainsDefaulted() const;
    bool setRadiativeFractionforZoneHeatGains(double radiativeFractionforZoneHeatGains);
    void resetRadiativeFractionforZoneHeatGains();

    double nominalEnergeticEfficiencyforCharging() const;
    bool isNominalEnergeticEfficiencyforChargingDefaulted() const;
    bool setNominalEnergeticEfficiencyforCharging(double nominalEnergeticEfficiencyforCharging);
    void resetNominalEnergeticEfficiencyforCharging();

    double nominalDischargingEnergeticEfficiency() const;
    bool isNominalDischargingEnergeticEfficiencyDefaulted() const;
    bool setNominalDischargingEnergeticEfficiency(double nominalDischargingEnergeticEfficiency);
    void resetNominalDischargingEnergeticEfficiency();

    double maximumStorageCapacity() const;
    bool setMaximumStorageCapacity(double maximumStorageCapacity);

    double maximumPowerforDischarging() const;
    bool setMaximumPowerforDischarging(double maximumPowerforDischarging);

    double maximumPowerforCharging() const;
    bool setMaximumPowerforCharging(double maximumPowerforCharging);

    double initialStateofCharge() const;
    bool isInitialStateofChargeDefaulted() const;
    bool setInitialStateofCharge(double initialStateofCharge);
    void resetInitialStateofCharge();

   protected:
    using ImplType = detail::ElectricLoadCenterStorageSimple_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ElectricLoadCenterStorageSimple(std::shared_ptr<detail::ElectricLoadCenterStorageSimple_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
