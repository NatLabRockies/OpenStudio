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

/** \brief Defines an air-cooled gas cooler for a transcritical refrigeration system.
 *
 * \par EnergyPlus object
 * \epobject{group-refrigeration.html#refrigerationgascooleraircooled,Refrigeration:GasCooler:AirCooled}
 *
 * \par Important behavior
 * Fan control, transition and condensing temperatures, approach values, airflow, refrigerant inventory, and end-use fields map directly to the object.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::RefrigerationGasCoolerAirCooled</code>.
 * <b>Not yet available:</b> Model's rated-total-heat-rejection curve relationship is not exposed.
 *
 * \par Known limitations
 * The gas cooler does not own the refrigeration system or compressor relationships.
 */
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
