/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BOILERSTEAM_HPP
#define EPMODEL_BOILERSTEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class BoilerSteam_Impl;
  }

  /**
   * \brief Steam boiler with fuel, efficiency, flow, pressure, sizing, curve, and end-use controls.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-plant-equipment.html#boilersteam,Boiler:Steam}.
   *
   * \par Important behavior
   * Scalar values, including the part-load fuel-use coefficients, are stored directly on the boiler object; plant
   * connectivity uses the inherited straight-component node relationship.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::BoilerSteam`. The boiler performance, flow, part-load coefficient, sizing, and end-use scalar
   * APIs are represented with their default/autosize behavior.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the inherited plant-node contract.
   */
  class EPMODEL_API BoilerSteam : public StraightComponent
  {
   public:
    explicit BoilerSteam(const Model& model);

    virtual ~BoilerSteam() override = default;
    BoilerSteam(const BoilerSteam& other) = default;
    BoilerSteam(BoilerSteam&& other) = default;
    BoilerSteam& operator=(const BoilerSteam&) = default;
    BoilerSteam& operator=(BoilerSteam&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fuelTypeValues();

    std::string fuelType() const;
    bool setFuelType(const std::string& fuelType);

    bool addToNode(Node& node);

    boost::optional<double> maximumOperatingPressure() const;
    bool setMaximumOperatingPressure(double maximumOperatingPressure);
    void resetMaximumOperatingPressure();

    boost::optional<double> theoreticalEfficiency() const;
    bool setTheoreticalEfficiency(double theoreticalEfficiency);
    void resetTheoreticalEfficiency();

    boost::optional<double> designOutletSteamTemperature() const;
    bool setDesignOutletSteamTemperature(double designOutletSteamTemperature);
    void resetDesignOutletSteamTemperature();

    boost::optional<double> nominalCapacity() const;
    bool setNominalCapacity(double nominalCapacity);
    void resetNominalCapacity();
    void autosizeNominalCapacity();
    bool isNominalCapacityAutosized() const;
    boost::optional<double> autosizedNominalCapacity() const;

    boost::optional<double> minimumPartLoadRatio() const;
    bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
    void resetMinimumPartLoadRatio();

    boost::optional<double> maximumPartLoadRatio() const;
    bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
    void resetMaximumPartLoadRatio();

    boost::optional<double> optimumPartLoadRatio() const;
    bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
    void resetOptimumPartLoadRatio();

    boost::optional<double> coefficient1ofFuelUseFunctionofPartLoadRatioCurve() const;
    bool setCoefficient1ofFuelUseFunctionofPartLoadRatioCurve(double coefficient1ofFuelUseFunctionofPartLoadRatioCurve);
    void resetCoefficient1ofFuelUseFunctionofPartLoadRatioCurve();

    boost::optional<double> coefficient2ofFuelUseFunctionofPartLoadRatioCurve() const;
    bool setCoefficient2ofFuelUseFunctionofPartLoadRatioCurve(double coefficient2ofFuelUseFunctionofPartLoadRatioCurve);
    void resetCoefficient2ofFuelUseFunctionofPartLoadRatioCurve();

    boost::optional<double> coefficient3ofFuelUseFunctionofPartLoadRatioCurve() const;
    bool setCoefficient3ofFuelUseFunctionofPartLoadRatioCurve(double coefficient3ofFuelUseFunctionofPartLoadRatioCurve);
    void resetCoefficient3ofFuelUseFunctionofPartLoadRatioCurve();

    double sizingFactor() const;
    bool setSizingFactor(double sizingFactor);
    void resetSizingFactor();
    bool isSizingFactorDefaulted() const;

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

   protected:
    using ImplType = detail::BoilerSteam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit BoilerSteam(std::shared_ptr<detail::BoilerSteam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
