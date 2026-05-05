/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad_Impl.hpp"

#include "Model.hpp"
#include "Model_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfObject.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    PlantEquipmentOperationHeatingLoad_Impl::PlantEquipmentOperationHeatingLoad_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationRangeBasedScheme_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == PlantEquipmentOperationHeatingLoad::iddObjectType());
    }

    PlantEquipmentOperationHeatingLoad_Impl::PlantEquipmentOperationHeatingLoad_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationRangeBasedScheme_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == PlantEquipmentOperationHeatingLoad::iddObjectType());
    }

    PlantEquipmentOperationHeatingLoad_Impl::PlantEquipmentOperationHeatingLoad_Impl(const PlantEquipmentOperationHeatingLoad_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationRangeBasedScheme_Impl(other, model, keepHandle) {}

  }  // namespace detail

  PlantEquipmentOperationHeatingLoad::PlantEquipmentOperationHeatingLoad(const Model& model)
    : PlantEquipmentOperationRangeBasedScheme(PlantEquipmentOperationHeatingLoad::iddObjectType(), model) {
    setName("PlantEquipmentOperationHeatingLoad");
  }

  PlantEquipmentOperationHeatingLoad::PlantEquipmentOperationHeatingLoad(std::shared_ptr<detail::PlantEquipmentOperationHeatingLoad_Impl> impl)
    : PlantEquipmentOperationRangeBasedScheme(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationHeatingLoad::iddObjectType() {
    return IddObjectType::PlantEquipmentOperation_HeatingLoad;
  }

}  // namespace epmodel
}  // namespace openstudio
