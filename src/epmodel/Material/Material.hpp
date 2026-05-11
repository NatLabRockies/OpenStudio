/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIAL_HPP
#define EPMODEL_MATERIAL_HPP

#include "EPModelAPI.hpp"
#include "ResourceObject/ResourceObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  namespace detail {
    class Material_Impl;
  }

  /** A Material is a ResourceObject that serves as a base class for all objects that can be used
   *  in LayeredConstructions. */
  class EPMODEL_API Material : public ResourceObject
  {
   public:
    virtual ~Material() override = default;
    Material(const Material& other) = default;
    Material(Material&& other) = default;
    Material& operator=(const Material&) = default;
    Material& operator=(Material&&) = default;

    /** Returns the thickness of the material in meters. For some materials, 0.0 is always returned. */
    double thickness() const;

    /** Sets the thickness of the material in meters. For some materials, false is always returned. */
    bool setThickness(double value);

    /** Returns the visible transmittance of the material, if available. */
    boost::optional<double> getVisibleTransmittance() const;

    /** Returns the interior visible absorptance of the material, if available. */
    boost::optional<double> interiorVisibleAbsorptance() const;

    /** Returns the exterior visible absorptance of the material, if available. */
    boost::optional<double> exteriorVisibleAbsorptance() const;

   protected:
    using ImplType = detail::Material_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    Material(IddObjectType type, const Model& model);

    explicit Material(std::shared_ptr<detail::Material_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.Material");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
