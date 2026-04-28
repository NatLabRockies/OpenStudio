/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GLAZEDDOOR_HPP
#define EPMODEL_GLAZEDDOOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GlazedDoor_Impl;
  }

  class EPMODEL_API GlazedDoor : public ModelObject
  {
   public:
    explicit GlazedDoor(const Model& model);

    virtual ~GlazedDoor() override = default;
    GlazedDoor(const GlazedDoor& other) = default;
    GlazedDoor(GlazedDoor&& other) = default;
    GlazedDoor& operator=(const GlazedDoor&) = default;
    GlazedDoor& operator=(GlazedDoor&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus GlazedDoor fields.
    // - Field Mapping: Construction Name, Building Surface Name, and Frame and Divider
    //   Name are relationship-like object-list links and are excluded from scalar accessors.
    // - ForwardTranslator Evidence: GeometryTranslator maps GlazedDoor scalar geometry
    //   fields (Starting X/Z, Length, Height, Multiplier) directly to
    //   FenestrationSurface:Detailed geometry/data.
    // - TODO(parity): Add typed relationship APIs when non-scalar parity work is prioritized.
    // Multiplier
    double multiplier() const;
    bool isMultiplierDefaulted() const;
    bool setMultiplier(double multiplier);
    void resetMultiplier();

    // Starting X coordinate
    boost::optional<double> startingXCoordinate() const;
    bool setStartingXCoordinate(double startingXCoordinate);
    void resetStartingXCoordinate();

    // Starting Z coordinate
    boost::optional<double> startingZCoordinate() const;
    bool setStartingZCoordinate(double startingZCoordinate);
    void resetStartingZCoordinate();

    // Length
    boost::optional<double> length() const;
    bool setLength(double length);
    void resetLength();

    // Height
    boost::optional<double> height() const;
    bool setHeight(double height);
    void resetHeight();

   protected:
    using ImplType = detail::GlazedDoor_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GlazedDoor(std::shared_ptr<detail::GlazedDoor_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
