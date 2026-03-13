/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/MaterialPropertyPhaseChangeHysteresis.hpp"
#include "ModelObject/MaterialPropertyPhaseChangeHysteresis_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/MaterialProperty_PhaseChangeHysteresis_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  MaterialPropertyPhaseChangeHysteresis::MaterialPropertyPhaseChangeHysteresis(const Model& model)
    : ModelObject(MaterialPropertyPhaseChangeHysteresis::iddObjectType(), model) {}

  MaterialPropertyPhaseChangeHysteresis::MaterialPropertyPhaseChangeHysteresis(
    std::shared_ptr<detail::MaterialPropertyPhaseChangeHysteresis_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType MaterialPropertyPhaseChangeHysteresis::iddObjectType() {
    return IddObjectType::MaterialProperty_PhaseChangeHysteresis;
  }

  double MaterialPropertyPhaseChangeHysteresis::latentHeatduringtheEntirePhaseChangeProcess() const {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->latentHeatduringtheEntirePhaseChangeProcess();
  }

  bool MaterialPropertyPhaseChangeHysteresis::setLatentHeatduringtheEntirePhaseChangeProcess(double latentHeatduringtheEntirePhaseChangeProcess) {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->setLatentHeatduringtheEntirePhaseChangeProcess(
      latentHeatduringtheEntirePhaseChangeProcess);
  }

  double MaterialPropertyPhaseChangeHysteresis::liquidStateThermalConductivity() const {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->liquidStateThermalConductivity();
  }

  bool MaterialPropertyPhaseChangeHysteresis::setLiquidStateThermalConductivity(double liquidStateThermalConductivity) {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->setLiquidStateThermalConductivity(liquidStateThermalConductivity);
  }

  double MaterialPropertyPhaseChangeHysteresis::liquidStateDensity() const {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->liquidStateDensity();
  }

  bool MaterialPropertyPhaseChangeHysteresis::setLiquidStateDensity(double liquidStateDensity) {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->setLiquidStateDensity(liquidStateDensity);
  }

  double MaterialPropertyPhaseChangeHysteresis::liquidStateSpecificHeat() const {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->liquidStateSpecificHeat();
  }

  bool MaterialPropertyPhaseChangeHysteresis::setLiquidStateSpecificHeat(double liquidStateSpecificHeat) {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->setLiquidStateSpecificHeat(liquidStateSpecificHeat);
  }

  double MaterialPropertyPhaseChangeHysteresis::highTemperatureDifferenceofMeltingCurve() const {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->highTemperatureDifferenceofMeltingCurve();
  }

  bool MaterialPropertyPhaseChangeHysteresis::setHighTemperatureDifferenceofMeltingCurve(double highTemperatureDifferenceofMeltingCurve) {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->setHighTemperatureDifferenceofMeltingCurve(
      highTemperatureDifferenceofMeltingCurve);
  }

  double MaterialPropertyPhaseChangeHysteresis::peakMeltingTemperature() const {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->peakMeltingTemperature();
  }

  bool MaterialPropertyPhaseChangeHysteresis::setPeakMeltingTemperature(double peakMeltingTemperature) {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->setPeakMeltingTemperature(peakMeltingTemperature);
  }

  double MaterialPropertyPhaseChangeHysteresis::lowTemperatureDifferenceofMeltingCurve() const {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->lowTemperatureDifferenceofMeltingCurve();
  }

  bool MaterialPropertyPhaseChangeHysteresis::setLowTemperatureDifferenceofMeltingCurve(double lowTemperatureDifferenceofMeltingCurve) {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->setLowTemperatureDifferenceofMeltingCurve(
      lowTemperatureDifferenceofMeltingCurve);
  }

  double MaterialPropertyPhaseChangeHysteresis::solidStateThermalConductivity() const {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->solidStateThermalConductivity();
  }

  bool MaterialPropertyPhaseChangeHysteresis::setSolidStateThermalConductivity(double solidStateThermalConductivity) {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->setSolidStateThermalConductivity(solidStateThermalConductivity);
  }

  double MaterialPropertyPhaseChangeHysteresis::solidStateDensity() const {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->solidStateDensity();
  }

  bool MaterialPropertyPhaseChangeHysteresis::setSolidStateDensity(double solidStateDensity) {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->setSolidStateDensity(solidStateDensity);
  }

  double MaterialPropertyPhaseChangeHysteresis::solidStateSpecificHeat() const {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->solidStateSpecificHeat();
  }

  bool MaterialPropertyPhaseChangeHysteresis::setSolidStateSpecificHeat(double solidStateSpecificHeat) {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->setSolidStateSpecificHeat(solidStateSpecificHeat);
  }

  double MaterialPropertyPhaseChangeHysteresis::highTemperatureDifferenceofFreezingCurve() const {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->highTemperatureDifferenceofFreezingCurve();
  }

  bool MaterialPropertyPhaseChangeHysteresis::setHighTemperatureDifferenceofFreezingCurve(double highTemperatureDifferenceofFreezingCurve) {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->setHighTemperatureDifferenceofFreezingCurve(
      highTemperatureDifferenceofFreezingCurve);
  }

  double MaterialPropertyPhaseChangeHysteresis::peakFreezingTemperature() const {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->peakFreezingTemperature();
  }

  bool MaterialPropertyPhaseChangeHysteresis::setPeakFreezingTemperature(double peakFreezingTemperature) {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->setPeakFreezingTemperature(peakFreezingTemperature);
  }

  double MaterialPropertyPhaseChangeHysteresis::lowTemperatureDifferenceofFreezingCurve() const {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->lowTemperatureDifferenceofFreezingCurve();
  }

  bool MaterialPropertyPhaseChangeHysteresis::setLowTemperatureDifferenceofFreezingCurve(double lowTemperatureDifferenceofFreezingCurve) {
    return getImpl<detail::MaterialPropertyPhaseChangeHysteresis_Impl>()->setLowTemperatureDifferenceofFreezingCurve(
      lowTemperatureDifferenceofFreezingCurve);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double MaterialPropertyPhaseChangeHysteresis_Impl::latentHeatduringtheEntirePhaseChangeProcess() const {
      const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::LatentHeatduringtheEntirePhaseChangeProcess, true);
      OS_ASSERT(value);
      return *value;
    }

    bool
      MaterialPropertyPhaseChangeHysteresis_Impl::setLatentHeatduringtheEntirePhaseChangeProcess(double latentHeatduringtheEntirePhaseChangeProcess) {
      const bool result = setDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::LatentHeatduringtheEntirePhaseChangeProcess,
                                    latentHeatduringtheEntirePhaseChangeProcess);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyPhaseChangeHysteresis_Impl::liquidStateThermalConductivity() const {
      const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::LiquidStateThermalConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyPhaseChangeHysteresis_Impl::setLiquidStateThermalConductivity(double liquidStateThermalConductivity) {
      const bool result =
        setDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::LiquidStateThermalConductivity, liquidStateThermalConductivity);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyPhaseChangeHysteresis_Impl::liquidStateDensity() const {
      const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::LiquidStateDensity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyPhaseChangeHysteresis_Impl::setLiquidStateDensity(double liquidStateDensity) {
      const bool result = setDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::LiquidStateDensity, liquidStateDensity);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyPhaseChangeHysteresis_Impl::liquidStateSpecificHeat() const {
      const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::LiquidStateSpecificHeat, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyPhaseChangeHysteresis_Impl::setLiquidStateSpecificHeat(double liquidStateSpecificHeat) {
      const bool result = setDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::LiquidStateSpecificHeat, liquidStateSpecificHeat);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyPhaseChangeHysteresis_Impl::highTemperatureDifferenceofMeltingCurve() const {
      const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::HighTemperatureDifferenceofMeltingCurve, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyPhaseChangeHysteresis_Impl::setHighTemperatureDifferenceofMeltingCurve(double highTemperatureDifferenceofMeltingCurve) {
      const bool result = setDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::HighTemperatureDifferenceofMeltingCurve,
                                    highTemperatureDifferenceofMeltingCurve);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyPhaseChangeHysteresis_Impl::peakMeltingTemperature() const {
      const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::PeakMeltingTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyPhaseChangeHysteresis_Impl::setPeakMeltingTemperature(double peakMeltingTemperature) {
      const bool result = setDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::PeakMeltingTemperature, peakMeltingTemperature);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyPhaseChangeHysteresis_Impl::lowTemperatureDifferenceofMeltingCurve() const {
      const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::LowTemperatureDifferenceofMeltingCurve, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyPhaseChangeHysteresis_Impl::setLowTemperatureDifferenceofMeltingCurve(double lowTemperatureDifferenceofMeltingCurve) {
      const bool result = setDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::LowTemperatureDifferenceofMeltingCurve,
                                    lowTemperatureDifferenceofMeltingCurve);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyPhaseChangeHysteresis_Impl::solidStateThermalConductivity() const {
      const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::SolidStateThermalConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyPhaseChangeHysteresis_Impl::setSolidStateThermalConductivity(double solidStateThermalConductivity) {
      const bool result =
        setDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::SolidStateThermalConductivity, solidStateThermalConductivity);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyPhaseChangeHysteresis_Impl::solidStateDensity() const {
      const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::SolidStateDensity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyPhaseChangeHysteresis_Impl::setSolidStateDensity(double solidStateDensity) {
      const bool result = setDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::SolidStateDensity, solidStateDensity);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyPhaseChangeHysteresis_Impl::solidStateSpecificHeat() const {
      const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::SolidStateSpecificHeat, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyPhaseChangeHysteresis_Impl::setSolidStateSpecificHeat(double solidStateSpecificHeat) {
      const bool result = setDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::SolidStateSpecificHeat, solidStateSpecificHeat);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyPhaseChangeHysteresis_Impl::highTemperatureDifferenceofFreezingCurve() const {
      const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::HighTemperatureDifferenceofFreezingCurve, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyPhaseChangeHysteresis_Impl::setHighTemperatureDifferenceofFreezingCurve(double highTemperatureDifferenceofFreezingCurve) {
      const bool result = setDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::HighTemperatureDifferenceofFreezingCurve,
                                    highTemperatureDifferenceofFreezingCurve);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyPhaseChangeHysteresis_Impl::peakFreezingTemperature() const {
      const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::PeakFreezingTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyPhaseChangeHysteresis_Impl::setPeakFreezingTemperature(double peakFreezingTemperature) {
      const bool result = setDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::PeakFreezingTemperature, peakFreezingTemperature);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyPhaseChangeHysteresis_Impl::lowTemperatureDifferenceofFreezingCurve() const {
      const auto value = getDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::LowTemperatureDifferenceofFreezingCurve, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyPhaseChangeHysteresis_Impl::setLowTemperatureDifferenceofFreezingCurve(double lowTemperatureDifferenceofFreezingCurve) {
      const bool result = setDouble(openstudio::MaterialProperty_PhaseChangeHysteresisFields::LowTemperatureDifferenceofFreezingCurve,
                                    lowTemperatureDifferenceofFreezingCurve);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
