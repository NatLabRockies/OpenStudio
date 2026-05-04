/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONGASCOOLERAIRCOOLED_HPP
#define EPMODEL_REFRIGERATIONGASCOOLERAIRCOOLED_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RefrigerationGasCoolerAirCooled_Impl;
  }

  class EPMODEL_API RefrigerationGasCoolerAirCooled : public ParentObject
  {
   public:
    explicit RefrigerationGasCoolerAirCooled(const Model& model);

    virtual ~RefrigerationGasCoolerAirCooled() override = default;
    RefrigerationGasCoolerAirCooled(const RefrigerationGasCoolerAirCooled& other) = default;
    RefrigerationGasCoolerAirCooled(RefrigerationGasCoolerAirCooled&& other) = default;
    RefrigerationGasCoolerAirCooled& operator=(const RefrigerationGasCoolerAirCooled&) = default;
    RefrigerationGasCoolerAirCooled& operator=(RefrigerationGasCoolerAirCooled&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> gasCoolerFanSpeedControlTypeValues();

    // Schema Alignment Notes:
    // - API: preserve openstudio::model::RefrigerationGasCoolerAirCooled scalar accessor names/signatures while keeping the epmodel type under ParentObject.
    // - Field Mapping: ForwardTranslateRefrigerationGasCoolerAirCooled.cpp maps the retained scalars to the EnergyPlus Refrigeration:GasCooler:AirCooled fields via
    //   Refrigeration_GasCooler_AirCooledFields.
    // - Field Mapping: the rated total heat rejection rate curve and air inlet node/zone references describe richer object relationships and are intentionally
    //   absent from this scalar-only scaffold.

    /** @name Getters */
    //@{
    std::string gasCoolerFanSpeedControlType() const;
    bool isGasCoolerFanSpeedControlTypeDefaulted() const;
    bool setGasCoolerFanSpeedControlType(const std::string& gasCoolerFanSpeedControlType);
    void resetGasCoolerFanSpeedControlType();

    double ratedFanPower() const;
    bool isRatedFanPowerDefaulted() const;
    bool setRatedFanPower(double ratedFanPower);
    void resetRatedFanPower();

    double minimumFanAirFlowRatio() const;
    bool isMinimumFanAirFlowRatioDefaulted() const;
    bool setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio);
    void resetMinimumFanAirFlowRatio();

    double transitionTemperature() const;
    bool isTransitionTemperatureDefaulted() const;
    bool setTransitionTemperature(double transitionTemperature);
    void resetTransitionTemperature();

    double transcriticalApproachTemperature() const;
    bool isTranscriticalApproachTemperatureDefaulted() const;
    bool setTranscriticalApproachTemperature(double transcriticalApproachTemperature);
    void resetTranscriticalApproachTemperature();

    double subcriticalTemperatureDifference() const;
    bool isSubcriticalTemperatureDifferenceDefaulted() const;
    bool setSubcriticalTemperatureDifference(double subcriticalTemperatureDifference);
    void resetSubcriticalTemperatureDifference();

    double minimumCondensingTemperature() const;
    bool isMinimumCondensingTemperatureDefaulted() const;
    bool setMinimumCondensingTemperature(double minimumCondensingTemperature);
    void resetMinimumCondensingTemperature();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    double gasCoolerRefrigerantOperatingChargeInventory() const;
    bool isGasCoolerRefrigerantOperatingChargeInventoryDefaulted() const;
    bool setGasCoolerRefrigerantOperatingChargeInventory(double gasCoolerRefrigerantOperatingChargeInventory);
    void resetGasCoolerRefrigerantOperatingChargeInventory();

    double gasCoolerReceiverRefrigerantInventory() const;
    bool isGasCoolerReceiverRefrigerantInventoryDefaulted() const;
    bool setGasCoolerReceiverRefrigerantInventory(double gasCoolerReceiverRefrigerantInventory);
    void resetGasCoolerReceiverRefrigerantInventory();

    double gasCoolerOutletPipingRefrigerantInventory() const;
    bool isGasCoolerOutletPipingRefrigerantInventoryDefaulted() const;
    bool setGasCoolerOutletPipingRefrigerantInventory(double gasCoolerOutletPipingRefrigerantInventory);
    void resetGasCoolerOutletPipingRefrigerantInventory();
    //@}

   protected:
    using ImplType = detail::RefrigerationGasCoolerAirCooled_Impl;

    explicit RefrigerationGasCoolerAirCooled(std::shared_ptr<detail::RefrigerationGasCoolerAirCooled_Impl> impl);

    friend class detail::RefrigerationGasCoolerAirCooled_Impl;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

   private:
    REGISTER_LOGGER("openstudio.epmodel.RefrigerationGasCoolerAirCooled");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
