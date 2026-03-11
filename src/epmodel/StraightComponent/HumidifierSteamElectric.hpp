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

  boost::optional<double> ratedPower() const;
  bool isRatedPowerAutosized() const;

  boost::optional<double> ratedFanPower() const;

  boost::optional<double> standbyPower() const;

  bool setRatedCapacity(double ratedCapacity);
  void autosizeRatedCapacity();

  bool setRatedPower(double ratedPower);
  void resetRatedPower();
  void autosizeRatedPower();

  bool setRatedFanPower(double ratedFanPower);
  void resetRatedFanPower();

  bool setStandbyPower(double standbyPower);
  void resetStandbyPower();

  boost::optional<double> autosizedRatedCapacity() const;
  boost::optional<double> autosizedRatedPower() const;

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
