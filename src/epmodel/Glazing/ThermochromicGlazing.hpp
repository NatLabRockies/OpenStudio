/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOCHROMICGLAZING_HPP
#define EPMODEL_THERMOCHROMICGLAZING_HPP

#include "EPModelAPI.hpp"
#include "Glazing/Glazing.hpp"

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermochromicGlazing_Impl;
  }

  /** \brief Groups temperature-dependent standard glazing layers.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#windowmaterialglazinggroupthermochromic,WindowMaterial:GlazingGroup:Thermochromic}. Its extensible rows
   * refer to standard glazing objects and switching temperatures.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ThermochromicGlazing</code>. EPModel currently
   * exposes no public group-management methods. Model's
   * <code>thermochromicGroups()</code>, add/remove, indexing, and standard-
   * glazing relationship methods are not available.
   *
   * \par Known limitations
   * Temperature-dependent glazing rows cannot yet be created or edited through
   * this wrapper.
   */
  class EPMODEL_API ThermochromicGlazing : public Glazing
  {
   public:
    explicit ThermochromicGlazing(const Model& model);

    virtual ~ThermochromicGlazing() override = default;
    ThermochromicGlazing(const ThermochromicGlazing& other) = default;
    ThermochromicGlazing(ThermochromicGlazing&& other) = default;
    ThermochromicGlazing& operator=(const ThermochromicGlazing&) = default;
    ThermochromicGlazing& operator=(ThermochromicGlazing&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::ThermochromicGlazing_Impl;

    explicit ThermochromicGlazing(std::shared_ptr<detail::ThermochromicGlazing_Impl> impl);

    friend class detail::ThermochromicGlazing_Impl;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_THERMOCHROMICGLAZING_HPP
