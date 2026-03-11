/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWGAPDEFLECTIONSTATE_HPP
#define EPMODEL_WINDOWGAPDEFLECTIONSTATE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowGapDeflectionState_Impl;
  }

  class EPMODEL_API WindowGapDeflectionState : public ModelObject
  {
   public:
    explicit WindowGapDeflectionState(const Model& model);

    virtual ~WindowGapDeflectionState() override = default;
    WindowGapDeflectionState(const WindowGapDeflectionState& other) = default;
    WindowGapDeflectionState(WindowGapDeflectionState&& other) = default;
    WindowGapDeflectionState& operator=(const WindowGapDeflectionState&) = default;
    WindowGapDeflectionState& operator=(WindowGapDeflectionState&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Scalar getters/setters map to the WindowGapDeflectionState measured deflection entry that WindowMaterial:Gap references by name.
    // - Field Mapping: deflectedThickness, initialTemperature, and initialPressure delegate to WindowGap:DeflectionState fields Deflected Thickness, Initial Temperature, and Initial Pressure.
    // - Field Mapping: Name is managed by ModelObject so the measured deflection state can be referenced by name from WindowMaterial:Gap definitions.
    // - TODO(parity): Add any non-scalar relationship APIs once scalar saturation is complete.
    double deflectedThickness() const;
    bool setDeflectedThickness(double deflectedThickness);

    double initialTemperature() const;
    bool setInitialTemperature(double initialTemperature);

    double initialPressure() const;
    bool setInitialPressure(double initialPressure);

   protected:
    using ImplType = detail::WindowGapDeflectionState_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowGapDeflectionState(std::shared_ptr<detail::WindowGapDeflectionState_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
