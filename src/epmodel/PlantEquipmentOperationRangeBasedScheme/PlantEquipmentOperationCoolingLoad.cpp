/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationCoolingLoad.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationCoolingLoad_Impl.hpp"

#include "Model.hpp"
#include "Model_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfObject.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    namespace {
      enum LoadExtensibleFields
      {
        LOADRANGEFIELDS_LOWERLIMIT,
        LOADRANGEFIELDS_UPPERLIMIT,
        LOADRANGEFIELDS_RANGEEQUIPMENTLISTNAME
      };
    }

    PlantEquipmentOperationCoolingLoad_Impl::PlantEquipmentOperationCoolingLoad_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == PlantEquipmentOperationCoolingLoad::iddObjectType());
    }

    PlantEquipmentOperationCoolingLoad_Impl::PlantEquipmentOperationCoolingLoad_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == PlantEquipmentOperationCoolingLoad::iddObjectType());
    }

    PlantEquipmentOperationCoolingLoad_Impl::PlantEquipmentOperationCoolingLoad_Impl(const PlantEquipmentOperationCoolingLoad_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    double PlantEquipmentOperationCoolingLoad_Impl::maximumUpperLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 1E9;
      }
      const auto& value = groups.back().getDouble(LOADRANGEFIELDS_UPPERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

    double PlantEquipmentOperationCoolingLoad_Impl::minimumLowerLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 0.0;
      }
      const auto& value = groups.front().getDouble(LOADRANGEFIELDS_LOWERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

  }  // namespace detail

  PlantEquipmentOperationCoolingLoad::PlantEquipmentOperationCoolingLoad(const Model& model)
    : ModelObject(PlantEquipmentOperationCoolingLoad::iddObjectType(), model) {
    setName("PlantEquipmentOperationCoolingLoad");
  }

  PlantEquipmentOperationCoolingLoad::PlantEquipmentOperationCoolingLoad(std::shared_ptr<detail::PlantEquipmentOperationCoolingLoad_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationCoolingLoad::iddObjectType() {
    return IddObjectType::OS_PlantEquipmentOperation_CoolingLoad;
  }

  double PlantEquipmentOperationCoolingLoad::maximumUpperLimit() const {
    return getImpl<detail::PlantEquipmentOperationCoolingLoad_Impl>()->maximumUpperLimit();
  }

  double PlantEquipmentOperationCoolingLoad::minimumLowerLimit() const {
    return getImpl<detail::PlantEquipmentOperationCoolingLoad_Impl>()->minimumLowerLimit();
  }

}  // namespace epmodel
}  // namespace openstudio
