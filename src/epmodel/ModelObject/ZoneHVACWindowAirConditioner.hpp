/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACWINDOWAIRCONDITIONER_HPP
#define EPMODEL_ZONEHVACWINDOWAIRCONDITIONER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>
#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACWindowAirConditioner_Impl;
  }

  class EPMODEL_API ZoneHVACWindowAirConditioner : public ModelObject
  {
   public:
    explicit ZoneHVACWindowAirConditioner(const Model& model);

    virtual ~ZoneHVACWindowAirConditioner() override = default;
    ZoneHVACWindowAirConditioner(const ZoneHVACWindowAirConditioner& other) = default;
    ZoneHVACWindowAirConditioner(ZoneHVACWindowAirConditioner&& other) = default;
    ZoneHVACWindowAirConditioner& operator=(const ZoneHVACWindowAirConditioner&) = default;
    ZoneHVACWindowAirConditioner& operator=(ZoneHVACWindowAirConditioner&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> outdoorAirMixerObjectTypeValues();
    static std::vector<std::string> supplyAirFanObjectTypeValues();
    static std::vector<std::string> coolingCoilObjectTypeValues();
    static std::vector<std::string> fanPlacementValues();

    // Schema Alignment Notes:
    // - API: Scalar/choice accessors mirror IDD-derived ZoneHVAC:WindowAirConditioner naming/semantics.
    // - Field Mapping: Maximum Supply/Air Flow Rate and Maximum Outdoor Air Flow Rate map directly to the same EnergyPlus fields while mixer/fan/coil names remain relationship-only.
    // - Field Mapping: Choice fields delegate to the corresponding IDD choice tokens; object-list relationships (schedules, nodes, component names, availability lists, sizing objects) were intentionally excluded here.
    // - TODO(parity): Add relationship helpers once scalar saturation is complete without modifying these scalar signatures.
    boost::optional<double> maximumSupplyAirFlowRate() const;
    bool isMaximumSupplyAirFlowRateAutosized() const;
    bool setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate);
    void autosizeMaximumSupplyAirFlowRate();
    boost::optional<double> autosizedMaximumSupplyAirFlowRate() const;

    boost::optional<double> maximumOutdoorAirFlowRate() const;
    bool isMaximumOutdoorAirFlowRateAutosized() const;
    bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
    void autosizeMaximumOutdoorAirFlowRate();
    boost::optional<double> autosizedMaximumOutdoorAirFlowRate() const;

    std::string outdoorAirMixerObjectType() const;
    bool setOutdoorAirMixerObjectType(const std::string& outdoorAirMixerObjectType);

    std::string supplyAirFanObjectType() const;
    bool setSupplyAirFanObjectType(const std::string& supplyAirFanObjectType);

    std::string coolingCoilObjectType() const;
    bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

    std::string fanPlacement() const;
    bool setFanPlacement(const std::string& fanPlacement);

   protected:
    using ImplType = detail::ZoneHVACWindowAirConditioner_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACWindowAirConditioner(std::shared_ptr<detail::ZoneHVACWindowAirConditioner_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
