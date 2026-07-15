/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/ResourceObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    ResourceObject_Impl::ResourceObject_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(idfObject, model, keepHandle) {}

    ResourceObject_Impl::ResourceObject_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
