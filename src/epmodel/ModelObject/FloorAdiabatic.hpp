/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLOORADIABATIC_HPP
#define EPMODEL_FLOORADIABATIC_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FloorAdiabatic_Impl;
  }

  class EPMODEL_API FloorAdiabatic : public ModelObject
  {
   public:
    explicit FloorAdiabatic(const Model& model);

    virtual ~FloorAdiabatic() override = default;
    FloorAdiabatic(const FloorAdiabatic& other) = default;
    FloorAdiabatic(FloorAdiabatic&& other) = default;
    FloorAdiabatic& operator=(const FloorAdiabatic&) = default;
    FloorAdiabatic& operator=(FloorAdiabatic&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: azimuthAngle, tiltAngle, startingXCoordinate, startingYCoordinate, startingZCoordinate,
    //   length, and width map directly to EnergyPlus Floor:Adiabatic scalar fields with matching names.
    // - Field Mapping: Construction Name, Zone Name, and Space Name are object-list relationship fields and are
    //   intentionally excluded from scalar accessors.
    // - Field Mapping: Name remains available through base ModelObject naming API.
    // - TODO(parity): Add typed relationship APIs after scalar scaffold saturation.

    // AzimuthAngle
    boost::optional<double> azimuthAngle() const;
    bool setAzimuthAngle(double azimuthAngle);
    void resetAzimuthAngle();

    // TiltAngle
    double tiltAngle() const;
    bool isTiltAngleDefaulted() const;
    bool setTiltAngle(double tiltAngle);
    void resetTiltAngle();

    // StartingXCoordinate
    boost::optional<double> startingXCoordinate() const;
    bool setStartingXCoordinate(double startingXCoordinate);
    void resetStartingXCoordinate();

    // StartingYCoordinate
    boost::optional<double> startingYCoordinate() const;
    bool setStartingYCoordinate(double startingYCoordinate);
    void resetStartingYCoordinate();

    // StartingZCoordinate
    boost::optional<double> startingZCoordinate() const;
    bool setStartingZCoordinate(double startingZCoordinate);
    void resetStartingZCoordinate();

    // Length
    boost::optional<double> length() const;
    bool setLength(double length);
    void resetLength();

    // Width
    boost::optional<double> width() const;
    bool setWidth(double width);
    void resetWidth();

   protected:
    using ImplType = detail::FloorAdiabatic_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FloorAdiabatic(std::shared_ptr<detail::FloorAdiabatic_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
