/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad_Impl.hpp"

#include "Model.hpp"
#include "Model_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfObject.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    PlantEquipmentOperationCoolingLoad_Impl::PlantEquipmentOperationCoolingLoad_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationRangeBasedScheme_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == PlantEquipmentOperationCoolingLoad::iddObjectType());
    }

    PlantEquipmentOperationCoolingLoad_Impl::PlantEquipmentOperationCoolingLoad_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationRangeBasedScheme_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == PlantEquipmentOperationCoolingLoad::iddObjectType());
    }

    PlantEquipmentOperationCoolingLoad_Impl::PlantEquipmentOperationCoolingLoad_Impl(const PlantEquipmentOperationCoolingLoad_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationRangeBasedScheme_Impl(other, model, keepHandle) {}

  }  // namespace detail

  PlantEquipmentOperationCoolingLoad::PlantEquipmentOperationCoolingLoad(const Model& model)
    : PlantEquipmentOperationRangeBasedScheme(PlantEquipmentOperationCoolingLoad::iddObjectType(), model) {
    setName("PlantEquipmentOperationCoolingLoad");
  }

  PlantEquipmentOperationCoolingLoad::PlantEquipmentOperationCoolingLoad(std::shared_ptr<detail::PlantEquipmentOperationCoolingLoad_Impl> impl)
    : PlantEquipmentOperationRangeBasedScheme(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationCoolingLoad::iddObjectType() {
    return IddObjectType::PlantEquipmentOperation_CoolingLoad;
  }

}  // namespace epmodel
}  // namespace openstudio
