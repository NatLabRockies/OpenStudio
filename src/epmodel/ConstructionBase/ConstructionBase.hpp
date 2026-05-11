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

  /** ConstructionBase is an abstract base class for all construction types that can be assigned
   *  to a PlanarSurface. */
  class EPMODEL_API ConstructionBase : public ResourceObject
  {
   public:
    virtual ~ConstructionBase() override = default;
    ConstructionBase(const ConstructionBase& other) = default;
    ConstructionBase(ConstructionBase&& other) = default;
    ConstructionBase& operator=(const ConstructionBase&) = default;
    ConstructionBase& operator=(ConstructionBase&&) = default;

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
