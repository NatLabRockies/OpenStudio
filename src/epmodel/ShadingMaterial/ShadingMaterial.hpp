/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGMATERIAL_HPP
#define EPMODEL_SHADINGMATERIAL_HPP

#include "EPModelAPI.hpp"
#include "FenestrationMaterial/FenestrationMaterial.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  namespace detail {
    class ShadingMaterial_Impl;
  }

  /** \brief Base class for window shading materials.
   *
   * \par EnergyPlus object
   * This class has no single EnergyPlus object. Concrete subclasses encapsulate
   * \epobject{group-surface-construction-elements.html#windowmaterialblind,WindowMaterial:Blind}, \epobject{group-surface-construction-elements.html#windowmaterialshade,WindowMaterial:Shade}, or
   * \epobject{group-surface-construction-elements.html#windowmaterialscreen,WindowMaterial:Screen}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ShadingMaterial</code>. No additional public API
   * differences are known.
   *
   * \par Known limitations
   * This abstract class cannot be persisted without a concrete shading type.
   */
  class EPMODEL_API ShadingMaterial : public FenestrationMaterial
  {
   public:
    virtual ~ShadingMaterial() override = default;
    ShadingMaterial(const ShadingMaterial& other) = default;
    ShadingMaterial(ShadingMaterial&& other) = default;
    ShadingMaterial& operator=(const ShadingMaterial&) = default;
    ShadingMaterial& operator=(ShadingMaterial&&) = default;

   protected:
    using ImplType = detail::ShadingMaterial_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    ShadingMaterial(IddObjectType type, const Model& model);

    explicit ShadingMaterial(std::shared_ptr<detail::ShadingMaterial_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.ShadingMaterial");
  };

  using OptionalShadingMaterial = boost::optional<ShadingMaterial>;
  using ShadingMaterialVector = std::vector<ShadingMaterial>;

}  // namespace epmodel
}  // namespace openstudio

#endif
