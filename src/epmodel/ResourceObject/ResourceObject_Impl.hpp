/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_RESOURCEOBJECT_IMPL_HPP
#define EPMODEL_RESOURCEOBJECT_IMPL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ResourceObject_Impl : public ModelObject_Impl
    {
     public:
      ResourceObject_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      ResourceObject_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      virtual ~ResourceObject_Impl() override = default;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
