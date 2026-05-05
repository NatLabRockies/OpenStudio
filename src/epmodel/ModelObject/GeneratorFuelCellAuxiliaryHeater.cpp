/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorFuelCellAuxiliaryHeater.hpp"
#include "GeneratorFuelCellAuxiliaryHeater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_FuelCell_AuxiliaryHeater_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  GeneratorFuelCellAuxiliaryHeater::GeneratorFuelCellAuxiliaryHeater(const Model& model)
    : ModelObject(GeneratorFuelCellAuxiliaryHeater::iddObjectType(), model) {}

  GeneratorFuelCellAuxiliaryHeater::GeneratorFuelCellAuxiliaryHeater(std::shared_ptr<detail::GeneratorFuelCellAuxiliaryHeater_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GeneratorFuelCellAuxiliaryHeater::iddObjectType() {
    return IddObjectType::Generator_FuelCell_AuxiliaryHeater;
  }

  std::vector<std::string> GeneratorFuelCellAuxiliaryHeater::skinLossDestinationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Generator_FuelCell_AuxiliaryHeaterFields::SkinLossDestination);
  }

  std::vector<std::string> GeneratorFuelCellAuxiliaryHeater::heatingCapacityUnitsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Generator_FuelCell_AuxiliaryHeaterFields::HeatingCapacityUnits);
  }

  double GeneratorFuelCellAuxiliaryHeater::excessAirRatio() const {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->excessAirRatio();
  }

  bool GeneratorFuelCellAuxiliaryHeater::setExcessAirRatio(double excessAirRatio) {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->setExcessAirRatio(excessAirRatio);
  }

  void GeneratorFuelCellAuxiliaryHeater::resetExcessAirRatio() {
    getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->resetExcessAirRatio();
  }

  double GeneratorFuelCellAuxiliaryHeater::ancillaryPowerConstantTerm() const {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->ancillaryPowerConstantTerm();
  }

  bool GeneratorFuelCellAuxiliaryHeater::setAncillaryPowerConstantTerm(double ancillaryPowerConstantTerm) {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->setAncillaryPowerConstantTerm(ancillaryPowerConstantTerm);
  }

  void GeneratorFuelCellAuxiliaryHeater::resetAncillaryPowerConstantTerm() {
    getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->resetAncillaryPowerConstantTerm();
  }

  double GeneratorFuelCellAuxiliaryHeater::ancillaryPowerLinearTerm() const {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->ancillaryPowerLinearTerm();
  }

  bool GeneratorFuelCellAuxiliaryHeater::setAncillaryPowerLinearTerm(double ancillaryPowerLinearTerm) {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->setAncillaryPowerLinearTerm(ancillaryPowerLinearTerm);
  }

  void GeneratorFuelCellAuxiliaryHeater::resetAncillaryPowerLinearTerm() {
    getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->resetAncillaryPowerLinearTerm();
  }

  double GeneratorFuelCellAuxiliaryHeater::skinLossUFactorTimesAreaValue() const {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->skinLossUFactorTimesAreaValue();
  }

  bool GeneratorFuelCellAuxiliaryHeater::setSkinLossUFactorTimesAreaValue(double skinLossUFactorTimesAreaValue) {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->setSkinLossUFactorTimesAreaValue(skinLossUFactorTimesAreaValue);
  }

  void GeneratorFuelCellAuxiliaryHeater::resetSkinLossUFactorTimesAreaValue() {
    getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->resetSkinLossUFactorTimesAreaValue();
  }

  std::string GeneratorFuelCellAuxiliaryHeater::skinLossDestination() const {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->skinLossDestination();
  }

  bool GeneratorFuelCellAuxiliaryHeater::setSkinLossDestination(const std::string& skinLossDestination) {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->setSkinLossDestination(skinLossDestination);
  }

  void GeneratorFuelCellAuxiliaryHeater::resetSkinLossDestination() {
    getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->resetSkinLossDestination();
  }

  std::string GeneratorFuelCellAuxiliaryHeater::heatingCapacityUnits() const {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->heatingCapacityUnits();
  }

  bool GeneratorFuelCellAuxiliaryHeater::setHeatingCapacityUnits(const std::string& heatingCapacityUnits) {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->setHeatingCapacityUnits(heatingCapacityUnits);
  }

  void GeneratorFuelCellAuxiliaryHeater::resetHeatingCapacityUnits() {
    getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->resetHeatingCapacityUnits();
  }

  double GeneratorFuelCellAuxiliaryHeater::maximumHeatingCapacityinWatts() const {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->maximumHeatingCapacityinWatts();
  }

  bool GeneratorFuelCellAuxiliaryHeater::setMaximumHeatingCapacityinWatts(double maximumHeatingCapacityinWatts) {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->setMaximumHeatingCapacityinWatts(maximumHeatingCapacityinWatts);
  }

  void GeneratorFuelCellAuxiliaryHeater::resetMaximumHeatingCapacityinWatts() {
    getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->resetMaximumHeatingCapacityinWatts();
  }

  double GeneratorFuelCellAuxiliaryHeater::minimumHeatingCapacityinWatts() const {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->minimumHeatingCapacityinWatts();
  }

  bool GeneratorFuelCellAuxiliaryHeater::setMinimumHeatingCapacityinWatts(double minimumHeatingCapacityinWatts) {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->setMinimumHeatingCapacityinWatts(minimumHeatingCapacityinWatts);
  }

  void GeneratorFuelCellAuxiliaryHeater::resetMinimumHeatingCapacityinWatts() {
    getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->resetMinimumHeatingCapacityinWatts();
  }

  double GeneratorFuelCellAuxiliaryHeater::maximumHeatingCapacityinKmolperSecond() const {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->maximumHeatingCapacityinKmolperSecond();
  }

  bool GeneratorFuelCellAuxiliaryHeater::setMaximumHeatingCapacityinKmolperSecond(double maximumHeatingCapacityinKmolperSecond) {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->setMaximumHeatingCapacityinKmolperSecond(maximumHeatingCapacityinKmolperSecond);
  }

  void GeneratorFuelCellAuxiliaryHeater::resetMaximumHeatingCapacityinKmolperSecond() {
    getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->resetMaximumHeatingCapacityinKmolperSecond();
  }

  double GeneratorFuelCellAuxiliaryHeater::minimumHeatingCapacityinKmolperSecond() const {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->minimumHeatingCapacityinKmolperSecond();
  }

  bool GeneratorFuelCellAuxiliaryHeater::setMinimumHeatingCapacityinKmolperSecond(double minimumHeatingCapacityinKmolperSecond) {
    return getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->setMinimumHeatingCapacityinKmolperSecond(minimumHeatingCapacityinKmolperSecond);
  }

  void GeneratorFuelCellAuxiliaryHeater::resetMinimumHeatingCapacityinKmolperSecond() {
    getImpl<detail::GeneratorFuelCellAuxiliaryHeater_Impl>()->resetMinimumHeatingCapacityinKmolperSecond();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double GeneratorFuelCellAuxiliaryHeater_Impl::excessAirRatio() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::ExcessAirRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAuxiliaryHeater_Impl::setExcessAirRatio(double excessAirRatio) {
      const bool result = setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::ExcessAirRatio, excessAirRatio);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellAuxiliaryHeater_Impl::resetExcessAirRatio() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::ExcessAirRatio, 0.0));
    }

    double GeneratorFuelCellAuxiliaryHeater_Impl::ancillaryPowerConstantTerm() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::AncillaryPowerConstantTerm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAuxiliaryHeater_Impl::setAncillaryPowerConstantTerm(double ancillaryPowerConstantTerm) {
      const bool result = setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::AncillaryPowerConstantTerm, ancillaryPowerConstantTerm);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellAuxiliaryHeater_Impl::resetAncillaryPowerConstantTerm() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::AncillaryPowerConstantTerm, 0.0));
    }

    double GeneratorFuelCellAuxiliaryHeater_Impl::ancillaryPowerLinearTerm() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::AncillaryPowerLinearTerm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAuxiliaryHeater_Impl::setAncillaryPowerLinearTerm(double ancillaryPowerLinearTerm) {
      const bool result = setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::AncillaryPowerLinearTerm, ancillaryPowerLinearTerm);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellAuxiliaryHeater_Impl::resetAncillaryPowerLinearTerm() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::AncillaryPowerLinearTerm, 0.0));
    }

    double GeneratorFuelCellAuxiliaryHeater_Impl::skinLossUFactorTimesAreaValue() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::SkinLossUFactorTimesAreaValue, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAuxiliaryHeater_Impl::setSkinLossUFactorTimesAreaValue(double skinLossUFactorTimesAreaValue) {
      const bool result =
        setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::SkinLossUFactorTimesAreaValue, skinLossUFactorTimesAreaValue);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellAuxiliaryHeater_Impl::resetSkinLossUFactorTimesAreaValue() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::SkinLossUFactorTimesAreaValue, 0.5));
    }

    std::string GeneratorFuelCellAuxiliaryHeater_Impl::skinLossDestination() const {
      const auto value = getString(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::SkinLossDestination, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAuxiliaryHeater_Impl::setSkinLossDestination(const std::string& skinLossDestination) {
      return setString(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::SkinLossDestination, skinLossDestination);
    }

    void GeneratorFuelCellAuxiliaryHeater_Impl::resetSkinLossDestination() {
      OS_ASSERT(setString(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::SkinLossDestination, "AirInletForFuelCell"));
    }

    std::string GeneratorFuelCellAuxiliaryHeater_Impl::heatingCapacityUnits() const {
      const auto value = getString(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::HeatingCapacityUnits, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAuxiliaryHeater_Impl::setHeatingCapacityUnits(const std::string& heatingCapacityUnits) {
      return setString(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::HeatingCapacityUnits, heatingCapacityUnits);
    }

    void GeneratorFuelCellAuxiliaryHeater_Impl::resetHeatingCapacityUnits() {
      OS_ASSERT(setString(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::HeatingCapacityUnits, "Watts"));
    }

    double GeneratorFuelCellAuxiliaryHeater_Impl::maximumHeatingCapacityinWatts() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::MaximumHeatingCapacityinWatts, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAuxiliaryHeater_Impl::setMaximumHeatingCapacityinWatts(double maximumHeatingCapacityinWatts) {
      const bool result =
        setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::MaximumHeatingCapacityinWatts, maximumHeatingCapacityinWatts);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellAuxiliaryHeater_Impl::resetMaximumHeatingCapacityinWatts() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::MaximumHeatingCapacityinWatts, 0.0));
    }

    double GeneratorFuelCellAuxiliaryHeater_Impl::minimumHeatingCapacityinWatts() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::MinimumHeatingCapacityinWatts, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAuxiliaryHeater_Impl::setMinimumHeatingCapacityinWatts(double minimumHeatingCapacityinWatts) {
      const bool result =
        setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::MinimumHeatingCapacityinWatts, minimumHeatingCapacityinWatts);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellAuxiliaryHeater_Impl::resetMinimumHeatingCapacityinWatts() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::MinimumHeatingCapacityinWatts, 0.0));
    }

    double GeneratorFuelCellAuxiliaryHeater_Impl::maximumHeatingCapacityinKmolperSecond() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::MaximumHeatingCapacityinKmolperSecond, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAuxiliaryHeater_Impl::setMaximumHeatingCapacityinKmolperSecond(double maximumHeatingCapacityinKmolperSecond) {
      const bool result =
        setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::MaximumHeatingCapacityinKmolperSecond, maximumHeatingCapacityinKmolperSecond);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellAuxiliaryHeater_Impl::resetMaximumHeatingCapacityinKmolperSecond() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::MaximumHeatingCapacityinKmolperSecond, 0.0));
    }

    double GeneratorFuelCellAuxiliaryHeater_Impl::minimumHeatingCapacityinKmolperSecond() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::MinimumHeatingCapacityinKmolperSecond, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAuxiliaryHeater_Impl::setMinimumHeatingCapacityinKmolperSecond(double minimumHeatingCapacityinKmolperSecond) {
      const bool result =
        setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::MinimumHeatingCapacityinKmolperSecond, minimumHeatingCapacityinKmolperSecond);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellAuxiliaryHeater_Impl::resetMinimumHeatingCapacityinKmolperSecond() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_AuxiliaryHeaterFields::MinimumHeatingCapacityinKmolperSecond, 0.0));
    }

    std::vector<std::string> GeneratorFuelCellAuxiliaryHeater_Impl::skinLossDestinationValues() const {
      return openstudio::epmodel::GeneratorFuelCellAuxiliaryHeater::skinLossDestinationValues();
    }

    std::vector<std::string> GeneratorFuelCellAuxiliaryHeater_Impl::heatingCapacityUnitsValues() const {
      return openstudio::epmodel::GeneratorFuelCellAuxiliaryHeater::heatingCapacityUnitsValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
