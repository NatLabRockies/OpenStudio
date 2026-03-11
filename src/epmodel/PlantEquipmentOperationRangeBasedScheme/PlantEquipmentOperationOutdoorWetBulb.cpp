/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorWetBulb.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorWetBulb_Impl.hpp"

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
      enum WetBulbRangeFields
      {
        WETBULBRANGEFIELDS_LOWERLIMIT,
        WETBULBRANGEFIELDS_UPPERLIMIT,
        WETBULBRANGEFIELDS_RANGEEQUIPMENTLISTNAME
      };
    }

    PlantEquipmentOperationOutdoorWetBulb_Impl::PlantEquipmentOperationOutdoorWetBulb_Impl(const IdfObject& idfObject, Model_Impl* model,
                                                                                           bool keepHandle)
      : ModelObject_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == PlantEquipmentOperationOutdoorWetBulb::iddObjectType());
    }

    PlantEquipmentOperationOutdoorWetBulb_Impl::PlantEquipmentOperationOutdoorWetBulb_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                           Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == PlantEquipmentOperationOutdoorWetBulb::iddObjectType());
    }

    PlantEquipmentOperationOutdoorWetBulb_Impl::PlantEquipmentOperationOutdoorWetBulb_Impl(const PlantEquipmentOperationOutdoorWetBulb_Impl& other,
                                                                                           Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    double PlantEquipmentOperationOutdoorWetBulb_Impl::maximumUpperLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 70.0;
      }
      const auto& value = groups.back().getDouble(WETBULBRANGEFIELDS_UPPERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

    double PlantEquipmentOperationOutdoorWetBulb_Impl::minimumLowerLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return -70.0;
      }
      const auto& value = groups.front().getDouble(WETBULBRANGEFIELDS_LOWERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

  }  // namespace detail

  PlantEquipmentOperationOutdoorWetBulb::PlantEquipmentOperationOutdoorWetBulb(const Model& model)
    : ModelObject(PlantEquipmentOperationOutdoorWetBulb::iddObjectType(), model) {
    setName("PlantEquipmentOperationOutdoorWetBulb");
  }

  PlantEquipmentOperationOutdoorWetBulb::PlantEquipmentOperationOutdoorWetBulb(
    std::shared_ptr<detail::PlantEquipmentOperationOutdoorWetBulb_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationOutdoorWetBulb::iddObjectType() {
    return IddObjectType::OS_PlantEquipmentOperation_OutdoorWetBulb;
  }

  double PlantEquipmentOperationOutdoorWetBulb::maximumUpperLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorWetBulb_Impl>()->maximumUpperLimit();
  }

  double PlantEquipmentOperationOutdoorWetBulb::minimumLowerLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorWetBulb_Impl>()->minimumLowerLimit();
  }

}  // namespace epmodel
}  // namespace openstudio
