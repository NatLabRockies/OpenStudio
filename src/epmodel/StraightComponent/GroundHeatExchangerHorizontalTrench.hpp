/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERHORIZONTALTRENCH_HPP
#define EPMODEL_GROUNDHEATEXCHANGERHORIZONTALTRENCH_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/core/Deprecated.hpp>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ModelObject;

  namespace detail {
    class GroundHeatExchangerHorizontalTrench_Impl;
  }

/** \brief A horizontal-trench ground heat exchanger.
 *
 * \par EnergyPlus object
 * \epobject{group-condenser-equipment.html#groundheatexchangerhorizontaltrench,GroundHeatExchanger:HorizontalTrench}
 *
 * \par Important behavior
 * Undisturbed-ground model links and scalar trench fields map directly to EnergyPlus; plant placement is supply-side only.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::GroundHeatExchangerHorizontalTrench</code>.
 *
 * \par Known limitations
 * No additional type-specific limitation is known beyond shared straight-component topology.
 */
  class EPMODEL_API GroundHeatExchangerHorizontalTrench : public StraightComponent
  {
   public:
    explicit GroundHeatExchangerHorizontalTrench(const Model& model);
    explicit GroundHeatExchangerHorizontalTrench(const Model& model, const ModelObject& undisturbedGroundTemperatureModel);

    virtual ~GroundHeatExchangerHorizontalTrench() override = default;
    GroundHeatExchangerHorizontalTrench(const GroundHeatExchangerHorizontalTrench& other) = default;
    GroundHeatExchangerHorizontalTrench(GroundHeatExchangerHorizontalTrench&& other) = default;
    GroundHeatExchangerHorizontalTrench& operator=(const GroundHeatExchangerHorizontalTrench&) = default;
    GroundHeatExchangerHorizontalTrench& operator=(GroundHeatExchangerHorizontalTrench&&) = default;

    static IddObjectType iddObjectType();

    OS_DEPRECATED(3, 6, 0) static std::vector<std::string> groundTemperatureModelValues();

    double designFlowRate() const;
    bool setDesignFlowRate(double designFlowRate);

    double trenchLengthinPipeAxialDirection() const;
    bool setTrenchLengthinPipeAxialDirection(double trenchLengthinPipeAxialDirection);

    int numberofTrenches() const;
    bool setNumberofTrenches(int numberofTrenches);

    double horizontalSpacingBetweenPipes() const;
    bool setHorizontalSpacingBetweenPipes(double horizontalSpacingBetweenPipes);

    double pipeInnerDiameter() const;
    bool setPipeInnerDiameter(double pipeInnerDiameter);

    double pipeOuterDiameter() const;
    bool setPipeOuterDiameter(double pipeOuterDiameter);

    double burialDepth() const;
    bool setBurialDepth(double burialDepth);

    double soilThermalConductivity() const;
    bool setSoilThermalConductivity(double soilThermalConductivity);

    double soilDensity() const;
    bool setSoilDensity(double soilDensity);

    double soilSpecificHeat() const;
    bool setSoilSpecificHeat(double soilSpecificHeat);

    double pipeThermalConductivity() const;
    bool setPipeThermalConductivity(double pipeThermalConductivity);

    double pipeDensity() const;
    bool setPipeDensity(double pipeDensity);

    double pipeSpecificHeat() const;
    bool setPipeSpecificHeat(double pipeSpecificHeat);

    double soilMoistureContentPercent() const;
    bool setSoilMoistureContentPercent(double soilMoistureContentPercent);

    double soilMoistureContentPercentatSaturation() const;
    bool setSoilMoistureContentPercentatSaturation(double soilMoistureContentPercentatSaturation);

    double evapotranspirationGroundCoverParameter() const;
    bool setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter);

    OS_DEPRECATED(3, 6, 0) std::string groundTemperatureModel() const;
    OS_DEPRECATED(3, 6, 0) bool isGroundTemperatureModelDefaulted() const;
    OS_DEPRECATED(3, 6, 0) double kusudaAchenbachAverageSurfaceTemperature() const;
    OS_DEPRECATED(3, 6, 0) double kusudaAchenbachAverageAmplitudeofSurfaceTemperature() const;
    OS_DEPRECATED(3, 6, 0) double kusudaAchenbachPhaseShiftofMinimumSurfaceTemperature() const;

    ModelObject undisturbedGroundTemperatureModel() const;

    OS_DEPRECATED(3, 6, 0) bool setGroundTemperatureModel(const std::string& groundTemperatureModel);
    OS_DEPRECATED(3, 6, 0) void resetGroundTemperatureModel();
    OS_DEPRECATED(3, 6, 0) bool setKusudaAchenbachAverageSurfaceTemperature(double kusudaAchenbachAverageSurfaceTemperature);
    OS_DEPRECATED(3, 6, 0) bool setKusudaAchenbachAverageAmplitudeofSurfaceTemperature(double kusudaAchenbachAverageAmplitudeofSurfaceTemperature);
    OS_DEPRECATED(3, 6, 0) bool setKusudaAchenbachPhaseShiftofMinimumSurfaceTemperature(double kusudaAchenbachPhaseShiftofMinimumSurfaceTemperature);

    bool setUndisturbedGroundTemperatureModel(const ModelObject& undisturbedGroundTemperatureModel);

   protected:
    using ImplType = detail::GroundHeatExchangerHorizontalTrench_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatExchangerHorizontalTrench(std::shared_ptr<detail::GroundHeatExchangerHorizontalTrench_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.GroundHeatExchangerHorizontalTrench");
  };

  using OptionalGroundHeatExchangerHorizontalTrench = boost::optional<GroundHeatExchangerHorizontalTrench>;
  using GroundHeatExchangerHorizontalTrenchVector = std::vector<GroundHeatExchangerHorizontalTrench>;

}  // namespace epmodel
}  // namespace openstudio

#endif
