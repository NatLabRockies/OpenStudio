/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCONDENSERAIRCOOLED_HPP
#define EPMODEL_REFRIGERATIONCONDENSERAIRCOOLED_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RefrigerationCondenserAirCooled_Impl;
  }

/** \brief Defines an air-cooled refrigeration condenser.
 *
 * \par EnergyPlus object
 * \epobject{group-refrigeration.html#refrigerationcondenseraircooled,Refrigeration:Condenser:AirCooled}
 *
 * \par Important behavior
 * Subcooling, fan control, fan power, airflow, refrigerant inventory, and end-use fields map directly to the condenser object.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::RefrigerationCondenserAirCooled</code>.
 * <b>Not yet available:</b> Model's air-inlet thermal-zone, heat-rejection curve, and refrigeration-system relationship methods are not exposed.
 *
 * \par Known limitations
 * The condenser does not own the refrigeration system or compressor relationships.
 */
  class EPMODEL_API RefrigerationCondenserAirCooled : public ParentObject
  {
   public:
    explicit RefrigerationCondenserAirCooled(const Model& model);

    virtual ~RefrigerationCondenserAirCooled() override = default;
    RefrigerationCondenserAirCooled(const RefrigerationCondenserAirCooled& other) = default;
    RefrigerationCondenserAirCooled(RefrigerationCondenserAirCooled&& other) = default;
    RefrigerationCondenserAirCooled& operator=(const RefrigerationCondenserAirCooled&) = default;
    RefrigerationCondenserAirCooled& operator=(RefrigerationCondenserAirCooled&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> condenserFanSpeedControlTypeValues();


    /** @name Getters */
    //@{
    double ratedSubcoolingTemperatureDifference() const;
    bool isRatedSubcoolingTemperatureDifferenceDefaulted() const;
    bool setRatedSubcoolingTemperatureDifference(double ratedSubcoolingTemperatureDifference);
    void resetRatedSubcoolingTemperatureDifference();

    std::string condenserFanSpeedControlType() const;
    bool isCondenserFanSpeedControlTypeDefaulted() const;
    bool setCondenserFanSpeedControlType(const std::string& condenserFanSpeedControlType);
    void resetCondenserFanSpeedControlType();

    double ratedFanPower() const;
    bool isRatedFanPowerDefaulted() const;
    bool setRatedFanPower(double ratedFanPower);
    void resetRatedFanPower();

    double minimumFanAirFlowRatio() const;
    bool isMinimumFanAirFlowRatioDefaulted() const;
    bool setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio);
    void resetMinimumFanAirFlowRatio();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    double condenserRefrigerantOperatingChargeInventory() const;
    bool isCondenserRefrigerantOperatingChargeInventoryDefaulted() const;
    bool setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory);
    void resetCondenserRefrigerantOperatingChargeInventory();

    double condensateReceiverRefrigerantInventory() const;
    bool isCondensateReceiverRefrigerantInventoryDefaulted() const;
    bool setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory);
    void resetCondensateReceiverRefrigerantInventory();

    double condensatePipingRefrigerantInventory() const;
    bool isCondensatePipingRefrigerantInventoryDefaulted() const;
    bool setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory);
    void resetCondensatePipingRefrigerantInventory();
    //@}

   protected:
    using ImplType = detail::RefrigerationCondenserAirCooled_Impl;

    explicit RefrigerationCondenserAirCooled(std::shared_ptr<detail::RefrigerationCondenserAirCooled_Impl> impl);

    friend class detail::RefrigerationCondenserAirCooled_Impl;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

   private:
    REGISTER_LOGGER("openstudio.epmodel.RefrigerationCondenserAirCooled");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
