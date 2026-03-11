/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRSETTINGSUNDERFLOORAIRDISTRIBUTIONINTERIOR_HPP
#define EPMODEL_ROOMAIRSETTINGSUNDERFLOORAIRDISTRIBUTIONINTERIOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class RoomAirSettingsUnderFloorAirDistributionInterior_Impl;
}

class EPMODEL_API RoomAirSettingsUnderFloorAirDistributionInterior : public ModelObject
{
 public:
  explicit RoomAirSettingsUnderFloorAirDistributionInterior(const Model& model);

  virtual ~RoomAirSettingsUnderFloorAirDistributionInterior() override = default;
  RoomAirSettingsUnderFloorAirDistributionInterior(const RoomAirSettingsUnderFloorAirDistributionInterior& other) = default;
  RoomAirSettingsUnderFloorAirDistributionInterior(RoomAirSettingsUnderFloorAirDistributionInterior&& other) = default;
  RoomAirSettingsUnderFloorAirDistributionInterior& operator=(const RoomAirSettingsUnderFloorAirDistributionInterior&) = default;
  RoomAirSettingsUnderFloorAirDistributionInterior& operator=(RoomAirSettingsUnderFloorAirDistributionInterior&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> floorDiffuserTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class and accessor naming.
  // - Field Mapping: Scalar accessors map directly to EnergyPlus
  //   RoomAirSettings:UnderFloorAirDistributionInterior scalar fields.
  // - Field Mapping: Zone Name is an object-list relationship field and intentionally excluded from scalar accessors
  //   in this scaffold pass.
  // - Field Mapping: Name remains available via ModelObject base name APIs.
  // - TODO(parity): Add typed relationship APIs for excluded fields after scalar saturation.
  boost::optional<double> numberofDiffusers() const;
  bool isNumberofDiffusersDefaulted() const;
  bool isNumberofDiffusersAutocalculated() const;
  bool setNumberofDiffusers(double numberofDiffusers);
  void resetNumberofDiffusers();
  void autocalculateNumberofDiffusers();

  boost::optional<double> powerperPlume() const;
  bool isPowerperPlumeDefaulted() const;
  bool isPowerperPlumeAutocalculated() const;
  bool setPowerperPlume(double powerperPlume);
  void resetPowerperPlume();
  void autocalculatePowerperPlume();

  boost::optional<double> designEffectiveAreaofDiffuser() const;
  bool isDesignEffectiveAreaofDiffuserDefaulted() const;
  bool isDesignEffectiveAreaofDiffuserAutocalculated() const;
  bool setDesignEffectiveAreaofDiffuser(double designEffectiveAreaofDiffuser);
  void resetDesignEffectiveAreaofDiffuser();
  void autocalculateDesignEffectiveAreaofDiffuser();

  boost::optional<double> diffuserSlotAnglefromVertical() const;
  bool isDiffuserSlotAnglefromVerticalDefaulted() const;
  bool isDiffuserSlotAnglefromVerticalAutocalculated() const;
  bool setDiffuserSlotAnglefromVertical(double diffuserSlotAnglefromVertical);
  void resetDiffuserSlotAnglefromVertical();
  void autocalculateDiffuserSlotAnglefromVertical();

  double thermostatHeight() const;
  bool isThermostatHeightDefaulted() const;
  bool setThermostatHeight(double thermostatHeight);
  void resetThermostatHeight();

  double comfortHeight() const;
  bool isComfortHeightDefaulted() const;
  bool setComfortHeight(double comfortHeight);
  void resetComfortHeight();

  double temperatureDifferenceThresholdforReporting() const;
  bool isTemperatureDifferenceThresholdforReportingDefaulted() const;
  bool setTemperatureDifferenceThresholdforReporting(double temperatureDifferenceThresholdforReporting);
  void resetTemperatureDifferenceThresholdforReporting();

  std::string floorDiffuserType() const;
  bool isFloorDiffuserTypeDefaulted() const;
  bool setFloorDiffuserType(const std::string& floorDiffuserType);
  void resetFloorDiffuserType();

  boost::optional<double> transitionHeight() const;
  bool isTransitionHeightDefaulted() const;
  bool isTransitionHeightAutocalculated() const;
  bool setTransitionHeight(double transitionHeight);
  void resetTransitionHeight();
  void autocalculateTransitionHeight();

  boost::optional<double> coefficientA() const;
  bool isCoefficientADefaulted() const;
  bool isCoefficientAAutocalculated() const;
  bool setCoefficientA(
    double coefficientA);
  void resetCoefficientA();
  void autocalculateCoefficientA();

  boost::optional<double> coefficientB() const;
  bool isCoefficientBDefaulted() const;
  bool isCoefficientBAutocalculated() const;
  bool setCoefficientB(
    double coefficientB);
  void resetCoefficientB();
  void autocalculateCoefficientB();

  boost::optional<double> coefficientC() const;
  bool isCoefficientCDefaulted() const;
  bool isCoefficientCAutocalculated() const;
  bool setCoefficientC(
    double coefficientC);
  void resetCoefficientC();
  void autocalculateCoefficientC();

  boost::optional<double> coefficientD() const;
  bool isCoefficientDDefaulted() const;
  bool isCoefficientDAutocalculated() const;
  bool setCoefficientD(
    double coefficientD);
  void resetCoefficientD();
  void autocalculateCoefficientD();

  boost::optional<double> coefficientE() const;
  bool isCoefficientEDefaulted() const;
  bool isCoefficientEAutocalculated() const;
  bool setCoefficientE(
    double coefficientE);
  void resetCoefficientE();
  void autocalculateCoefficientE();

 protected:
  using ImplType = detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit RoomAirSettingsUnderFloorAirDistributionInterior(std::shared_ptr<detail::RoomAirSettingsUnderFloorAirDistributionInterior_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
