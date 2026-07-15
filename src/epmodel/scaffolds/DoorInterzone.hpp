/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DOORINTERZONE_HPP
#define EPMODEL_DOORINTERZONE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DoorInterzone_Impl;
  }

  class EPMODEL_API DoorInterzone : public ModelObject
  {
   public:
    explicit DoorInterzone(const Model& model);

    virtual ~DoorInterzone() override = default;
    DoorInterzone(const DoorInterzone& other) = default;
    DoorInterzone(DoorInterzone&& other) = default;
    DoorInterzone& operator=(const DoorInterzone&) = default;
    DoorInterzone& operator=(DoorInterzone&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus Door:Interzone fields.
    // - Field Mapping: Construction Name, Building Surface Name, and Outside Boundary
    //   Condition Object are relationship-like object-list links and are excluded from
    //   scalar accessors.
    // - ForwardTranslator Evidence: GeometryTranslator maps Door:Interzone scalar geometry
    //   fields (Starting X/Z, Length, Height, Multiplier) directly to
    //   FenestrationSurface:Detailed geometry/data.
    // - TODO(parity): Add typed relationship APIs when non-scalar parity work is prioritized.
    double multiplier() const;
    bool isMultiplierDefaulted() const;
    bool setMultiplier(double multiplier);
    void resetMultiplier();

    boost::optional<double> startingXCoordinate() const;
    bool setStartingXCoordinate(double startingXCoordinate);
    void resetStartingXCoordinate();

    boost::optional<double> startingZCoordinate() const;
    bool setStartingZCoordinate(double startingZCoordinate);
    void resetStartingZCoordinate();

    boost::optional<double> length() const;
    bool setLength(double length);
    void resetLength();

    boost::optional<double> height() const;
    bool setHeight(double height);
    void resetHeight();

   protected:
    using ImplType = detail::DoorInterzone_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DoorInterzone(std::shared_ptr<detail::DoorInterzone_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
