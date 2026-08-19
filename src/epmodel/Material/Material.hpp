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

  /** \brief Base class for materials that can be used in layered constructions.
   *
   * \par EnergyPlus object
   * This class has no single EnergyPlus object. Concrete material subclasses
   * encapsulate the applicable material object and implement the shared
   * thickness and optical queries where those fields exist.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::Material</code>. EPModel does not provide Model's
   * <code>standardsInformation()</code> helper.
   *
   * \par Known limitations
   * A base Material may not have meaningful thickness or optical values;
   * concrete subclasses define which shared queries are supported.
   */
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
