/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/MaterialPropertyMoisturePenetrationDepthSettings.hpp"
#include "ModelObject/MaterialPropertyMoisturePenetrationDepthSettings_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/MaterialProperty_MoisturePenetrationDepth_Settings_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  MaterialPropertyMoisturePenetrationDepthSettings::MaterialPropertyMoisturePenetrationDepthSettings(const Model& model)
    : ModelObject(MaterialPropertyMoisturePenetrationDepthSettings::iddObjectType(), model) {}

  MaterialPropertyMoisturePenetrationDepthSettings::MaterialPropertyMoisturePenetrationDepthSettings(
    std::shared_ptr<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType MaterialPropertyMoisturePenetrationDepthSettings::iddObjectType() {
    return IddObjectType::MaterialProperty_MoisturePenetrationDepth_Settings;
  }

  double MaterialPropertyMoisturePenetrationDepthSettings::waterVaporDiffusionResistanceFactor() const {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->waterVaporDiffusionResistanceFactor();
  }

  bool MaterialPropertyMoisturePenetrationDepthSettings::setWaterVaporDiffusionResistanceFactor(double waterVaporDiffusionResistanceFactor) {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->setWaterVaporDiffusionResistanceFactor(
      waterVaporDiffusionResistanceFactor);
  }

  double MaterialPropertyMoisturePenetrationDepthSettings::moistureEquationCoefficientA() const {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->moistureEquationCoefficientA();
  }

  bool MaterialPropertyMoisturePenetrationDepthSettings::setMoistureEquationCoefficientA(double moistureEquationCoefficientA) {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->setMoistureEquationCoefficientA(moistureEquationCoefficientA);
  }

  double MaterialPropertyMoisturePenetrationDepthSettings::moistureEquationCoefficientB() const {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->moistureEquationCoefficientB();
  }

  bool MaterialPropertyMoisturePenetrationDepthSettings::setMoistureEquationCoefficientB(double moistureEquationCoefficientB) {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->setMoistureEquationCoefficientB(moistureEquationCoefficientB);
  }

  double MaterialPropertyMoisturePenetrationDepthSettings::moistureEquationCoefficientC() const {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->moistureEquationCoefficientC();
  }

  bool MaterialPropertyMoisturePenetrationDepthSettings::setMoistureEquationCoefficientC(double moistureEquationCoefficientC) {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->setMoistureEquationCoefficientC(moistureEquationCoefficientC);
  }

  double MaterialPropertyMoisturePenetrationDepthSettings::moistureEquationCoefficientD() const {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->moistureEquationCoefficientD();
  }

  bool MaterialPropertyMoisturePenetrationDepthSettings::setMoistureEquationCoefficientD(double moistureEquationCoefficientD) {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->setMoistureEquationCoefficientD(moistureEquationCoefficientD);
  }

  std::vector<double> MaterialPropertyMoisturePenetrationDepthSettings::moistureEquationCoefficients() const {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->moistureEquationCoefficients();
  }

  bool MaterialPropertyMoisturePenetrationDepthSettings::setMoistureEquationCoefficients(double moistureEquationCoefficientA,
                                                                                         double moistureEquationCoefficientB,
                                                                                         double moistureEquationCoefficientC,
                                                                                         double moistureEquationCoefficientD) {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->setMoistureEquationCoefficients(
      moistureEquationCoefficientA, moistureEquationCoefficientB, moistureEquationCoefficientC, moistureEquationCoefficientD);
  }

  boost::optional<double> MaterialPropertyMoisturePenetrationDepthSettings::surfaceLayerPenetrationDepth() {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->surfaceLayerPenetrationDepth();
  }

  bool MaterialPropertyMoisturePenetrationDepthSettings::setSurfaceLayerPenetrationDepth(double surfaceLayerPenetrationDepth) {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->setSurfaceLayerPenetrationDepth(surfaceLayerPenetrationDepth);
  }

  bool MaterialPropertyMoisturePenetrationDepthSettings::isSurfaceLayerPenetrationDepthAutocalculated() {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->isSurfaceLayerPenetrationDepthAutocalculated();
  }

  void MaterialPropertyMoisturePenetrationDepthSettings::autocalculateSurfaceLayerPenetrationDepth() {
    getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->autocalculateSurfaceLayerPenetrationDepth();
  }

  boost::optional<double> MaterialPropertyMoisturePenetrationDepthSettings::deepLayerPenetrationDepth() {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->deepLayerPenetrationDepth();
  }

  bool MaterialPropertyMoisturePenetrationDepthSettings::setDeepLayerPenetrationDepth(double deepLayerPenetrationDepth) {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->setDeepLayerPenetrationDepth(deepLayerPenetrationDepth);
  }

  bool MaterialPropertyMoisturePenetrationDepthSettings::isDeepLayerPenetrationDepthAutocalculated() {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->isDeepLayerPenetrationDepthAutocalculated();
  }

  void MaterialPropertyMoisturePenetrationDepthSettings::autocalculateDeepLayerPenetrationDepth() {
    getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->autocalculateDeepLayerPenetrationDepth();
  }

  double MaterialPropertyMoisturePenetrationDepthSettings::coatingLayerThickness() const {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->coatingLayerThickness();
  }

  bool MaterialPropertyMoisturePenetrationDepthSettings::setCoatingLayerThickness(double coatingLayerThickness) {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->setCoatingLayerThickness(coatingLayerThickness);
  }

  double MaterialPropertyMoisturePenetrationDepthSettings::coatingLayerWaterVaporDiffusionResistanceFactor() const {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->coatingLayerWaterVaporDiffusionResistanceFactor();
  }

  bool MaterialPropertyMoisturePenetrationDepthSettings::setCoatingLayerWaterVaporDiffusionResistanceFactor(
    double coatingLayerWaterVaporDiffusionResistanceFactor) {
    return getImpl<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl>()->setCoatingLayerWaterVaporDiffusionResistanceFactor(
      coatingLayerWaterVaporDiffusionResistanceFactor);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double MaterialPropertyMoisturePenetrationDepthSettings_Impl::waterVaporDiffusionResistanceFactor() const {
      const auto value = getDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::WaterVaporDiffusionResistanceFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyMoisturePenetrationDepthSettings_Impl::setWaterVaporDiffusionResistanceFactor(double waterVaporDiffusionResistanceFactor) {
      const bool result = setDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::WaterVaporDiffusionResistanceFactor,
                                    waterVaporDiffusionResistanceFactor);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyMoisturePenetrationDepthSettings_Impl::moistureEquationCoefficientA() const {
      const auto value = getDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficienta, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyMoisturePenetrationDepthSettings_Impl::setMoistureEquationCoefficientA(double moistureEquationCoefficientA) {
      const bool result =
        setDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficienta, moistureEquationCoefficientA);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyMoisturePenetrationDepthSettings_Impl::moistureEquationCoefficientB() const {
      const auto value = getDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficientb, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyMoisturePenetrationDepthSettings_Impl::setMoistureEquationCoefficientB(double moistureEquationCoefficientB) {
      const bool result =
        setDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficientb, moistureEquationCoefficientB);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyMoisturePenetrationDepthSettings_Impl::moistureEquationCoefficientC() const {
      const auto value = getDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficientc, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyMoisturePenetrationDepthSettings_Impl::setMoistureEquationCoefficientC(double moistureEquationCoefficientC) {
      const bool result =
        setDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficientc, moistureEquationCoefficientC);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyMoisturePenetrationDepthSettings_Impl::moistureEquationCoefficientD() const {
      const auto value = getDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficientd, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyMoisturePenetrationDepthSettings_Impl::setMoistureEquationCoefficientD(double moistureEquationCoefficientD) {
      const bool result =
        setDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficientd, moistureEquationCoefficientD);
      OS_ASSERT(result);
      return result;
    }

    std::vector<double> MaterialPropertyMoisturePenetrationDepthSettings_Impl::moistureEquationCoefficients() const {
      const auto coefficientA = getDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficienta, true);
      const auto coefficientB = getDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficientb, true);
      const auto coefficientC = getDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficientc, true);
      const auto coefficientD = getDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficientd, true);
      OS_ASSERT(coefficientA && coefficientB && coefficientC && coefficientD);
      return {*coefficientA, *coefficientB, *coefficientC, *coefficientD};
    }

    bool MaterialPropertyMoisturePenetrationDepthSettings_Impl::setMoistureEquationCoefficients(double moistureEquationCoefficientA,
                                                                                                double moistureEquationCoefficientB,
                                                                                                double moistureEquationCoefficientC,
                                                                                                double moistureEquationCoefficientD) {
      const bool resultA = setMoistureEquationCoefficientA(moistureEquationCoefficientA);
      const bool resultB = setMoistureEquationCoefficientB(moistureEquationCoefficientB);
      const bool resultC = setMoistureEquationCoefficientC(moistureEquationCoefficientC);
      const bool resultD = setMoistureEquationCoefficientD(moistureEquationCoefficientD);
      const bool result = resultA && resultB && resultC && resultD;
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> MaterialPropertyMoisturePenetrationDepthSettings_Impl::surfaceLayerPenetrationDepth() {
      return getDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::SurfaceLayerPenetrationDepth, true);
    }

    bool MaterialPropertyMoisturePenetrationDepthSettings_Impl::setSurfaceLayerPenetrationDepth(double surfaceLayerPenetrationDepth) {
      const bool result =
        setDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::SurfaceLayerPenetrationDepth, surfaceLayerPenetrationDepth);
      OS_ASSERT(result);
      return result;
    }

    bool MaterialPropertyMoisturePenetrationDepthSettings_Impl::isSurfaceLayerPenetrationDepthAutocalculated() {
      if (const auto value = getString(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::SurfaceLayerPenetrationDepth, true)) {
        return openstudio::istringEqual(*value, "Autocalculate");
      }
      return false;
    }

    void MaterialPropertyMoisturePenetrationDepthSettings_Impl::autocalculateSurfaceLayerPenetrationDepth() {
      OS_ASSERT(setString(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::SurfaceLayerPenetrationDepth, ""));
    }

    boost::optional<double> MaterialPropertyMoisturePenetrationDepthSettings_Impl::deepLayerPenetrationDepth() {
      return getDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::DeepLayerPenetrationDepth, true);
    }

    bool MaterialPropertyMoisturePenetrationDepthSettings_Impl::setDeepLayerPenetrationDepth(double deepLayerPenetrationDepth) {
      const bool result =
        setDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::DeepLayerPenetrationDepth, deepLayerPenetrationDepth);
      OS_ASSERT(result);
      return result;
    }

    bool MaterialPropertyMoisturePenetrationDepthSettings_Impl::isDeepLayerPenetrationDepthAutocalculated() {
      if (const auto value = getString(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::DeepLayerPenetrationDepth, true)) {
        return openstudio::istringEqual(*value, "Autocalculate");
      }
      return false;
    }

    void MaterialPropertyMoisturePenetrationDepthSettings_Impl::autocalculateDeepLayerPenetrationDepth() {
      OS_ASSERT(setString(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::DeepLayerPenetrationDepth, ""));
    }

    double MaterialPropertyMoisturePenetrationDepthSettings_Impl::coatingLayerThickness() const {
      const auto value = getDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::CoatingLayerThickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyMoisturePenetrationDepthSettings_Impl::setCoatingLayerThickness(double coatingLayerThickness) {
      const bool result =
        setDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::CoatingLayerThickness, coatingLayerThickness);
      OS_ASSERT(result);
      return result;
    }

    double MaterialPropertyMoisturePenetrationDepthSettings_Impl::coatingLayerWaterVaporDiffusionResistanceFactor() const {
      const auto value =
        getDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::CoatingLayerWaterVaporDiffusionResistanceFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyMoisturePenetrationDepthSettings_Impl::setCoatingLayerWaterVaporDiffusionResistanceFactor(
      double coatingLayerWaterVaporDiffusionResistanceFactor) {
      const bool result =
        setDouble(openstudio::MaterialProperty_MoisturePenetrationDepth_SettingsFields::CoatingLayerWaterVaporDiffusionResistanceFactor,
                  coatingLayerWaterVaporDiffusionResistanceFactor);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
