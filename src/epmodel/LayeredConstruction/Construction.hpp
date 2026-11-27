/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTION_HPP
#define EPMODEL_CONSTRUCTION_HPP

#include "EPModelAPI.hpp"
#include "LayeredConstruction/LayeredConstruction.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  namespace detail {
    class Construction_Impl;
  }

  /** \brief Represents a conventional layered construction.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#construction-000,Construction}. Its extensible layer fields reference material
   * objects.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::Construction</code>. <b>Not yet available:</b> the
   * constructors taking a vector of OpaqueMaterial or FenestrationMaterial, or a
   * ModelPartitionMaterial; construct from the Model and call
   * <code>setLayers()</code> instead.
   *
   * \par Known limitations
   * Layer relationships must be managed through the inherited layer methods;
   * this wrapper does not add alternate relationship helpers.
   */
  class EPMODEL_API Construction : public LayeredConstruction
  {
   public:
    explicit Construction(const Model& model);

    virtual ~Construction() override = default;
    Construction(const Construction& other) = default;
    Construction(Construction&& other) = default;
    Construction& operator=(const Construction&) = default;
    Construction& operator=(Construction&&) = default;

    static IddObjectType iddObjectType();

    /** Searches the model for a layered construction with layers which are the reverse of this one.  Returns that construction
     *  if found, creates one if not. */
    Construction reverseConstruction() const;

   protected:
    using ImplType = detail::Construction_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Construction(std::shared_ptr<detail::Construction_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
