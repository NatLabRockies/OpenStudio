/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorDryBulbDifference.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorDryBulbDifference_Impl.hpp"

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
      enum DryBulbDifferenceRangeFields
      {
        DRYBULBDIFFERENCERANGEFIELDS_LOWERLIMIT,
        DRYBULBDIFFERENCERANGEFIELDS_UPPERLIMIT,
        DRYBULBDIFFERENCERANGEFIELDS_RANGEEQUIPMENTLISTNAME
      };
    }

    PlantEquipmentOperationOutdoorDryBulbDifference_Impl::PlantEquipmentOperationOutdoorDryBulbDifference_Impl(const IdfObject& idfObject,
                                                                                                               Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationScheme_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == PlantEquipmentOperationOutdoorDryBulbDifference::iddObjectType());
    }

    PlantEquipmentOperationOutdoorDryBulbDifference_Impl::PlantEquipmentOperationOutdoorDryBulbDifference_Impl(
      const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationScheme_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == PlantEquipmentOperationOutdoorDryBulbDifference::iddObjectType());
    }

    PlantEquipmentOperationOutdoorDryBulbDifference_Impl::PlantEquipmentOperationOutdoorDryBulbDifference_Impl(
      const PlantEquipmentOperationOutdoorDryBulbDifference_Impl& other, Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationScheme_Impl(other, model, keepHandle) {}

    double PlantEquipmentOperationOutdoorDryBulbDifference_Impl::maximumUpperLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 100.0;
      }
      const auto& value = groups.back().getDouble(DRYBULBDIFFERENCERANGEFIELDS_UPPERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

    double PlantEquipmentOperationOutdoorDryBulbDifference_Impl::minimumLowerLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return -50.0;
      }
      const auto& value = groups.front().getDouble(DRYBULBDIFFERENCERANGEFIELDS_LOWERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

  }  // namespace detail

  PlantEquipmentOperationOutdoorDryBulbDifference::PlantEquipmentOperationOutdoorDryBulbDifference(const Model& model)
    : PlantEquipmentOperationScheme(PlantEquipmentOperationOutdoorDryBulbDifference::iddObjectType(), model) {
    setName("PlantEquipmentOperationOutdoorDryBulbDifference");
  }

  PlantEquipmentOperationOutdoorDryBulbDifference::PlantEquipmentOperationOutdoorDryBulbDifference(
    std::shared_ptr<detail::PlantEquipmentOperationOutdoorDryBulbDifference_Impl> impl)
    : PlantEquipmentOperationScheme(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationOutdoorDryBulbDifference::iddObjectType() {
    return IddObjectType::PlantEquipmentOperation_OutdoorDryBulbDifference;
  }

  double PlantEquipmentOperationOutdoorDryBulbDifference::maximumUpperLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorDryBulbDifference_Impl>()->maximumUpperLimit();
  }

  double PlantEquipmentOperationOutdoorDryBulbDifference::minimumLowerLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorDryBulbDifference_Impl>()->minimumLowerLimit();
  }

}  // namespace epmodel
}  // namespace openstudio
