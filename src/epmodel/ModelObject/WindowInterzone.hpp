/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWINTERZONE_HPP
#define EPMODEL_WINDOWINTERZONE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowInterzone_Impl;
  }

  class EPMODEL_API WindowInterzone : public ModelObject
  {
   public:
    explicit WindowInterzone(const Model& model);

    virtual ~WindowInterzone() override = default;
    WindowInterzone(const WindowInterzone& other) = default;
    WindowInterzone(WindowInterzone&& other) = default;
    WindowInterzone& operator=(const WindowInterzone&) = default;
    WindowInterzone& operator=(WindowInterzone&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Window:Interzone has no openstudio::model counterpart, so this class keeps IDD-derived names while scalar-only helpers cover the simple geometry fields.
    // - Field Mapping: Multiplier, Starting X Coordinate, Starting Z Coordinate, Length, and Height map directly to openstudio::Window_InterzoneFields scalars.
    // - Field Mapping: Name, Construction Name, Building Surface Name, and Outside Boundary Condition Object are object-list/relationship fields and are intentionally excluded from the scalar API.
    // - ForwardTranslator Evidence: GeometryTranslator's Window:Interzone pass (src/energyplus/GeometryTranslator.cpp) consumes these scalars to seed FenestrationSurface:Detailed vertices.
    // - TODO(parity): Add typed helpers for the related surface/construction targets once relationship parity work advances.
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
    using ImplType = detail::WindowInterzone_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowInterzone(std::shared_ptr<detail::WindowInterzone_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
