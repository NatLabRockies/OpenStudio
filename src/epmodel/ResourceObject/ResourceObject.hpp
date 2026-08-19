/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_RESOURCEOBJECT_HPP
#define EPMODEL_RESOURCEOBJECT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ResourceObject_Impl;
  }

  /** \brief Base class for reusable EnergyPlus resource objects.
   *
   * \par EnergyPlus object
   * This class has no single EnergyPlus object. Concrete subclasses wrap
   * individual resource objects and may opt into the resource lifecycle or
   * transient behavior provided by this base.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model base class is
   * <code>openstudio::model::ResourceObject</code>. No additional public
   * methods are exposed by either base class.
   *
   * \par Known limitations
   * Object-specific fields and relationships are available only on concrete
   * resource subclasses.
   */
  class EPMODEL_API ResourceObject : public ModelObject
  {
   public:
    virtual ~ResourceObject() override = default;
    ResourceObject(const ResourceObject& other) = default;
    ResourceObject(ResourceObject&& other) = default;
    ResourceObject& operator=(const ResourceObject&) = default;
    ResourceObject& operator=(ResourceObject&&) = default;

   protected:
    using ImplType = detail::ResourceObject_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    ResourceObject(IddObjectType type, const Model& model, bool fastName = false, bool isTransient = false);
    explicit ResourceObject(std::shared_ptr<ImplType> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
