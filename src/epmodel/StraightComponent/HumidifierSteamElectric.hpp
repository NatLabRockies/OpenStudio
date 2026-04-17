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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical steam-electric humidifier preserves the scalar and availability-schedule surface, while the storage-tank helper remains out of scope and `addToNode` parity stays intentionally narrowed.
    // - Canonical Counterpart: openstudio::model::HumidifierSteamElectric.
    // - Implemented Parity: `availabilitySchedule`, `setAvailabilitySchedule`, and `resetAvailabilitySchedule` preserve the canonical schedule relationship,
    //   rated-capacity and rated-power preserve the canonical optional/default/autosize behavior, and rated-fan-power plus standby-power preserve the
    //   canonical optional scalar behavior used by the forward translator.
    // - Documented Delta: The wrapper currently relies on inherited inlet/outlet model-object helpers, matching the canonical wrapper today; the
    //   water-storage-tank helper remains intentionally omitted, autosized-result queries still return `boost::none` until epmodel sizing results exist,
    //   and `addToNode` remains intentionally narrower than canonical behavior by accepting only air-loop supply placement plus OA-system outboard OA/relief nodes.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `Humidifier:Steam:Electric` fields used by the forward translator.
    // - Evidence: `src/model/HumidifierSteamElectric.hpp`, `src/model/HumidifierSteamElectric.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHumidifierSteamElectric.cpp`.
    // - Remaining Parity Work: Restore broader canonical `addToNode` parity if this family is widened beyond the current supply/OA-only guardrails, add the
    //   omitted water-storage-tank helper if that relationship is surfaced in epmodel, and resolve real autosized-result values once epmodel sizing results exist.
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
