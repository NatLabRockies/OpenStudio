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
    // - API: Preserve openstudio::model::HumidifierSteamElectric scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: Preserved scalar APIs map directly to E+ Humidifier:Steam:Electric fields Rated Capacity, Rated Power,
    //   Rated Fan Power, and Standby Power.
    // - ForwardTranslator evidence: ForwardTranslateHumidifierSteamElectric.cpp maps these exact model methods to matching E+ fields,
    //   including autosize handling for Rated Capacity and Rated Power.
    // - Field Mapping: Availability Schedule Name, Air Inlet/Outlet Node Name, and Water Storage Tank Name are relationship-like
    //   fields and are excluded from this scalar pass.
    // - TODO(parity): Add excluded relationship APIs in a dedicated relationship pass.
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
