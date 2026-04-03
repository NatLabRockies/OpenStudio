/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlantEquipmentOperationScheme.hpp"
#include "PlantEquipmentOperationScheme_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idf/IdfObject.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    PlantEquipmentOperationScheme_Impl::PlantEquipmentOperationScheme_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(idfObject, model, keepHandle) {}

    PlantEquipmentOperationScheme_Impl::PlantEquipmentOperationScheme_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model,
                                                                           bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    PlantEquipmentOperationScheme_Impl::PlantEquipmentOperationScheme_Impl(const PlantEquipmentOperationScheme_Impl& other, Model_Impl* model,
                                                                           bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    boost::optional<openstudio::epmodel::PlantLoop> PlantEquipmentOperationScheme_Impl::plantLoop() const {
      return boost::none;
    }

  }  // namespace detail

  PlantEquipmentOperationScheme::PlantEquipmentOperationScheme(IddObjectType type, const Model& model) : ModelObject(type, model) {
    OS_ASSERT(getImpl<detail::PlantEquipmentOperationScheme_Impl>());
  }

  PlantEquipmentOperationScheme::PlantEquipmentOperationScheme(std::shared_ptr<detail::PlantEquipmentOperationScheme_Impl> impl)
    : ModelObject(std::move(impl)) {}

  boost::optional<PlantLoop> PlantEquipmentOperationScheme::plantLoop() const {
    return getImpl<detail::PlantEquipmentOperationScheme_Impl>()->plantLoop();
  }

}  // namespace epmodel
}  // namespace openstudio
