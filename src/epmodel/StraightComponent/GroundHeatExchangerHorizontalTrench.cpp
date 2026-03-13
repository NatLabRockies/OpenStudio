/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/GroundHeatExchangerHorizontalTrench.hpp"
#include "StraightComponent/GroundHeatExchangerHorizontalTrench_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatExchanger_HorizontalTrench_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatExchangerHorizontalTrench::GroundHeatExchangerHorizontalTrench(const Model& model)
    : StraightComponent(GroundHeatExchangerHorizontalTrench::iddObjectType(), model) {
    bool ok = true;
    ok = setDesignFlowRate(0.004);
    OS_ASSERT(ok);
    ok = setTrenchLengthinPipeAxialDirection(75.0);
    OS_ASSERT(ok);
    ok = setNumberofTrenches(2);
    OS_ASSERT(ok);
    ok = setHorizontalSpacingBetweenPipes(2.0);
    OS_ASSERT(ok);
    ok = setPipeInnerDiameter(0.016);
    OS_ASSERT(ok);
    ok = setPipeOuterDiameter(0.02667);
    OS_ASSERT(ok);
    ok = setBurialDepth(1.25);
    OS_ASSERT(ok);
    ok = setSoilThermalConductivity(1.08);
    OS_ASSERT(ok);
    ok = setSoilDensity(962.0);
    OS_ASSERT(ok);
    ok = setSoilSpecificHeat(2576.0);
    OS_ASSERT(ok);
    ok = setPipeThermalConductivity(0.3895);
    OS_ASSERT(ok);
    ok = setPipeDensity(641.0);
    OS_ASSERT(ok);
    ok = setPipeSpecificHeat(2405.0);
    OS_ASSERT(ok);
    ok = setSoilMoistureContentPercent(30.0);
    OS_ASSERT(ok);
    ok = setSoilMoistureContentPercentatSaturation(50.0);
    OS_ASSERT(ok);
    ok = setEvapotranspirationGroundCoverParameter(0.408);
    OS_ASSERT(ok);
  }

  GroundHeatExchangerHorizontalTrench::GroundHeatExchangerHorizontalTrench(std::shared_ptr<detail::GroundHeatExchangerHorizontalTrench_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType GroundHeatExchangerHorizontalTrench::iddObjectType() {
    return IddObjectType::GroundHeatExchanger_HorizontalTrench;
  }

  double GroundHeatExchangerHorizontalTrench::designFlowRate() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->designFlowRate();
  }

  double GroundHeatExchangerHorizontalTrench::trenchLengthinPipeAxialDirection() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->trenchLengthinPipeAxialDirection();
  }

  int GroundHeatExchangerHorizontalTrench::numberofTrenches() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->numberofTrenches();
  }

  double GroundHeatExchangerHorizontalTrench::horizontalSpacingBetweenPipes() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->horizontalSpacingBetweenPipes();
  }

  double GroundHeatExchangerHorizontalTrench::pipeInnerDiameter() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->pipeInnerDiameter();
  }

  double GroundHeatExchangerHorizontalTrench::pipeOuterDiameter() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->pipeOuterDiameter();
  }

  double GroundHeatExchangerHorizontalTrench::burialDepth() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->burialDepth();
  }

  double GroundHeatExchangerHorizontalTrench::soilThermalConductivity() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->soilThermalConductivity();
  }

  double GroundHeatExchangerHorizontalTrench::soilDensity() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->soilDensity();
  }

  double GroundHeatExchangerHorizontalTrench::soilSpecificHeat() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->soilSpecificHeat();
  }

  double GroundHeatExchangerHorizontalTrench::pipeThermalConductivity() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->pipeThermalConductivity();
  }

  double GroundHeatExchangerHorizontalTrench::pipeDensity() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->pipeDensity();
  }

  double GroundHeatExchangerHorizontalTrench::pipeSpecificHeat() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->pipeSpecificHeat();
  }

  double GroundHeatExchangerHorizontalTrench::soilMoistureContentPercent() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->soilMoistureContentPercent();
  }

  double GroundHeatExchangerHorizontalTrench::soilMoistureContentPercentatSaturation() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->soilMoistureContentPercentatSaturation();
  }

  double GroundHeatExchangerHorizontalTrench::evapotranspirationGroundCoverParameter() const {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->evapotranspirationGroundCoverParameter();
  }

  bool GroundHeatExchangerHorizontalTrench::setDesignFlowRate(double designFlowRate) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setDesignFlowRate(designFlowRate);
  }

  bool GroundHeatExchangerHorizontalTrench::setTrenchLengthinPipeAxialDirection(double trenchLengthinPipeAxialDirection) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setTrenchLengthinPipeAxialDirection(trenchLengthinPipeAxialDirection);
  }

  bool GroundHeatExchangerHorizontalTrench::setNumberofTrenches(int numberofTrenches) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setNumberofTrenches(numberofTrenches);
  }

  bool GroundHeatExchangerHorizontalTrench::setHorizontalSpacingBetweenPipes(double horizontalSpacingBetweenPipes) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setHorizontalSpacingBetweenPipes(horizontalSpacingBetweenPipes);
  }

  bool GroundHeatExchangerHorizontalTrench::setPipeInnerDiameter(double pipeInnerDiameter) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setPipeInnerDiameter(pipeInnerDiameter);
  }

  bool GroundHeatExchangerHorizontalTrench::setPipeOuterDiameter(double pipeOuterDiameter) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setPipeOuterDiameter(pipeOuterDiameter);
  }

  bool GroundHeatExchangerHorizontalTrench::setBurialDepth(double burialDepth) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setBurialDepth(burialDepth);
  }

  bool GroundHeatExchangerHorizontalTrench::setSoilThermalConductivity(double soilThermalConductivity) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setSoilThermalConductivity(soilThermalConductivity);
  }

  bool GroundHeatExchangerHorizontalTrench::setSoilDensity(double soilDensity) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setSoilDensity(soilDensity);
  }

  bool GroundHeatExchangerHorizontalTrench::setSoilSpecificHeat(double soilSpecificHeat) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setSoilSpecificHeat(soilSpecificHeat);
  }

  bool GroundHeatExchangerHorizontalTrench::setPipeThermalConductivity(double pipeThermalConductivity) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setPipeThermalConductivity(pipeThermalConductivity);
  }

  bool GroundHeatExchangerHorizontalTrench::setPipeDensity(double pipeDensity) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setPipeDensity(pipeDensity);
  }

  bool GroundHeatExchangerHorizontalTrench::setPipeSpecificHeat(double pipeSpecificHeat) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setPipeSpecificHeat(pipeSpecificHeat);
  }

  bool GroundHeatExchangerHorizontalTrench::setSoilMoistureContentPercent(double soilMoistureContentPercent) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setSoilMoistureContentPercent(soilMoistureContentPercent);
  }

  bool GroundHeatExchangerHorizontalTrench::setSoilMoistureContentPercentatSaturation(double soilMoistureContentPercentatSaturation) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setSoilMoistureContentPercentatSaturation(
      soilMoistureContentPercentatSaturation);
  }

  bool GroundHeatExchangerHorizontalTrench::setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter) {
    return getImpl<detail::GroundHeatExchangerHorizontalTrench_Impl>()->setEvapotranspirationGroundCoverParameter(
      evapotranspirationGroundCoverParameter);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned GroundHeatExchangerHorizontalTrench_Impl::inletPort() const {
      return openstudio::GroundHeatExchanger_HorizontalTrenchFields::InletNodeName;
    }

    unsigned GroundHeatExchangerHorizontalTrench_Impl::outletPort() const {
      return openstudio::GroundHeatExchanger_HorizontalTrenchFields::OutletNodeName;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setDesignFlowRate(double designFlowRate) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::DesignFlowRate, designFlowRate);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::designFlowRate() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::DesignFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatExchangerHorizontalTrench_Impl::trenchLengthinPipeAxialDirection() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::TrenchLengthinPipeAxialDirection, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setTrenchLengthinPipeAxialDirection(double trenchLengthinPipeAxialDirection) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::TrenchLengthinPipeAxialDirection, trenchLengthinPipeAxialDirection);
    }

    int GroundHeatExchangerHorizontalTrench_Impl::numberofTrenches() const {
      const auto value = getInt(openstudio::GroundHeatExchanger_HorizontalTrenchFields::NumberofTrenches, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setNumberofTrenches(int numberofTrenches) {
      return setInt(openstudio::GroundHeatExchanger_HorizontalTrenchFields::NumberofTrenches, numberofTrenches);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::horizontalSpacingBetweenPipes() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::HorizontalSpacingBetweenPipes, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setHorizontalSpacingBetweenPipes(double horizontalSpacingBetweenPipes) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::HorizontalSpacingBetweenPipes, horizontalSpacingBetweenPipes);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::pipeInnerDiameter() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::PipeInnerDiameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setPipeInnerDiameter(double pipeInnerDiameter) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::PipeInnerDiameter, pipeInnerDiameter);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::pipeOuterDiameter() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::PipeOuterDiameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setPipeOuterDiameter(double pipeOuterDiameter) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::PipeOuterDiameter, pipeOuterDiameter);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::burialDepth() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::BurialDepth, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setBurialDepth(double burialDepth) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::BurialDepth, burialDepth);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::soilThermalConductivity() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::SoilThermalConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setSoilThermalConductivity(double soilThermalConductivity) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::SoilThermalConductivity, soilThermalConductivity);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::soilDensity() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::SoilDensity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setSoilDensity(double soilDensity) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::SoilDensity, soilDensity);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::soilSpecificHeat() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::SoilSpecificHeat, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setSoilSpecificHeat(double soilSpecificHeat) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::SoilSpecificHeat, soilSpecificHeat);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::pipeThermalConductivity() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::PipeThermalConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setPipeThermalConductivity(double pipeThermalConductivity) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::PipeThermalConductivity, pipeThermalConductivity);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::pipeDensity() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::PipeDensity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setPipeDensity(double pipeDensity) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::PipeDensity, pipeDensity);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::pipeSpecificHeat() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::PipeSpecificHeat, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setPipeSpecificHeat(double pipeSpecificHeat) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::PipeSpecificHeat, pipeSpecificHeat);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::soilMoistureContentPercent() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::SoilMoistureContentPercent, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setSoilMoistureContentPercent(double soilMoistureContentPercent) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::SoilMoistureContentPercent, soilMoistureContentPercent);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::soilMoistureContentPercentatSaturation() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::SoilMoistureContentPercentatSaturation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setSoilMoistureContentPercentatSaturation(double soilMoistureContentPercentatSaturation) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::SoilMoistureContentPercentatSaturation,
                       soilMoistureContentPercentatSaturation);
    }

    double GroundHeatExchangerHorizontalTrench_Impl::evapotranspirationGroundCoverParameter() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::EvapotranspirationGroundCoverParameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerHorizontalTrench_Impl::setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter) {
      return setDouble(openstudio::GroundHeatExchanger_HorizontalTrenchFields::EvapotranspirationGroundCoverParameter,
                       evapotranspirationGroundCoverParameter);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
