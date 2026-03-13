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

    double sumUAReceiverSeparatorShell() const;
    bool isSumUAReceiverSeparatorShellDefaulted() const;
    bool setSumUAReceiverSeparatorShell(double sumUAReceiverSeparatorShell);
    void resetSumUAReceiverSeparatorShell();

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
