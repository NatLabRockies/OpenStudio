/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfacePropertyExteriorNaturalVentedCavity.hpp"
#include "SurfacePropertyExteriorNaturalVentedCavity_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/SurfaceProperty_ExteriorNaturalVentedCavity_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SurfacePropertyExteriorNaturalVentedCavity::SurfacePropertyExteriorNaturalVentedCavity(const Model& model)
    : ModelObject(SurfacePropertyExteriorNaturalVentedCavity::iddObjectType(), model) {}

  SurfacePropertyExteriorNaturalVentedCavity::SurfacePropertyExteriorNaturalVentedCavity(
    std::shared_ptr<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertyExteriorNaturalVentedCavity::iddObjectType() {
    return IddObjectType::SurfaceProperty_ExteriorNaturalVentedCavity;
  }

  std::vector<std::string> SurfacePropertyExteriorNaturalVentedCavity::roughnessOfExteriorSurfaceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::RoughnessofExteriorSurface);
  }

  boost::optional<double> SurfacePropertyExteriorNaturalVentedCavity::areaFractionOfOpenings() const {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->areaFractionOfOpenings();
  }

  bool SurfacePropertyExteriorNaturalVentedCavity::setAreaFractionOfOpenings(double areaFractionOfOpenings) {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->setAreaFractionOfOpenings(areaFractionOfOpenings);
  }

  void SurfacePropertyExteriorNaturalVentedCavity::resetAreaFractionOfOpenings() {
    getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->resetAreaFractionOfOpenings();
  }

  boost::optional<double> SurfacePropertyExteriorNaturalVentedCavity::thermalEmissivityOfExteriorBaffleMaterial() const {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->thermalEmissivityOfExteriorBaffleMaterial();
  }

  bool SurfacePropertyExteriorNaturalVentedCavity::setThermalEmissivityOfExteriorBaffleMaterial(double thermalEmissivityOfExteriorBaffleMaterial) {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->setThermalEmissivityOfExteriorBaffleMaterial(
      thermalEmissivityOfExteriorBaffleMaterial);
  }

  void SurfacePropertyExteriorNaturalVentedCavity::resetThermalEmissivityOfExteriorBaffleMaterial() {
    getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->resetThermalEmissivityOfExteriorBaffleMaterial();
  }

  boost::optional<double> SurfacePropertyExteriorNaturalVentedCavity::solarAbsorbtivityOfExteriorBaffle() const {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->solarAbsorbtivityOfExteriorBaffle();
  }

  bool SurfacePropertyExteriorNaturalVentedCavity::setSolarAbsorbtivityOfExteriorBaffle(double solarAbsorbtivityOfExteriorBaffle) {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->setSolarAbsorbtivityOfExteriorBaffle(
      solarAbsorbtivityOfExteriorBaffle);
  }

  void SurfacePropertyExteriorNaturalVentedCavity::resetSolarAbsorbtivityOfExteriorBaffle() {
    getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->resetSolarAbsorbtivityOfExteriorBaffle();
  }

  boost::optional<double> SurfacePropertyExteriorNaturalVentedCavity::heightScaleForBuoyancyDrivenVentilation() const {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->heightScaleForBuoyancyDrivenVentilation();
  }

  bool SurfacePropertyExteriorNaturalVentedCavity::setHeightScaleForBuoyancyDrivenVentilation(double heightScaleForBuoyancyDrivenVentilation) {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->setHeightScaleForBuoyancyDrivenVentilation(
      heightScaleForBuoyancyDrivenVentilation);
  }

  void SurfacePropertyExteriorNaturalVentedCavity::resetHeightScaleForBuoyancyDrivenVentilation() {
    getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->resetHeightScaleForBuoyancyDrivenVentilation();
  }

  boost::optional<double> SurfacePropertyExteriorNaturalVentedCavity::effectiveThicknessOfCavityBehindExteriorBaffle() const {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->effectiveThicknessOfCavityBehindExteriorBaffle();
  }

  bool SurfacePropertyExteriorNaturalVentedCavity::setEffectiveThicknessOfCavityBehindExteriorBaffle(
    double effectiveThicknessOfCavityBehindExteriorBaffle) {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->setEffectiveThicknessOfCavityBehindExteriorBaffle(
      effectiveThicknessOfCavityBehindExteriorBaffle);
  }

  void SurfacePropertyExteriorNaturalVentedCavity::resetEffectiveThicknessOfCavityBehindExteriorBaffle() {
    getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->resetEffectiveThicknessOfCavityBehindExteriorBaffle();
  }

  double SurfacePropertyExteriorNaturalVentedCavity::ratioOfActualSurfaceAreaToProjectedSurfaceArea() const {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->ratioOfActualSurfaceAreaToProjectedSurfaceArea();
  }

  bool SurfacePropertyExteriorNaturalVentedCavity::setRatioOfActualSurfaceAreaToProjectedSurfaceArea(
    double ratioOfActualSurfaceAreaToProjectedSurfaceArea) {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->setRatioOfActualSurfaceAreaToProjectedSurfaceArea(
      ratioOfActualSurfaceAreaToProjectedSurfaceArea);
  }

  bool SurfacePropertyExteriorNaturalVentedCavity::isRatioOfActualSurfaceAreaToProjectedSurfaceAreaDefaulted() const {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->isRatioOfActualSurfaceAreaToProjectedSurfaceAreaDefaulted();
  }

  void SurfacePropertyExteriorNaturalVentedCavity::resetRatioOfActualSurfaceAreaToProjectedSurfaceArea() {
    getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->resetRatioOfActualSurfaceAreaToProjectedSurfaceArea();
  }

  std::string SurfacePropertyExteriorNaturalVentedCavity::roughnessOfExteriorSurface() const {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->roughnessOfExteriorSurface();
  }

  bool SurfacePropertyExteriorNaturalVentedCavity::setRoughnessOfExteriorSurface(const std::string& roughnessOfExteriorSurface) {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->setRoughnessOfExteriorSurface(roughnessOfExteriorSurface);
  }

  double SurfacePropertyExteriorNaturalVentedCavity::effectivenessForPerforationsWithRespectToWind() const {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->effectivenessForPerforationsWithRespectToWind();
  }

  bool SurfacePropertyExteriorNaturalVentedCavity::setEffectivenessForPerforationsWithRespectToWind(
    double effectivenessForPerforationsWithRespectToWind) {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->setEffectivenessForPerforationsWithRespectToWind(
      effectivenessForPerforationsWithRespectToWind);
  }

  bool SurfacePropertyExteriorNaturalVentedCavity::isEffectivenessForPerforationsWithRespectToWindDefaulted() const {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->isEffectivenessForPerforationsWithRespectToWindDefaulted();
  }

  void SurfacePropertyExteriorNaturalVentedCavity::resetEffectivenessForPerforationsWithRespectToWind() {
    getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->resetEffectivenessForPerforationsWithRespectToWind();
  }

  double SurfacePropertyExteriorNaturalVentedCavity::dischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow() const {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->dischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow();
  }

  bool SurfacePropertyExteriorNaturalVentedCavity::setDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow(
    double dischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow) {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->setDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow(
      dischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow);
  }

  bool SurfacePropertyExteriorNaturalVentedCavity::isDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlowDefaulted() const {
    return getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()
      ->isDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlowDefaulted();
  }

  void SurfacePropertyExteriorNaturalVentedCavity::resetDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow() {
    getImpl<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl>()->resetDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> SurfacePropertyExteriorNaturalVentedCavity_Impl::areaFractionOfOpenings() const {
      return getDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::AreaFractionofOpenings, true);
    }

    bool SurfacePropertyExteriorNaturalVentedCavity_Impl::setAreaFractionOfOpenings(double areaFractionOfOpenings) {
      return setDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::AreaFractionofOpenings, areaFractionOfOpenings);
    }

    void SurfacePropertyExteriorNaturalVentedCavity_Impl::resetAreaFractionOfOpenings() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::AreaFractionofOpenings, ""));
    }

    boost::optional<double> SurfacePropertyExteriorNaturalVentedCavity_Impl::thermalEmissivityOfExteriorBaffleMaterial() const {
      return getDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::ThermalEmissivityofExteriorBaffleMaterial, true);
    }

    bool SurfacePropertyExteriorNaturalVentedCavity_Impl::setThermalEmissivityOfExteriorBaffleMaterial(
      double thermalEmissivityOfExteriorBaffleMaterial) {
      return setDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::ThermalEmissivityofExteriorBaffleMaterial,
                       thermalEmissivityOfExteriorBaffleMaterial);
    }

    void SurfacePropertyExteriorNaturalVentedCavity_Impl::resetThermalEmissivityOfExteriorBaffleMaterial() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::ThermalEmissivityofExteriorBaffleMaterial, ""));
    }

    boost::optional<double> SurfacePropertyExteriorNaturalVentedCavity_Impl::solarAbsorbtivityOfExteriorBaffle() const {
      return getDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::SolarAbsorbtivityofExteriorBaffle, true);
    }

    bool SurfacePropertyExteriorNaturalVentedCavity_Impl::setSolarAbsorbtivityOfExteriorBaffle(double solarAbsorbtivityOfExteriorBaffle) {
      return setDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::SolarAbsorbtivityofExteriorBaffle,
                       solarAbsorbtivityOfExteriorBaffle);
    }

    void SurfacePropertyExteriorNaturalVentedCavity_Impl::resetSolarAbsorbtivityOfExteriorBaffle() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::SolarAbsorbtivityofExteriorBaffle, ""));
    }

    boost::optional<double> SurfacePropertyExteriorNaturalVentedCavity_Impl::heightScaleForBuoyancyDrivenVentilation() const {
      return getDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::HeightScaleforBuoyancyDrivenVentilation, true);
    }

    bool SurfacePropertyExteriorNaturalVentedCavity_Impl::setHeightScaleForBuoyancyDrivenVentilation(double heightScaleForBuoyancyDrivenVentilation) {
      return setDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::HeightScaleforBuoyancyDrivenVentilation,
                       heightScaleForBuoyancyDrivenVentilation);
    }

    void SurfacePropertyExteriorNaturalVentedCavity_Impl::resetHeightScaleForBuoyancyDrivenVentilation() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::HeightScaleforBuoyancyDrivenVentilation, ""));
    }

    boost::optional<double> SurfacePropertyExteriorNaturalVentedCavity_Impl::effectiveThicknessOfCavityBehindExteriorBaffle() const {
      return getDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::EffectiveThicknessofCavityBehindExteriorBaffle, true);
    }

    bool SurfacePropertyExteriorNaturalVentedCavity_Impl::setEffectiveThicknessOfCavityBehindExteriorBaffle(
      double effectiveThicknessOfCavityBehindExteriorBaffle) {
      return setDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::EffectiveThicknessofCavityBehindExteriorBaffle,
                       effectiveThicknessOfCavityBehindExteriorBaffle);
    }

    void SurfacePropertyExteriorNaturalVentedCavity_Impl::resetEffectiveThicknessOfCavityBehindExteriorBaffle() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::EffectiveThicknessofCavityBehindExteriorBaffle, ""));
    }

    double SurfacePropertyExteriorNaturalVentedCavity_Impl::ratioOfActualSurfaceAreaToProjectedSurfaceArea() const {
      boost::optional<double> value =
        getDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::RatioofActualSurfaceAreatoProjectedSurfaceArea, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyExteriorNaturalVentedCavity_Impl::setRatioOfActualSurfaceAreaToProjectedSurfaceArea(
      double ratioOfActualSurfaceAreaToProjectedSurfaceArea) {
      return setDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::RatioofActualSurfaceAreatoProjectedSurfaceArea,
                       ratioOfActualSurfaceAreaToProjectedSurfaceArea);
    }

    bool SurfacePropertyExteriorNaturalVentedCavity_Impl::isRatioOfActualSurfaceAreaToProjectedSurfaceAreaDefaulted() const {
      return isEmpty(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::RatioofActualSurfaceAreatoProjectedSurfaceArea);
    }

    void SurfacePropertyExteriorNaturalVentedCavity_Impl::resetRatioOfActualSurfaceAreaToProjectedSurfaceArea() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::RatioofActualSurfaceAreatoProjectedSurfaceArea, ""));
    }

    std::string SurfacePropertyExteriorNaturalVentedCavity_Impl::roughnessOfExteriorSurface() const {
      boost::optional<std::string> value = getString(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::RoughnessofExteriorSurface, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyExteriorNaturalVentedCavity_Impl::setRoughnessOfExteriorSurface(const std::string& roughnessOfExteriorSurface) {
      return setString(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::RoughnessofExteriorSurface, roughnessOfExteriorSurface);
    }

    double SurfacePropertyExteriorNaturalVentedCavity_Impl::effectivenessForPerforationsWithRespectToWind() const {
      boost::optional<double> value =
        getDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::EffectivenessforPerforationswithRespecttoWind, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyExteriorNaturalVentedCavity_Impl::setEffectivenessForPerforationsWithRespectToWind(
      double effectivenessForPerforationsWithRespectToWind) {
      return setDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::EffectivenessforPerforationswithRespecttoWind,
                       effectivenessForPerforationsWithRespectToWind);
    }

    bool SurfacePropertyExteriorNaturalVentedCavity_Impl::isEffectivenessForPerforationsWithRespectToWindDefaulted() const {
      return isEmpty(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::EffectivenessforPerforationswithRespecttoWind);
    }

    void SurfacePropertyExteriorNaturalVentedCavity_Impl::resetEffectivenessForPerforationsWithRespectToWind() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::EffectivenessforPerforationswithRespecttoWind, ""));
    }

    double SurfacePropertyExteriorNaturalVentedCavity_Impl::dischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow() const {
      boost::optional<double> value = getDouble(
        openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyExteriorNaturalVentedCavity_Impl::setDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow(
      double dischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow) {
      return setDouble(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow,
                       dischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow);
    }

    bool SurfacePropertyExteriorNaturalVentedCavity_Impl::isDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlowDefaulted() const {
      return isEmpty(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow);
    }

    void SurfacePropertyExteriorNaturalVentedCavity_Impl::resetDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow() {
      OS_ASSERT(
        setString(openstudio::SurfaceProperty_ExteriorNaturalVentedCavityFields::DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow, ""));
    }

    std::vector<std::string> SurfacePropertyExteriorNaturalVentedCavity_Impl::roughnessOfExteriorSurfaceValues() const {
      return openstudio::epmodel::SurfacePropertyExteriorNaturalVentedCavity::roughnessOfExteriorSurfaceValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
