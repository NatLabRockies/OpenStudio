/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERFLUIDTOFLUID_HPP
#define EPMODEL_HEATEXCHANGERFLUIDTOFLUID_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class Node;

  namespace detail {
    class HeatExchangerFluidToFluid_Impl;
  }

  /** \brief Represents a fluid-to-fluid heat exchanger between two plant loops.
   *
   * \par EnergyPlus object
   * \epobject{group-condenser-equipment.html#heatexchangerfluidtofluid,HeatExchanger:FluidToFluid}
   *
   * \par Important behavior
   * Component classification and reported loop fuel types follow the selected
   * <code>controlType()</code> and the attached secondary plant loop.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::HeatExchangerFluidToFluid</code>. No known public
   * API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API HeatExchangerFluidToFluid : public WaterToWaterComponent
  {
   public:
    explicit HeatExchangerFluidToFluid(const Model& model);

    virtual ~HeatExchangerFluidToFluid() override = default;
    HeatExchangerFluidToFluid(const HeatExchangerFluidToFluid& other) = default;
    HeatExchangerFluidToFluid(HeatExchangerFluidToFluid&& other) = default;
    HeatExchangerFluidToFluid& operator=(const HeatExchangerFluidToFluid&) = default;
    HeatExchangerFluidToFluid& operator=(HeatExchangerFluidToFluid&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatExchangeModelTypeValues();
    static std::vector<std::string> controlTypeValues();
    static std::vector<std::string> heatTransferMeteringEndUseTypeValues();
    static std::vector<std::string> componentOverrideCoolingControlTemperatureModeValues();

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    boost::optional<double> loopDemandSideDesignFlowRate() const;
    bool isLoopDemandSideDesignFlowRateAutosized() const;
    bool setLoopDemandSideDesignFlowRate(double loopDemandSideDesignFlowRate);
    void autosizeLoopDemandSideDesignFlowRate();

    boost::optional<double> loopSupplySideDesignFlowRate() const;
    bool isLoopSupplySideDesignFlowRateAutosized() const;
    bool setLoopSupplySideDesignFlowRate(double loopSupplySideDesignFlowRate);
    void autosizeLoopSupplySideDesignFlowRate();

    std::string heatExchangeModelType() const;
    bool isHeatExchangeModelTypeDefaulted() const;
    bool setHeatExchangeModelType(const std::string& heatExchangeModelType);
    void resetHeatExchangeModelType();

    boost::optional<double> heatExchangerUFactorTimesAreaValue() const;
    bool isHeatExchangerUFactorTimesAreaValueAutosized() const;
    bool setHeatExchangerUFactorTimesAreaValue(double heatExchangerUFactorTimesAreaValue);
    void autosizeHeatExchangerUFactorTimesAreaValue();

    std::string controlType() const;
    bool isControlTypeDefaulted() const;
    bool setControlType(const std::string& controlType);
    void resetControlType();

    double minimumTemperatureDifferencetoActivateHeatExchanger() const;
    bool isMinimumTemperatureDifferencetoActivateHeatExchangerDefaulted() const;
    bool setMinimumTemperatureDifferencetoActivateHeatExchanger(double minimumTemperatureDifferencetoActivateHeatExchanger);
    void resetMinimumTemperatureDifferencetoActivateHeatExchanger();

    std::string heatTransferMeteringEndUseType() const;
    bool isHeatTransferMeteringEndUseTypeDefaulted() const;
    bool setHeatTransferMeteringEndUseType(const std::string& heatTransferMeteringEndUseType);
    void resetHeatTransferMeteringEndUseType();

    boost::optional<Node> componentOverrideLoopSupplySideInletNode() const;
    bool setComponentOverrideLoopSupplySideInletNode(const Node& node);
    void resetComponentOverrideLoopSupplySideInletNode();

    boost::optional<Node> componentOverrideLoopDemandSideInletNode() const;
    bool setComponentOverrideLoopDemandSideInletNode(const Node& node);
    void resetComponentOverrideLoopDemandSideInletNode();

    std::string componentOverrideCoolingControlTemperatureMode() const;
    bool isComponentOverrideCoolingControlTemperatureModeDefaulted() const;
    bool setComponentOverrideCoolingControlTemperatureMode(const std::string& componentOverrideCoolingControlTemperatureMode);
    void resetComponentOverrideCoolingControlTemperatureMode();

    double sizingFactor() const;
    bool isSizingFactorDefaulted() const;
    bool setSizingFactor(double sizingFactor);
    void resetSizingFactor();

    boost::optional<double> operationMinimumTemperatureLimit() const;
    bool setOperationMinimumTemperatureLimit(double operationMinimumTemperatureLimit);
    void resetOperationMinimumTemperatureLimit();

    boost::optional<double> operationMaximumTemperatureLimit() const;
    bool setOperationMaximumTemperatureLimit(double operationMaximumTemperatureLimit);
    void resetOperationMaximumTemperatureLimit();

    boost::optional<double> autosizedLoopDemandSideDesignFlowRate() const;
    boost::optional<double> autosizedLoopSupplySideDesignFlowRate() const;
    boost::optional<double> autosizedHeatExchangerUFactorTimesAreaValue() const;

   protected:
    using ImplType = detail::HeatExchangerFluidToFluid_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatExchangerFluidToFluid(std::shared_ptr<detail::HeatExchangerFluidToFluid_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
