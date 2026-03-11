/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACOUTDOORAIRUNIT_HPP
#define EPMODEL_ZONEHVACOUTDOORAIRUNIT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACOutdoorAirUnit_Impl;
  }

  class EPMODEL_API ZoneHVACOutdoorAirUnit : public ModelObject
  {
   public:
    explicit ZoneHVACOutdoorAirUnit(const Model& model);

    virtual ~ZoneHVACOutdoorAirUnit() override = default;
    ZoneHVACOutdoorAirUnit(const ZoneHVACOutdoorAirUnit& other) = default;
    ZoneHVACOutdoorAirUnit(ZoneHVACOutdoorAirUnit&& other) = default;
    ZoneHVACOutdoorAirUnit& operator=(const ZoneHVACOutdoorAirUnit&) = default;
    ZoneHVACOutdoorAirUnit& operator=(ZoneHVACOutdoorAirUnit&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> supplyFanPlacementValues();
    static std::vector<std::string> unitControlTypeValues();

    // Schema Alignment Notes:
    // - API: Scalar accessors map to the IDD ZoneHVAC:OutdoorAirUnit real/choice fields while keeping IDD-derived naming.
    // - Field Mapping: Outdoor Air Flow Rate and Exhaust Air Flow Rate are simple real scalars; relationship fields remain
    //   handled elsewhere (schedules, zones, nodes, fans, equipment lists, availability managers).
    // - Field Mapping: Supply Fan Placement and Unit Control Type are non-boolean choice fields whose values mirror
    //   the equivalent EnergyPlus keys (BlowThrough/DrawThrough and NeutralControl/TemperatureControl).
    // - TODO(parity): Add relationship APIs (schedules/nodes/equipment links) once scalar coverage completes.
    boost::optional<double> outdoorAirFlowRate() const;
    bool isOutdoorAirFlowRateAutosized() const;
    bool setOutdoorAirFlowRate(double outdoorAirFlowRate);
    void autosizeOutdoorAirFlowRate();

    boost::optional<double> exhaustAirFlowRate() const;
    bool isExhaustAirFlowRateAutosized() const;
    bool setExhaustAirFlowRate(double exhaustAirFlowRate);
    void autosizeExhaustAirFlowRate();
    void resetExhaustAirFlowRate();

    std::string supplyFanPlacement() const;
    bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
    bool isSupplyFanPlacementDefaulted() const;
    void resetSupplyFanPlacement();

    std::string unitControlType() const;
    bool setUnitControlType(const std::string& unitControlType);
    bool isUnitControlTypeDefaulted() const;
    void resetUnitControlType();

   protected:
    using ImplType = detail::ZoneHVACOutdoorAirUnit_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACOutdoorAirUnit(std::shared_ptr<detail::ZoneHVACOutdoorAirUnit_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
