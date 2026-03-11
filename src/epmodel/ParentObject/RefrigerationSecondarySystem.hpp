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

  namespace detail {
    class RefrigerationSecondarySystem_Impl;
  }

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

    // Schema Alignment Notes:
    // - API: preserve openstudio::model::RefrigerationSecondarySystem scalar accessor naming/signatures for the numeric and string fields backed by
    //   the EnergyPlus Refrigeration:SecondarySystem object.
    // - Field Mapping: ForwardTranslateRefrigerationSecondarySystem.cpp documents how the retained scalars write to Refrigeration_SecondarySystemFields.
    // - Field Mapping: richer relationship fields (case/walk-in lists, the variable-speed pump curve, zone references, etc.) are handled elsewhere and intentionally
    //   excluded from this scalar-only scaffold.

    /** @name Getters */
    //@{
    std::string circulatingFluidName() const;

    boost::optional<double> evaporatorCapacity() const;

    boost::optional<double> evaporatorFlowRateforSecondaryFluid() const;

    double evaporatorEvaporatingTemperature() const;

    double evaporatorApproachTemperatureDifference() const;

    boost::optional<double> evaporatorRangeTemperatureDifference() const;

    int numberofPumpsinLoop() const;

    bool isNumberofPumpsinLoopDefaulted() const;

    boost::optional<double> totalPumpFlowRate() const;

    boost::optional<double> totalPumpPower() const;

    boost::optional<double> totalPumpHead() const;

    double phaseChangeCirculatingRate() const;

    bool isPhaseChangeCirculatingRateDefaulted() const;

    std::string pumpDriveType() const;

    bool isPumpDriveTypeDefaulted() const;

    double pumpMotorHeattoFluid() const;

    bool isPumpMotorHeattoFluidDefaulted() const;

    double sumUADistributionPiping() const;

    bool isSumUADistributionPipingDefaulted() const;

    double sumUAReceiverSeparatorShell() const;

    bool isSumUAReceiverSeparatorShellDefaulted() const;

    double evaporatorRefrigerantInventory() const;

    bool isEvaporatorRefrigerantInventoryDefaulted() const;

    std::string endUseSubcategory() const;

    bool isEndUseSubcategoryDefaulted() const;
    //@}

    /** @name Setters */
    //@{
    bool setCirculatingFluidName(const std::string& circulatingFluidName);

    bool setEvaporatorCapacity(double evaporatorCapacity);
    void resetEvaporatorCapacity();

    bool setEvaporatorFlowRateforSecondaryFluid(double evaporatorFlowRateforSecondaryFluid);
    void resetEvaporatorFlowRateforSecondaryFluid();

    bool setEvaporatorEvaporatingTemperature(double evaporatorEvaporatingTemperature);

    bool setEvaporatorApproachTemperatureDifference(double evaporatorApproachTemperatureDifference);

    bool setEvaporatorRangeTemperatureDifference(double evaporatorRangeTemperatureDifference);
    void resetEvaporatorRangeTemperatureDifference();

    bool setNumberofPumpsinLoop(int numberofPumpsinLoop);
    void resetNumberofPumpsinLoop();

    bool setTotalPumpFlowRate(double totalPumpFlowRate);
    void resetTotalPumpFlowRate();

    bool setTotalPumpPower(double totalPumpPower);
    void resetTotalPumpPower();

    bool setTotalPumpHead(double totalPumpHead);
    void resetTotalPumpHead();

    bool setPhaseChangeCirculatingRate(double phaseChangeCirculatingRate);
    void resetPhaseChangeCirculatingRate();

    bool setPumpDriveType(const std::string& pumpDriveType);
    void resetPumpDriveType();

    bool setPumpMotorHeattoFluid(double pumpMotorHeattoFluid);
    void resetPumpMotorHeattoFluid();

    bool setSumUADistributionPiping(double sumUADistributionPiping);
    void resetSumUADistributionPiping();

    bool setSumUAReceiverSeparatorShell(double sumUAReceiverSeparatorShell);
    void resetSumUAReceiverSeparatorShell();

    bool setEvaporatorRefrigerantInventory(double evaporatorRefrigerantInventory);
    void resetEvaporatorRefrigerantInventory();

    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();
    //@}

   protected:
    using ImplType = detail::RefrigerationSecondarySystem_Impl;

    explicit RefrigerationSecondarySystem(std::shared_ptr<detail::RefrigerationSecondarySystem_Impl> impl);

    friend class detail::RefrigerationSecondarySystem_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

   private:
    REGISTER_LOGGER("openstudio.epmodel.RefrigerationSecondarySystem");
  };

  using OptionalRefrigerationSecondarySystem = boost::optional<RefrigerationSecondarySystem>;
  using RefrigerationSecondarySystemVector = std::vector<RefrigerationSecondarySystem>;

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONSECONDARYSYSTEM_HPP
