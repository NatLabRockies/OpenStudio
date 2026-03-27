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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical boiler-steam scalar surface is present, and the node topology is mostly inherited, but explicit relationship helpers remain limited.
    // - Canonical Counterpart: openstudio::model::BoilerSteam.
    // - Implemented Parity: The preserved scalar API covers the boiler performance, flow, curve, sizing, and end-use fields with matching default/autosize behavior.
    // - Documented Delta: Relationship helpers beyond the inherited StraightComponent node contract remain intentionally limited in this pass.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `Boiler:Steam` scalar fields used by the forward translator.
    // - Evidence: `src/model/BoilerSteam.hpp` and `src/energyplus/ForwardTranslator/ForwardTranslateBoilerSteam.cpp`.
    // - Remaining Parity Work: Add any remaining relationship convenience around the inlet and outlet nodes without changing the preserved scalar signatures.
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
