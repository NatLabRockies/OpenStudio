/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALGAP_HPP
#define EPMODEL_WINDOWMATERIALGAP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowMaterialGap_Impl;
  }

  class EPMODEL_API WindowMaterialGap : public ModelObject
  {
   public:
    explicit WindowMaterialGap(const Model& model);

    virtual ~WindowMaterialGap() override = default;
    WindowMaterialGap(const WindowMaterialGap& other) = default;
    WindowMaterialGap(WindowMaterialGap&& other) = default;
    WindowMaterialGap& operator=(const WindowMaterialGap&) = default;
    WindowMaterialGap& operator=(WindowMaterialGap&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: thickness and pressure expose the WindowMaterial:Gap scalars while remaining scalar-only.
    // - Field Mapping: Thickness is seeded from a typical gap depth so the required getter always returns a valid value.
    // - Field Mapping: Pressure defaults to 101,325 Pa per the IDD metadata and exposes isPressureDefaulted/reset helpers.
    // - Field Mapping: Name and gas references remain relationship-like fields managed by ModelObject, while deflection states and support pillars delegate to WindowGapDeflectionState and WindowGapSupportPillar respectively.

    double thickness() const;
    bool setThickness(double thickness);

    double pressure() const;
    bool isPressureDefaulted() const;
    bool setPressure(double pressure);
    void resetPressure();

   protected:
    using ImplType = detail::WindowMaterialGap_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowMaterialGap(std::shared_ptr<detail::WindowMaterialGap_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
