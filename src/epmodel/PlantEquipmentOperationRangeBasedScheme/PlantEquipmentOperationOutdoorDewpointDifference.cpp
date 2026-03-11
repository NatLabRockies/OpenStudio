/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorDewpointDifference.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorDewpointDifference_Impl.hpp"

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
      enum DewpointDifferenceRangeFields
      {
        DEWPOINTDIFFERENCERANGEFIELDS_LOWERLIMIT,
        DEWPOINTDIFFERENCERANGEFIELDS_UPPERLIMIT,
        DEWPOINTDIFFERENCERANGEFIELDS_RANGEEQUIPMENTLISTNAME
      };
    }

    PlantEquipmentOperationOutdoorDewpointDifference_Impl::PlantEquipmentOperationOutdoorDewpointDifference_Impl(const IdfObject& idfObject,
                                                                                                                 Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == PlantEquipmentOperationOutdoorDewpointDifference::iddObjectType());
    }

    PlantEquipmentOperationOutdoorDewpointDifference_Impl::PlantEquipmentOperationOutdoorDewpointDifference_Impl(
      const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == PlantEquipmentOperationOutdoorDewpointDifference::iddObjectType());
    }

    PlantEquipmentOperationOutdoorDewpointDifference_Impl::PlantEquipmentOperationOutdoorDewpointDifference_Impl(
      const PlantEquipmentOperationOutdoorDewpointDifference_Impl& other, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    double PlantEquipmentOperationOutdoorDewpointDifference_Impl::maximumUpperLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 100.0;
      }
      const auto& value = groups.back().getDouble(DEWPOINTDIFFERENCERANGEFIELDS_UPPERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

    double PlantEquipmentOperationOutdoorDewpointDifference_Impl::minimumLowerLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return -50.0;
      }
      const auto& value = groups.front().getDouble(DEWPOINTDIFFERENCERANGEFIELDS_LOWERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

  }  // namespace detail

  PlantEquipmentOperationOutdoorDewpointDifference::PlantEquipmentOperationOutdoorDewpointDifference(const Model& model)
    : ModelObject(PlantEquipmentOperationOutdoorDewpointDifference::iddObjectType(), model) {
    setName("PlantEquipmentOperationOutdoorDewpointDifference");
  }

  PlantEquipmentOperationOutdoorDewpointDifference::PlantEquipmentOperationOutdoorDewpointDifference(
    std::shared_ptr<detail::PlantEquipmentOperationOutdoorDewpointDifference_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationOutdoorDewpointDifference::iddObjectType() {
    return IddObjectType::OS_PlantEquipmentOperation_OutdoorDewpointDifference;
  }

  double PlantEquipmentOperationOutdoorDewpointDifference::maximumUpperLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorDewpointDifference_Impl>()->maximumUpperLimit();
  }

  double PlantEquipmentOperationOutdoorDewpointDifference::minimumLowerLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorDewpointDifference_Impl>()->minimumLowerLimit();
  }

}  // namespace epmodel
}  // namespace openstudio
