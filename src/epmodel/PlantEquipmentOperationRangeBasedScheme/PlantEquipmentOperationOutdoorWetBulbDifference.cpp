/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorWetBulbDifference.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorWetBulbDifference_Impl.hpp"

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
      enum WetBulbDifferenceRangeFields
      {
        WETBULBDIFFERENCERANGEFIELDS_LOWERLIMIT,
        WETBULBDIFFERENCERANGEFIELDS_UPPERLIMIT,
        WETBULBDIFFERENCERANGEFIELDS_RANGEEQUIPMENTLISTNAME
      };
    }

    PlantEquipmentOperationOutdoorWetBulbDifference_Impl::PlantEquipmentOperationOutdoorWetBulbDifference_Impl(const IdfObject& idfObject,
                                                                                                               Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == PlantEquipmentOperationOutdoorWetBulbDifference::iddObjectType());
    }

    PlantEquipmentOperationOutdoorWetBulbDifference_Impl::PlantEquipmentOperationOutdoorWetBulbDifference_Impl(
      const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == PlantEquipmentOperationOutdoorWetBulbDifference::iddObjectType());
    }

    PlantEquipmentOperationOutdoorWetBulbDifference_Impl::PlantEquipmentOperationOutdoorWetBulbDifference_Impl(
      const PlantEquipmentOperationOutdoorWetBulbDifference_Impl& other, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    double PlantEquipmentOperationOutdoorWetBulbDifference_Impl::maximumUpperLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 100.0;
      }
      const auto& value = groups.back().getDouble(WETBULBDIFFERENCERANGEFIELDS_UPPERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

    double PlantEquipmentOperationOutdoorWetBulbDifference_Impl::minimumLowerLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return -50.0;
      }
      const auto& value = groups.front().getDouble(WETBULBDIFFERENCERANGEFIELDS_LOWERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

  }  // namespace detail

  PlantEquipmentOperationOutdoorWetBulbDifference::PlantEquipmentOperationOutdoorWetBulbDifference(const Model& model)
    : ModelObject(PlantEquipmentOperationOutdoorWetBulbDifference::iddObjectType(), model) {
    setName("PlantEquipmentOperationOutdoorWetBulbDifference");
  }

  PlantEquipmentOperationOutdoorWetBulbDifference::PlantEquipmentOperationOutdoorWetBulbDifference(
    std::shared_ptr<detail::PlantEquipmentOperationOutdoorWetBulbDifference_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationOutdoorWetBulbDifference::iddObjectType() {
    return IddObjectType::OS_PlantEquipmentOperation_OutdoorWetBulbDifference;
  }

  double PlantEquipmentOperationOutdoorWetBulbDifference::maximumUpperLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorWetBulbDifference_Impl>()->maximumUpperLimit();
  }

  double PlantEquipmentOperationOutdoorWetBulbDifference::minimumLowerLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorWetBulbDifference_Impl>()->minimumLowerLimit();
  }

}  // namespace epmodel
}  // namespace openstudio
