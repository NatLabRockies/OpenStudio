/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorDewpoint.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorDewpoint_Impl.hpp"

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
      enum DewpointRangeFields
      {
        DEWPOINTRANGEFIELDS_LOWERLIMIT,
        DEWPOINTRANGEFIELDS_UPPERLIMIT,
        DEWPOINTRANGEFIELDS_RANGEEQUIPMENTLISTNAME
      };
    }

    PlantEquipmentOperationOutdoorDewpoint_Impl::PlantEquipmentOperationOutdoorDewpoint_Impl(const IdfObject& idfObject, Model_Impl* model,
                                                                                             bool keepHandle)
      : ModelObject_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == PlantEquipmentOperationOutdoorDewpoint::iddObjectType());
    }

    PlantEquipmentOperationOutdoorDewpoint_Impl::PlantEquipmentOperationOutdoorDewpoint_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                             Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == PlantEquipmentOperationOutdoorDewpoint::iddObjectType());
    }

    PlantEquipmentOperationOutdoorDewpoint_Impl::PlantEquipmentOperationOutdoorDewpoint_Impl(const PlantEquipmentOperationOutdoorDewpoint_Impl& other,
                                                                                             Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    double PlantEquipmentOperationOutdoorDewpoint_Impl::maximumUpperLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 70.0;
      }
      const auto& value = groups.back().getDouble(DEWPOINTRANGEFIELDS_UPPERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

    double PlantEquipmentOperationOutdoorDewpoint_Impl::minimumLowerLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return -70.0;
      }
      const auto& value = groups.front().getDouble(DEWPOINTRANGEFIELDS_LOWERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

  }  // namespace detail

  PlantEquipmentOperationOutdoorDewpoint::PlantEquipmentOperationOutdoorDewpoint(const Model& model)
    : ModelObject(PlantEquipmentOperationOutdoorDewpoint::iddObjectType(), model) {
    setName("PlantEquipmentOperationOutdoorDewpoint");
  }

  PlantEquipmentOperationOutdoorDewpoint::PlantEquipmentOperationOutdoorDewpoint(
    std::shared_ptr<detail::PlantEquipmentOperationOutdoorDewpoint_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationOutdoorDewpoint::iddObjectType() {
    return IddObjectType::PlantEquipmentOperation_OutdoorDewpoint;
  }

  double PlantEquipmentOperationOutdoorDewpoint::maximumUpperLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorDewpoint_Impl>()->maximumUpperLimit();
  }

  double PlantEquipmentOperationOutdoorDewpoint::minimumLowerLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorDewpoint_Impl>()->minimumLowerLimit();
  }

}  // namespace epmodel
}  // namespace openstudio
