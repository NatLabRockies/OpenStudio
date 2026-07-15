/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVECOOLERINDIRECTCELDEKPAD_HPP
#define EPMODEL_EVAPORATIVECOOLERINDIRECTCELDEKPAD_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EvaporativeCoolerIndirectCelDekPad_Impl;
  }

  class EPMODEL_API EvaporativeCoolerIndirectCelDekPad : public ModelObject
  {
   public:
    explicit EvaporativeCoolerIndirectCelDekPad(const Model& model);

    virtual ~EvaporativeCoolerIndirectCelDekPad() override = default;
    EvaporativeCoolerIndirectCelDekPad(const EvaporativeCoolerIndirectCelDekPad& other) = default;
    EvaporativeCoolerIndirectCelDekPad(EvaporativeCoolerIndirectCelDekPad&& other) = default;
    EvaporativeCoolerIndirectCelDekPad& operator=(const EvaporativeCoolerIndirectCelDekPad&) = default;
    EvaporativeCoolerIndirectCelDekPad& operator=(EvaporativeCoolerIndirectCelDekPad&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: directPadArea/directPadDepth/recirculatingWaterPumpPowerConsumption/secondaryAirFanFlowRate/
    //   secondaryAirFanTotalEfficiency/secondaryAirFanDeltaPressure/indirectHeatExchangerEffectiveness/controlType map directly to
    //   EvaporativeCooler:Indirect:CelDekPad fields.
    // - Field Mapping: Availability Schedule Name, Primary Air Inlet Node Name, Primary Air Outlet Node Name,
    //   Water Supply Storage Tank Name, and Secondary Air Inlet Node Name are relationship-like fields and are excluded from
    //   scalar accessors.
    // - TODO(parity): Add relationship APIs incrementally after scalar saturation.
    boost::optional<double> directPadArea() const;
    bool isDirectPadAreaAutosized() const;
    bool setDirectPadArea(double directPadArea);
    void resetDirectPadArea();
    void autosizeDirectPadArea();

    boost::optional<double> directPadDepth() const;
    bool isDirectPadDepthAutosized() const;
    bool setDirectPadDepth(double directPadDepth);
    void resetDirectPadDepth();
    void autosizeDirectPadDepth();

    double recirculatingWaterPumpPowerConsumption() const;
    bool setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption);

    double secondaryAirFanFlowRate() const;
    bool setSecondaryAirFanFlowRate(double secondaryAirFanFlowRate);

    boost::optional<double> secondaryAirFanTotalEfficiency() const;
    bool setSecondaryAirFanTotalEfficiency(double secondaryAirFanTotalEfficiency);
    void resetSecondaryAirFanTotalEfficiency();

    double secondaryAirFanDeltaPressure() const;
    bool setSecondaryAirFanDeltaPressure(double secondaryAirFanDeltaPressure);

    double indirectHeatExchangerEffectiveness() const;
    bool setIndirectHeatExchangerEffectiveness(double indirectHeatExchangerEffectiveness);

    boost::optional<std::string> controlType() const;
    bool setControlType(const std::string& controlType);
    void resetControlType();

   protected:
    using ImplType = detail::EvaporativeCoolerIndirectCelDekPad_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EvaporativeCoolerIndirectCelDekPad(std::shared_ptr<detail::EvaporativeCoolerIndirectCelDekPad_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
