/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRSETTINGSTHREENODEDISPLACEMENTVENTILATION_HPP
#define EPMODEL_ROOMAIRSETTINGSTHREENODEDISPLACEMENTVENTILATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RoomAirSettingsThreeNodeDisplacementVentilation_Impl;
  }

  class EPMODEL_API RoomAirSettingsThreeNodeDisplacementVentilation : public ModelObject
  {
   public:
    explicit RoomAirSettingsThreeNodeDisplacementVentilation(const Model& model);

    virtual ~RoomAirSettingsThreeNodeDisplacementVentilation() override = default;
    RoomAirSettingsThreeNodeDisplacementVentilation(const RoomAirSettingsThreeNodeDisplacementVentilation& other) = default;
    RoomAirSettingsThreeNodeDisplacementVentilation(RoomAirSettingsThreeNodeDisplacementVentilation&& other) = default;
    RoomAirSettingsThreeNodeDisplacementVentilation& operator=(const RoomAirSettingsThreeNodeDisplacementVentilation&) = default;
    RoomAirSettingsThreeNodeDisplacementVentilation& operator=(RoomAirSettingsThreeNodeDisplacementVentilation&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class and accessor naming.
    // - Field Mapping: numberofPlumesperOccupant, thermostatHeight, comfortHeight, and
    //   temperatureDifferenceThresholdforReporting map directly to EnergyPlus
    //   RoomAirSettings:ThreeNodeDisplacementVentilation scalar fields.
    // - Field Mapping: Zone Name and Gain Distribution Schedule Name are object-list relationship fields and
    //   intentionally excluded from scalar accessors in this scaffold pass.
    // - Field Mapping: Name remains available via ModelObject base name APIs.
    // - TODO(parity): Add typed relationship APIs for excluded fields after scalar saturation.
    double numberofPlumesperOccupant() const;
    bool isNumberofPlumesperOccupantDefaulted() const;
    bool setNumberofPlumesperOccupant(double numberofPlumesperOccupant);
    void resetNumberofPlumesperOccupant();

    double thermostatHeight() const;
    bool isThermostatHeightDefaulted() const;
    bool setThermostatHeight(double thermostatHeight);
    void resetThermostatHeight();

    double comfortHeight() const;
    bool isComfortHeightDefaulted() const;
    bool setComfortHeight(double comfortHeight);
    void resetComfortHeight();

    double temperatureDifferenceThresholdforReporting() const;
    bool isTemperatureDifferenceThresholdforReportingDefaulted() const;
    bool setTemperatureDifferenceThresholdforReporting(double temperatureDifferenceThresholdforReporting);
    void resetTemperatureDifferenceThresholdforReporting();

   protected:
    using ImplType = detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RoomAirSettingsThreeNodeDisplacementVentilation(std::shared_ptr<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
