/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERVERTICAL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERVERTICAL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ModelObject;

  namespace detail {
    class GroundHeatExchangerVertical_Impl;
  }

/** \brief One g-function value pair for a vertical ground heat exchanger.
 *
 * \par EnergyPlus object
 * No standalone EnergyPlus object. Each instance exposes one extensible row of
 * the parent \epobject{group-condenser-equipment.html#groundheatexchangerresponsefactors,GroundHeatExchanger:ResponseFactors} object: g-Function
 * Ln(T/Ts) Value 1 and g-Function g Value 1.
 *
 * \par Important behavior
 * The logarithmic time value and g-function value are stored as a value object used by GroundHeatExchangerVertical extensible rows.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::GFunction</code>.
 *
 * \par Known limitations
 * The value is an immutable, detached entry. Use
 * <code>GroundHeatExchangerVertical::addGFunction(...)</code> to store it.
 */
  class EPMODEL_API GFunction
  {
   public:
    GFunction(double lnValue, double gValue);
    double lnValue() const;
    double gValue() const;

   private:
    double m_lnValue;
    double m_gValue;
  };

/** \brief A vertical ground heat exchanger.
 *
 * \par EnergyPlus object
 * Composite wrapper for \epobject{group-condenser-equipment.html#groundheatexchangersystem,GroundHeatExchanger:System},
 * \epobject{group-condenser-equipment.html#groundheatexchangerverticalproperties,GroundHeatExchanger:Vertical:Properties}, and
 * \epobject{group-condenser-equipment.html#groundheatexchangerresponsefactors,GroundHeatExchanger:ResponseFactors}.
 *
 * \par Important behavior
 * The wrapper projects GroundHeatExchanger:System, GroundHeatExchanger:Vertical:Properties, and GroundHeatExchanger:ResponseFactors storage; g-functions are stored as response-factor extensible rows.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::GroundHeatExchangerVertical</code>.
 *
 * \par Known limitations
 * groundTemperature() and maximumLengthofSimulation() have no direct EnergyPlus fields, and undisturbed-ground models are limited to supported EnergyPlus object-list types.
 */
  class EPMODEL_API GroundHeatExchangerVertical : public StraightComponent
  {
   public:
    explicit GroundHeatExchangerVertical(const Model& model);
    explicit GroundHeatExchangerVertical(const Model& model, const ModelObject& undisturbedGroundTemperatureModel);

    virtual ~GroundHeatExchangerVertical() override = default;
    GroundHeatExchangerVertical(const GroundHeatExchangerVertical& other) = default;
    GroundHeatExchangerVertical(GroundHeatExchangerVertical&& other) = default;
    GroundHeatExchangerVertical& operator=(const GroundHeatExchangerVertical&) = default;
    GroundHeatExchangerVertical& operator=(GroundHeatExchangerVertical&&) = default;

    static IddObjectType iddObjectType();


    bool addGFunction(double gFunctionLN, double gFunctionGValue);
    bool addGFunction(GFunction gFunc);
    void removeGFunction(int groupIndex);
    void removeAllGFunctions();
    std::vector<GFunction> gFunctions();

    boost::optional<double> designFlowRate() const;
    bool setDesignFlowRate(double designFlowRate);

    boost::optional<double> groundThermalConductivity() const;
    bool setGroundThermalConductivity(double groundThermalConductivity);
    void resetGroundThermalConductivity();

    boost::optional<double> groundThermalHeatCapacity() const;
    bool setGroundThermalHeatCapacity(double groundThermalHeatCapacity);
    void resetGroundThermalHeatCapacity();

    double boreHoleTopDepth() const;
    bool setBoreHoleTopDepth(double boreHoleTopDepth);

    boost::optional<double> boreHoleLength() const;
    bool setBoreHoleLength(double boreHoleLength);
    void resetBoreHoleLength();

    boost::optional<double> boreHoleRadius() const;
    bool setBoreHoleRadius(double boreHoleRadius);
    void resetBoreHoleRadius();

    boost::optional<double> groutThermalConductivity() const;
    bool setGroutThermalConductivity(double groutThermalConductivity);
    void resetGroutThermalConductivity();

    boost::optional<double> pipeThermalConductivity() const;
    bool setPipeThermalConductivity(double pipeThermalConductivity);
    void resetPipeThermalConductivity();

    boost::optional<double> pipeOutDiameter() const;
    bool setPipeOutDiameter(double pipeOutDiameter);
    void resetPipeOutDiameter();

    boost::optional<double> uTubeDistance() const;
    bool setUTubeDistance(double uTubeDistance);
    void resetUTubeDistance();

    boost::optional<double> pipeThickness() const;
    bool setPipeThickness(double pipeThickness);
    void resetPipeThickness();

    boost::optional<int> numberofBoreHoles() const;
    bool setNumberofBoreHoles(int numberofBoreHoles);
    void resetNumberofBoreHoles();

    double gFunctionReferenceRatio() const;
    bool isGFunctionReferenceRatioDefaulted() const;
    bool setGFunctionReferenceRatio(double gFunctionReferenceRatio);
    void resetGFunctionReferenceRatio();

    ModelObject undisturbedGroundTemperatureModel() const;
    bool setUndisturbedGroundTemperatureModel(const ModelObject& undisturbedGroundTemperatureModel);

   protected:
    using ImplType = detail::GroundHeatExchangerVertical_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatExchangerVertical(std::shared_ptr<detail::GroundHeatExchangerVertical_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.GroundHeatExchangerVertical");
  };

  using OptionalGroundHeatExchangerVertical = boost::optional<GroundHeatExchangerVertical>;
  using GroundHeatExchangerVerticalVector = std::vector<GroundHeatExchangerVertical>;

}  // namespace epmodel
}  // namespace openstudio

#endif
