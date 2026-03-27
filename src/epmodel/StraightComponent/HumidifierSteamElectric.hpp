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
    // - Status: Scalar Parity. The canonical steam-electric humidifier scalar surface is present, while schedule, node, and storage-tank helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::HumidifierSteamElectric.
    // - Implemented Parity: The preserved scalar API matches the rated-capacity, rated-power, fan-power, and standby-power accessors with matching autosize/default behavior.
    // - Documented Delta: Availability schedule, inlet/outlet node, and water-storage-tank helpers remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `Humidifier:Steam:Electric` scalar fields used by the forward translator.
    // - Evidence: `src/model/HumidifierSteamElectric.hpp`, `src/model/HumidifierSteamElectric.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHumidifierSteamElectric.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
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
