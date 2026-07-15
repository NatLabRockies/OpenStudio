/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DOOR_HPP
#define EPMODEL_DOOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Door_Impl;
  }

  class EPMODEL_API Door : public ModelObject
  {
   public:
    explicit Door(const Model& model);

    virtual ~Door() override = default;
    Door(const Door& other) = default;
    Door(Door&& other) = default;
    Door& operator=(const Door&) = default;
    Door& operator=(Door&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus Door fields.
    // - Field Mapping: Construction Name and Building Surface Name are
    //   relationship-like object-list links and are excluded from scalar accessors.
    // - ForwardTranslator Evidence: GeometryTranslator maps Door scalar geometry
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
    using ImplType = detail::Door_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Door(std::shared_ptr<detail::Door_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
