/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HUMIDIFIERSTEAMELECTRIC_HPP
#define EPMODEL_HUMIDIFIERSTEAMELECTRIC_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class HumidifierSteamElectric_Impl;
  }

/** \brief An electric steam humidifier.
 *
 * \par EnergyPlus object
 * \epobject{group-humidifiers-and-dehumidifiers.html#humidifiersteamelectric,Humidifier:Steam:Electric}
 *
 * \par Important behavior
 * Availability, node, capacity, efficiency, and water-use fields map directly to Humidifier:Steam:Electric.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::HumidifierSteamElectric</code>.
 *
 * \par Known limitations
 * No additional type-specific limitation is known beyond shared straight-component topology.
 */
  class EPMODEL_API HumidifierSteamElectric : public StraightComponent
  {
   public:
    explicit HumidifierSteamElectric(const Model& model);

    virtual ~HumidifierSteamElectric() override = default;
    HumidifierSteamElectric(const HumidifierSteamElectric& other) = default;
    HumidifierSteamElectric(HumidifierSteamElectric&& other) = default;
    HumidifierSteamElectric& operator=(const HumidifierSteamElectric&) = default;
    HumidifierSteamElectric& operator=(HumidifierSteamElectric&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    boost::optional<double> ratedCapacity() const;
    bool isRatedCapacityAutosized() const;
    bool setRatedCapacity(double ratedCapacity);
    void autosizeRatedCapacity();
    boost::optional<double> autosizedRatedCapacity() const;

    boost::optional<double> ratedPower() const;
    bool isRatedPowerAutosized() const;
    bool setRatedPower(double ratedPower);
    void resetRatedPower();
    void autosizeRatedPower();
    boost::optional<double> autosizedRatedPower() const;

    boost::optional<double> ratedFanPower() const;
    bool setRatedFanPower(double ratedFanPower);
    void resetRatedFanPower();

    boost::optional<double> standbyPower() const;
    bool setStandbyPower(double standbyPower);
    void resetStandbyPower();

   protected:
    using ImplType = detail::HumidifierSteamElectric_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HumidifierSteamElectric(std::shared_ptr<detail::HumidifierSteamElectric_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
