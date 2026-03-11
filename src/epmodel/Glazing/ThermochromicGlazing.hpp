/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOCHROMICGLAZING_HPP
#define EPMODEL_THERMOCHROMICGLAZING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermochromicGlazing_Impl;
  }

  class EPMODEL_API ThermochromicGlazing : public ModelObject
  {
   public:
    explicit ThermochromicGlazing(const Model& model);

    virtual ~ThermochromicGlazing() override = default;
    ThermochromicGlazing(const ThermochromicGlazing& other) = default;
    ThermochromicGlazing(ThermochromicGlazing&& other) = default;
    ThermochromicGlazing& operator=(const ThermochromicGlazing&) = default;
    ThermochromicGlazing& operator=(ThermochromicGlazing&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Mirrors openstudio::model::ThermochromicGlazing naming so the translator still operates on the same type
    //   while this scaffold defers the extensible-group helpers to later iterations.
    // - Field Mapping: Represents OS:WindowMaterial:GlazingGroup:Thermochromic and its extensible groups through
    //   OS_WindowMaterial_GlazingGroup_ThermochromicExtensibleFields, matching ForwardTranslateThermochromicGlazing.
    // - ForwardTranslator evidence: ForwardTranslateThermochromicGlazing.cpp keeps the StandardGlazing references in sync;
    //   reverse translation reads the same extensible data.

   protected:
    using ImplType = detail::ThermochromicGlazing_Impl;

    explicit ThermochromicGlazing(std::shared_ptr<detail::ThermochromicGlazing_Impl> impl);

    friend class detail::ThermochromicGlazing_Impl;
    friend class Model;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_THERMOCHROMICGLAZING_HPP
