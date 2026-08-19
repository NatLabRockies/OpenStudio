/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PARENTOBJECT_HPP
#define EPMODEL_PARENTOBJECT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/core/Logger.hpp"

#include <boost/optional.hpp>

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {
    class ParentObject_Impl;
  }

/** \brief Base class for parent-backed and compound EnergyPlus objects.
 *
 * \par EnergyPlus object
 * No single EnergyPlus object; concrete subclasses wrap individual parent objects.
 *
 * \par Important behavior
 * Concrete subclasses use this base for direct EnergyPlus-backed storage and parent-owned relationships.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ParentObject</code>.
 *
 * \par Known limitations
 * Object-specific fields and relationships are available only on concrete subclasses.
 */
  class EPMODEL_API ParentObject : public ModelObject
  {
   public:
    virtual ~ParentObject() override = default;
    ParentObject(const ParentObject& other) = default;
    ParentObject(ParentObject&& other) = default;
    ParentObject& operator=(const ParentObject&) = default;
    ParentObject& operator=(ParentObject&&) = default;

    std::vector<ModelObject> children() const;

   protected:
    ParentObject(IddObjectType type, const Model& model, bool fastName = false, bool isTransient = false);

    using ImplType = detail::ParentObject_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ParentObject(std::shared_ptr<ImplType> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.ParentObject");
  };

  using OptionalParentObject = boost::optional<ParentObject>;
  using ParentObjectVector = std::vector<ParentObject>;

}  // namespace epmodel
}  // namespace openstudio

#endif
