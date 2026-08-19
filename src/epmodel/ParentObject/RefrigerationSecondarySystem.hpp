/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONSECONDARYSYSTEM_HPP
#define EPMODEL_REFRIGERATIONSECONDARYSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ThermalZone;

  namespace detail {
    class RefrigerationSecondarySystem_Impl;
  }

/** \brief Defines a secondary refrigeration fluid system.
 *
 * \par EnergyPlus object
 * \epobject{group-refrigeration.html#refrigerationsecondarysystem,Refrigeration:SecondarySystem}
 *
 * \par Important behavior
 * Circulating-fluid, evaporator, pump, phase-change, pipe-distribution, and control fields are stored directly on the secondary-system object.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::RefrigerationSecondarySystem</code>.
 * <b>Not yet available:</b> Case, walk-in, and air-chiller collections, refrigeration-system attachment, glycol concentration, and pump-curve relationships are not exposed.
 *
 * \par Known limitations
 * Cases and the primary refrigeration system reference this object; they are not owned by it.
 */
  class EPMODEL_API RefrigerationSecondarySystem : public ParentObject
  {
   public:
    explicit RefrigerationSecondarySystem(const Model& model);

    virtual ~RefrigerationSecondarySystem() override = default;
    RefrigerationSecondarySystem(const RefrigerationSecondarySystem& other) = default;
    RefrigerationSecondarySystem(RefrigerationSecondarySystem&& other) = default;
    RefrigerationSecondarySystem& operator=(const RefrigerationSecondarySystem&) = default;
    RefrigerationSecondarySystem& operator=(RefrigerationSecondarySystem&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> circulatingFluidNameValues();
    static std::vector<std::string> pumpDriveTypeValues();


    /** @name Field accessors */
    //@{
    std::string circulatingFluidName() const;
    bool setCirculatingFluidName(const std::string& circulatingFluidName);

    boost::optional<double> evaporatorCapacity() const;
    bool setEvaporatorCapacity(double evaporatorCapacity);
    void resetEvaporatorCapacity();

    boost::optional<double> evaporatorFlowRateforSecondaryFluid() const;
    bool setEvaporatorFlowRateforSecondaryFluid(double evaporatorFlowRateforSecondaryFluid);
    void resetEvaporatorFlowRateforSecondaryFluid();

    double evaporatorEvaporatingTemperature() const;
    bool setEvaporatorEvaporatingTemperature(double evaporatorEvaporatingTemperature);

    double evaporatorApproachTemperatureDifference() const;
    bool setEvaporatorApproachTemperatureDifference(double evaporatorApproachTemperatureDifference);

    boost::optional<double> evaporatorRangeTemperatureDifference() const;
    bool setEvaporatorRangeTemperatureDifference(double evaporatorRangeTemperatureDifference);
    void resetEvaporatorRangeTemperatureDifference();

    int numberofPumpsinLoop() const;
    bool isNumberofPumpsinLoopDefaulted() const;
    bool setNumberofPumpsinLoop(int numberofPumpsinLoop);
    void resetNumberofPumpsinLoop();

    boost::optional<double> totalPumpFlowRate() const;
    bool setTotalPumpFlowRate(double totalPumpFlowRate);
    void resetTotalPumpFlowRate();

    boost::optional<double> totalPumpPower() const;
    bool setTotalPumpPower(double totalPumpPower);
    void resetTotalPumpPower();

    boost::optional<double> totalPumpHead() const;
    bool setTotalPumpHead(double totalPumpHead);
    void resetTotalPumpHead();

    double phaseChangeCirculatingRate() const;
    bool isPhaseChangeCirculatingRateDefaulted() const;
    bool setPhaseChangeCirculatingRate(double phaseChangeCirculatingRate);
    void resetPhaseChangeCirculatingRate();

    std::string pumpDriveType() const;
    bool isPumpDriveTypeDefaulted() const;
    bool setPumpDriveType(const std::string& pumpDriveType);
    void resetPumpDriveType();

    double pumpMotorHeattoFluid() const;
    bool isPumpMotorHeattoFluidDefaulted() const;
    bool setPumpMotorHeattoFluid(double pumpMotorHeattoFluid);
    void resetPumpMotorHeattoFluid();

    double sumUADistributionPiping() const;
    bool isSumUADistributionPipingDefaulted() const;
    bool setSumUADistributionPiping(double sumUADistributionPiping);
    void resetSumUADistributionPiping();

    boost::optional<ThermalZone> distributionPipingZone() const;
    bool setDistributionPipingZone(const ThermalZone& thermalZone);
    void resetDistributionPipingZone();

    double sumUAReceiverSeparatorShell() const;
    bool isSumUAReceiverSeparatorShellDefaulted() const;
    bool setSumUAReceiverSeparatorShell(double sumUAReceiverSeparatorShell);
    void resetSumUAReceiverSeparatorShell();

    boost::optional<ThermalZone> receiverSeparatorZone() const;
    bool setReceiverSeparatorZone(const ThermalZone& thermalZone);
    void resetReceiverSeparatorZone();

    double evaporatorRefrigerantInventory() const;
    bool isEvaporatorRefrigerantInventoryDefaulted() const;
    bool setEvaporatorRefrigerantInventory(double evaporatorRefrigerantInventory);
    void resetEvaporatorRefrigerantInventory();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();
    //@}

   protected:
    using ImplType = detail::RefrigerationSecondarySystem_Impl;

    explicit RefrigerationSecondarySystem(std::shared_ptr<detail::RefrigerationSecondarySystem_Impl> impl);

    friend class detail::RefrigerationSecondarySystem_Impl;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

   private:
    REGISTER_LOGGER("openstudio.epmodel.RefrigerationSecondarySystem");
  };

  using OptionalRefrigerationSecondarySystem = boost::optional<RefrigerationSecondarySystem>;
  using RefrigerationSecondarySystemVector = std::vector<RefrigerationSecondarySystem>;

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONSECONDARYSYSTEM_HPP
