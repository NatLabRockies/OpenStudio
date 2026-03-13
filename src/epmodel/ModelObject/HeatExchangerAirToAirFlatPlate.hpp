/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERAIRTOAIRFLATPLATE_HPP
#define EPMODEL_HEATEXCHANGERAIRTOAIRFLATPLATE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HeatExchangerAirToAirFlatPlate_Impl;
  }

  class EPMODEL_API HeatExchangerAirToAirFlatPlate : public ModelObject
  {
   public:
    explicit HeatExchangerAirToAirFlatPlate(const Model& model);

    virtual ~HeatExchangerAirToAirFlatPlate() override = default;
    HeatExchangerAirToAirFlatPlate(const HeatExchangerAirToAirFlatPlate& other) = default;
    HeatExchangerAirToAirFlatPlate(HeatExchangerAirToAirFlatPlate&& other) = default;
    HeatExchangerAirToAirFlatPlate& operator=(const HeatExchangerAirToAirFlatPlate&) = default;
    HeatExchangerAirToAirFlatPlate& operator=(HeatExchangerAirToAirFlatPlate&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> flowArrangementTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HeatExchanger:AirToAir:FlatPlate choice/real fields.
    // - Field Mapping: Availability schedule and node-name fields are excluded as relationship fields.
    // - TODO(parity): Relationship APIs remain out of scope during scalar-only scaffold saturation.
    boost::optional<std::string> flowArrangementType() const;
    bool setFlowArrangementType(const std::string& flowArrangementType);
    void resetFlowArrangementType();

    bool economizerLockout() const;
    bool setEconomizerLockout(bool economizerLockout);
    void resetEconomizerLockout();
    bool isEconomizerLockoutDefaulted() const;

    boost::optional<double> ratioofSupplytoSecondaryhAValues() const;
    bool setRatioofSupplytoSecondaryhAValues(double ratioofSupplytoSecondaryhAValues);
    void resetRatioofSupplytoSecondaryhAValues();

    boost::optional<double> nominalSupplyAirFlowRate() const;
    bool setNominalSupplyAirFlowRate(double nominalSupplyAirFlowRate);
    void resetNominalSupplyAirFlowRate();
    void autosizeNominalSupplyAirFlowRate();
    bool isNominalSupplyAirFlowRateAutosized() const;

    double nominalSupplyAirInletTemperature() const;
    bool setNominalSupplyAirInletTemperature(double nominalSupplyAirInletTemperature);

    double nominalSupplyAirOutletTemperature() const;
    bool setNominalSupplyAirOutletTemperature(double nominalSupplyAirOutletTemperature);

    boost::optional<double> nominalSecondaryAirFlowRate() const;
    bool setNominalSecondaryAirFlowRate(double nominalSecondaryAirFlowRate);
    void autosizeNominalSecondaryAirFlowRate();
    bool isNominalSecondaryAirFlowRateAutosized() const;

    double nominalSecondaryAirInletTemperature() const;
    bool setNominalSecondaryAirInletTemperature(double nominalSecondaryAirInletTemperature);

    boost::optional<double> nominalElectricPower() const;
    bool setNominalElectricPower(double nominalElectricPower);
    void resetNominalElectricPower();

   protected:
    using ImplType = detail::HeatExchangerAirToAirFlatPlate_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatExchangerAirToAirFlatPlate(std::shared_ptr<detail::HeatExchangerAirToAirFlatPlate_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
