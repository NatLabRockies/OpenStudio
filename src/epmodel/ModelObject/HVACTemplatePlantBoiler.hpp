/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTBOILER_HPP
#define EPMODEL_HVACTEMPLATEPLANTBOILER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplatePlantBoiler_Impl;
  }

  class EPMODEL_API HVACTemplatePlantBoiler : public ModelObject
  {
   public:
    explicit HVACTemplatePlantBoiler(const Model& model);

    virtual ~HVACTemplatePlantBoiler() override = default;
    HVACTemplatePlantBoiler(const HVACTemplatePlantBoiler& other) = default;
    HVACTemplatePlantBoiler(HVACTemplatePlantBoiler&& other) = default;
    HVACTemplatePlantBoiler& operator=(const HVACTemplatePlantBoiler&) = default;
    HVACTemplatePlantBoiler& operator=(HVACTemplatePlantBoiler&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> boilerTypeValues();
    static std::vector<std::string> fuelTypeValues();
    static std::vector<std::string> templatePlantLoopTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:Plant:Boiler non-name scalar fields.
    // - TODO(parity): Keep object-reference linkage behavior out of this scalar-only scaffold pass.
    std::string boilerType() const;
    bool setBoilerType(const std::string& boilerType);

    boost::optional<double> capacity() const;
    bool isCapacityDefaulted() const;
    bool isCapacityAutosized() const;
    bool setCapacity(double capacity);
    void resetCapacity();
    void autosizeCapacity();

    double efficiency() const;
    bool isEfficiencyDefaulted() const;
    bool setEfficiency(double efficiency);
    void resetEfficiency();

    boost::optional<std::string> fuelType() const;
    bool setFuelType(const std::string& fuelType);
    void resetFuelType();

    boost::optional<std::string> priority() const;
    bool setPriority(const std::string& priority);
    void resetPriority();

    double sizingFactor() const;
    bool isSizingFactorDefaulted() const;
    bool setSizingFactor(double sizingFactor);
    void resetSizingFactor();

    double minimumPartLoadRatio() const;
    bool isMinimumPartLoadRatioDefaulted() const;
    bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
    void resetMinimumPartLoadRatio();

    double maximumPartLoadRatio() const;
    bool isMaximumPartLoadRatioDefaulted() const;
    bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
    void resetMaximumPartLoadRatio();

    double optimumPartLoadRatio() const;
    bool isOptimumPartLoadRatioDefaulted() const;
    bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
    void resetOptimumPartLoadRatio();

    double waterOutletUpperTemperatureLimit() const;
    bool isWaterOutletUpperTemperatureLimitDefaulted() const;
    bool setWaterOutletUpperTemperatureLimit(double waterOutletUpperTemperatureLimit);
    void resetWaterOutletUpperTemperatureLimit();

    boost::optional<std::string> templatePlantLoopType() const;
    bool setTemplatePlantLoopType(const std::string& templatePlantLoopType);
    void resetTemplatePlantLoopType();

   protected:
    using ImplType = detail::HVACTemplatePlantBoiler_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplatePlantBoiler(std::shared_ptr<detail::HVACTemplatePlantBoiler_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
