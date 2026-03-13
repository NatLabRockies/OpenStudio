/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRTEMPERATUREPATTERNTWOGRADIENT_HPP
#define EPMODEL_ROOMAIRTEMPERATUREPATTERNTWOGRADIENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RoomAirTemperaturePatternTwoGradient_Impl;
  }

  class EPMODEL_API RoomAirTemperaturePatternTwoGradient : public ModelObject
  {
   public:
    explicit RoomAirTemperaturePatternTwoGradient(const Model& model);

    virtual ~RoomAirTemperaturePatternTwoGradient() override = default;
    RoomAirTemperaturePatternTwoGradient(const RoomAirTemperaturePatternTwoGradient& other) = default;
    RoomAirTemperaturePatternTwoGradient(RoomAirTemperaturePatternTwoGradient&& other) = default;
    RoomAirTemperaturePatternTwoGradient& operator=(const RoomAirTemperaturePatternTwoGradient&) = default;
    RoomAirTemperaturePatternTwoGradient& operator=(RoomAirTemperaturePatternTwoGradient&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> gradientInterpolationModeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class and accessor naming.
    // - Field Mapping: controlIntegerforPatternControlScheduleName, thermostatHeight, returnAirHeight, exhaustAirHeight,
    //   temperatureGradientLowerBound, temperatureGradientUpperBound, gradientInterpolationMode, upperTemperatureBound,
    //   lowerTemperatureBound, upperHeatRateBound, and lowerHeatRateBound map directly to EnergyPlus
    //   RoomAir:TemperaturePattern:TwoGradient scalar fields.
    // - Field Mapping: Name is intentionally omitted here and remains provided by ModelObject base name APIs.
    // - TODO(parity): Add relationship APIs only if future schema revisions introduce non-scalar links for this object.

    int controlIntegerforPatternControlScheduleName() const;
    bool setControlIntegerforPatternControlScheduleName(int controlIntegerforPatternControlScheduleName);

    boost::optional<double> thermostatHeight() const;
    bool setThermostatHeight(double thermostatHeight);
    void resetThermostatHeight();

    boost::optional<double> returnAirHeight() const;
    bool setReturnAirHeight(double returnAirHeight);
    void resetReturnAirHeight();

    boost::optional<double> exhaustAirHeight() const;
    bool setExhaustAirHeight(double exhaustAirHeight);
    void resetExhaustAirHeight();

    boost::optional<double> temperatureGradientLowerBound() const;
    bool setTemperatureGradientLowerBound(double temperatureGradientLowerBound);
    void resetTemperatureGradientLowerBound();

    boost::optional<double> temperatureGradientUpperBound() const;
    bool setTemperatureGradientUpperBound(double temperatureGradientUpperBound);
    void resetTemperatureGradientUpperBound();

    boost::optional<std::string> gradientInterpolationMode() const;
    bool setGradientInterpolationMode(const std::string& gradientInterpolationMode);
    void resetGradientInterpolationMode();

    boost::optional<double> upperTemperatureBound() const;
    bool setUpperTemperatureBound(double upperTemperatureBound);
    void resetUpperTemperatureBound();

    boost::optional<double> lowerTemperatureBound() const;
    bool setLowerTemperatureBound(double lowerTemperatureBound);
    void resetLowerTemperatureBound();

    boost::optional<double> upperHeatRateBound() const;
    bool setUpperHeatRateBound(double upperHeatRateBound);
    void resetUpperHeatRateBound();

    boost::optional<double> lowerHeatRateBound() const;
    bool setLowerHeatRateBound(double lowerHeatRateBound);
    void resetLowerHeatRateBound();

   protected:
    using ImplType = detail::RoomAirTemperaturePatternTwoGradient_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RoomAirTemperaturePatternTwoGradient(std::shared_ptr<detail::RoomAirTemperaturePatternTwoGradient_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
