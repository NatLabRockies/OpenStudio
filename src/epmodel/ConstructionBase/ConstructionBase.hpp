/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONBASE_HPP
#define EPMODEL_CONSTRUCTIONBASE_HPP

#include "EPModelAPI.hpp"
#include "ResourceObject/ResourceObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  namespace detail {
    class ConstructionBase_Impl;
  }

  /** \brief Base class for constructions assigned to planar surfaces.
   *
   * \par EnergyPlus object
   * This class has no single EnergyPlus object. Concrete subclasses encapsulate
   * layered, air-boundary, or ground-construction objects.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ConstructionBase</code>. EPModel provides the
   * construction classification queries, but not Model's inherited material
   * convenience methods or standards/rendering helpers such as
   * <code>uFactor()</code>, <code>heatCapacity()</code>, and
   * <code>standardsInformation()</code>.
   *
   * \par Known limitations
   * A concrete construction type is required to create a persisted EnergyPlus
   * object.
   */
  class EPMODEL_API ConstructionBase : public ResourceObject
  {
   public:
    virtual ~ConstructionBase() override = default;
    ConstructionBase(const ConstructionBase& other) = default;
    ConstructionBase(ConstructionBase&& other) = default;
    ConstructionBase& operator=(const ConstructionBase&) = default;
    ConstructionBase& operator=(ConstructionBase&&) = default;

    bool isOpaque() const;
    bool isFenestration() const;
    bool isSolarDiffusing() const;
    bool isModelPartition() const;

    /** Returns true if the construction has RoofVegetation as the outer layer. */
    bool isGreenRoof() const;

   protected:
    ConstructionBase(IddObjectType type, const Model& model);

    using ImplType = detail::ConstructionBase_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ConstructionBase(std::shared_ptr<detail::ConstructionBase_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.ConstructionBase");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
