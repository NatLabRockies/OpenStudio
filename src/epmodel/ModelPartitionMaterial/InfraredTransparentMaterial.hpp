/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_INFRAREDTRANSPARENTMATERIAL_HPP
#define EPMODEL_INFRAREDTRANSPARENTMATERIAL_HPP

#include "EPModelAPI.hpp"
#include "Material/Material.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class InfraredTransparentMaterial_Impl;
  }

  /** \brief Represents a material transparent to infrared radiation.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#materialinfraredtransparent,Material:InfraredTransparent}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::InfraredTransparentMaterial</code>. The public
   * object surface is limited to inherited name/material behavior in both
   * APIs.
   *
   * \par Known limitations
   * The EnergyPlus object has no additional scalar fields exposed by this
   * wrapper.
   */
  class EPMODEL_API InfraredTransparentMaterial : public Material
  {
   public:
    explicit InfraredTransparentMaterial(const Model& model);

    virtual ~InfraredTransparentMaterial() override = default;
    InfraredTransparentMaterial(const InfraredTransparentMaterial& other) = default;
    InfraredTransparentMaterial(InfraredTransparentMaterial&& other) = default;
    InfraredTransparentMaterial& operator=(const InfraredTransparentMaterial&) = default;
    InfraredTransparentMaterial& operator=(InfraredTransparentMaterial&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::InfraredTransparentMaterial_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit InfraredTransparentMaterial(std::shared_ptr<detail::InfraredTransparentMaterial_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
