/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOW_HPP
#define EPMODEL_WINDOW_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Window_Impl;
  }

  class EPMODEL_API Window : public ModelObject
  {
   public:
    explicit Window(const Model& model);

    virtual ~Window() override = default;
    Window(const Window& other) = default;
    Window(Window&& other) = default;
    Window& operator=(const Window&) = default;
    Window& operator=(Window&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so this class keeps IDD-derived naming/scalar semantics while leaving relationship helpers for future work.
    // - Field Mapping: Multiplier, Starting X Coordinate, Starting Z Coordinate, Length, and Height map directly to openstudio::WindowFields scalars.
    // - Field Mapping: Name, Construction Name, Building Surface Name, and Frame and Divider Name are relationship/object-list fields handled downstream and excluded from the scalar API.
    // - TODO(parity): Add helpers for the associated surface and construction targets once the Window translators/factory routing are ported to epmodel.
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
    using ImplType = detail::Window_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Window(std::shared_ptr<detail::Window_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
