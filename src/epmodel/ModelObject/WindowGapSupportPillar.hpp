/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWGAPSUPPORTPILLAR_HPP
#define EPMODEL_WINDOWGAPSUPPORTPILLAR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowGapSupportPillar_Impl;
  }

  class EPMODEL_API WindowGapSupportPillar : public ModelObject
  {
   public:
    explicit WindowGapSupportPillar(const Model& model);

    virtual ~WindowGapSupportPillar() override = default;
    WindowGapSupportPillar(const WindowGapSupportPillar& other) = default;
    WindowGapSupportPillar(WindowGapSupportPillar&& other) = default;
    WindowGapSupportPillar& operator=(const WindowGapSupportPillar&) = default;
    WindowGapSupportPillar& operator=(WindowGapSupportPillar&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Spacing and Radius mirror the simple geometry scalars WindowMaterial:Gap uses for support pillars.
    // - Field Mapping: Spacing maps to WindowGap:SupportPillar Spacing (default 0.04 m) and exposes isSpacingDefaulted/reset helpers.
    // - Field Mapping: Radius maps to WindowGap:SupportPillar Radius (default 0.0004 m) with accompanying default/reset helpers.
    // - Field Mapping: Name is inherited from ModelObject so a WindowMaterial:Gap can reference the pillar entry without additional scalar APIs.
    double spacing() const;
    bool isSpacingDefaulted() const;
    bool setSpacing(double spacing);
    void resetSpacing();

    double radius() const;
    bool isRadiusDefaulted() const;
    bool setRadius(double radius);
    void resetRadius();

   protected:
    using ImplType = detail::WindowGapSupportPillar_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowGapSupportPillar(std::shared_ptr<detail::WindowGapSupportPillar_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
