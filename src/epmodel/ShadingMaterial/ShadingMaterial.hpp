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

  /** A ShadingMaterial is a FenestrationMaterial that serves as a base class for window shading
   *  devices: Blind, Shade, and Screen. */
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
