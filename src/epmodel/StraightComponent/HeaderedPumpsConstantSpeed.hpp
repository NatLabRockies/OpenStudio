/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEADEREDPUMPSCONSTANTSPEED_HPP
#define EPMODEL_HEADEREDPUMPSCONSTANTSPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HeaderedPumpsConstantSpeed_Impl;
  }

  class EPMODEL_API HeaderedPumpsConstantSpeed : public StraightComponent
  {
   public:
    explicit HeaderedPumpsConstantSpeed(const Model& model);

    virtual ~HeaderedPumpsConstantSpeed() override = default;
    HeaderedPumpsConstantSpeed(const HeaderedPumpsConstantSpeed& other) = default;
    HeaderedPumpsConstantSpeed(HeaderedPumpsConstantSpeed&& other) = default;
    HeaderedPumpsConstantSpeed& operator=(const HeaderedPumpsConstantSpeed&) = default;
    HeaderedPumpsConstantSpeed& operator=(HeaderedPumpsConstantSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> flowSequencingControlSchemeValues();
    static std::vector<std::string> pumpControlTypeValues();
    static std::vector<std::string> designPowerSizingMethodValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::HeaderedPumpsConstantSpeed scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: totalRatedFlowRate/ratedPumpHead/ratedPowerConsumption APIs map to E+ HeaderedPumps:ConstantSpeed TotalDesignFlowRate/DesignPumpHead/DesignPowerConsumption.
    // - Field Mapping: pumpFlowRateSchedule, thermalZone, and inlet/outlet node name fields are relationship-like fields and are excluded in this scalar-only pass.
    // - ForwardTranslator evidence: ForwardTranslateHeaderedPumpsConstantSpeed.cpp maps the preserved API names to these E+ fields.
    // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.

    boost::optional<double> totalRatedFlowRate() const;
    bool isTotalRatedFlowRateAutosized() const;
    bool setTotalRatedFlowRate(double totalRatedFlowRate);
    void autosizeTotalRatedFlowRate();
    boost::optional<double> autosizedTotalRatedFlowRate() const;

    int numberofPumpsinBank() const;
    bool setNumberofPumpsinBank(int numberofPumpsinBank);

    std::string flowSequencingControlScheme() const;
    bool setFlowSequencingControlScheme(const std::string& flowSequencingControlScheme);

    double ratedPumpHead() const;
    bool setRatedPumpHead(double ratedPumpHead);

    boost::optional<double> ratedPowerConsumption() const;
    bool isRatedPowerConsumptionAutosized() const;
    bool setRatedPowerConsumption(double ratedPowerConsumption);
    void autosizeRatedPowerConsumption();
    boost::optional<double> autosizedRatedPowerConsumption() const;

    double motorEfficiency() const;
    bool setMotorEfficiency(double motorEfficiency);

    double fractionofMotorInefficienciestoFluidStream() const;
    bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);

    std::string pumpControlType() const;
    bool setPumpControlType(const std::string& pumpControlType);

    double skinLossRadiativeFraction() const;
    bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);

    std::string designPowerSizingMethod() const;
    bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

    double designElectricPowerPerUnitFlowRate() const;
    bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);

    double designShaftPowerPerUnitFlowRatePerUnitHead() const;
    bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

   protected:
    using ImplType = detail::HeaderedPumpsConstantSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeaderedPumpsConstantSpeed(std::shared_ptr<detail::HeaderedPumpsConstantSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
