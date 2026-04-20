/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRTEMPERATUREPATTERNNONDIMENSIONALHEIGHT_HPP
#define EPMODEL_ROOMAIRTEMPERATUREPATTERNNONDIMENSIONALHEIGHT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RoomAirTemperaturePatternNondimensionalHeight_Impl;
  }

  class EPMODEL_API RoomAirTemperaturePatternNondimensionalHeight : public ModelObject
  {
   public:
    explicit RoomAirTemperaturePatternNondimensionalHeight(const Model& model);

    virtual ~RoomAirTemperaturePatternNondimensionalHeight() override = default;
    RoomAirTemperaturePatternNondimensionalHeight(const RoomAirTemperaturePatternNondimensionalHeight& other) = default;
    RoomAirTemperaturePatternNondimensionalHeight(RoomAirTemperaturePatternNondimensionalHeight&& other) = default;
    RoomAirTemperaturePatternNondimensionalHeight& operator=(const RoomAirTemperaturePatternNondimensionalHeight&) = default;
    RoomAirTemperaturePatternNondimensionalHeight& operator=(RoomAirTemperaturePatternNondimensionalHeight&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class and accessor naming.
    // - Field Mapping: controlIntegerforPatternControlScheduleName, thermostatOffset, returnAirOffset, and exhaustAirOffset
    //   map directly to EnergyPlus RoomAir:TemperaturePattern:NondimensionalHeight non-extensible scalar fields.
    // - Field Mapping: Name is intentionally omitted here and remains provided by ModelObject base name APIs.
    // - TODO(parity): Add APIs for extensible (Pair Zeta/Delta Adjacent Air Temperature) groups when non-scalar support is added.
    int controlIntegerforPatternControlScheduleName() const;
    bool setControlIntegerforPatternControlScheduleName(int controlIntegerforPatternControlScheduleName);

    boost::optional<double> thermostatOffset() const;
    bool setThermostatOffset(double thermostatOffset);
    void resetThermostatOffset();

    boost::optional<double> returnAirOffset() const;
    bool setReturnAirOffset(double returnAirOffset);
    void resetReturnAirOffset();

    boost::optional<double> exhaustAirOffset() const;
    bool setExhaustAirOffset(double exhaustAirOffset);
    void resetExhaustAirOffset();

   protected:
    using ImplType = detail::RoomAirTemperaturePatternNondimensionalHeight_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RoomAirTemperaturePatternNondimensionalHeight(std::shared_ptr<detail::RoomAirTemperaturePatternNondimensionalHeight_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
