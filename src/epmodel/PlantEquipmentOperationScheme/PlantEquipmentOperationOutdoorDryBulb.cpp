/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorDryBulb.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorDryBulb_Impl.hpp"

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
      enum DryBulbRangeFields
      {
        DRYBULBRANGEFIELDS_LOWERLIMIT,
        DRYBULBRANGEFIELDS_UPPERLIMIT,
        DRYBULBRANGEFIELDS_RANGEEQUIPMENTLISTNAME
      };
    }

    PlantEquipmentOperationOutdoorDryBulb_Impl::PlantEquipmentOperationOutdoorDryBulb_Impl(const IdfObject& idfObject, Model_Impl* model,
                                                                                           bool keepHandle)
      : PlantEquipmentOperationScheme_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == PlantEquipmentOperationOutdoorDryBulb::iddObjectType());
    }

    PlantEquipmentOperationOutdoorDryBulb_Impl::PlantEquipmentOperationOutdoorDryBulb_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                           Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationScheme_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == PlantEquipmentOperationOutdoorDryBulb::iddObjectType());
    }

    PlantEquipmentOperationOutdoorDryBulb_Impl::PlantEquipmentOperationOutdoorDryBulb_Impl(const PlantEquipmentOperationOutdoorDryBulb_Impl& other,
                                                                                           Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationScheme_Impl(other, model, keepHandle) {}

    double PlantEquipmentOperationOutdoorDryBulb_Impl::maximumUpperLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 70.0;
      }
      const auto& value = groups.back().getDouble(DRYBULBRANGEFIELDS_UPPERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

    double PlantEquipmentOperationOutdoorDryBulb_Impl::minimumLowerLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return -70.0;
      }
      const auto& value = groups.front().getDouble(DRYBULBRANGEFIELDS_LOWERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

  }  // namespace detail

  PlantEquipmentOperationOutdoorDryBulb::PlantEquipmentOperationOutdoorDryBulb(const Model& model)
    : PlantEquipmentOperationScheme(PlantEquipmentOperationOutdoorDryBulb::iddObjectType(), model) {
    setName("PlantEquipmentOperationOutdoorDryBulb");
  }

  PlantEquipmentOperationOutdoorDryBulb::PlantEquipmentOperationOutdoorDryBulb(
    std::shared_ptr<detail::PlantEquipmentOperationOutdoorDryBulb_Impl> impl)
    : PlantEquipmentOperationScheme(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationOutdoorDryBulb::iddObjectType() {
    return IddObjectType::PlantEquipmentOperation_OutdoorDryBulb;
  }

  double PlantEquipmentOperationOutdoorDryBulb::maximumUpperLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorDryBulb_Impl>()->maximumUpperLimit();
  }

  double PlantEquipmentOperationOutdoorDryBulb::minimumLowerLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorDryBulb_Impl>()->minimumLowerLimit();
  }

}  // namespace epmodel
}  // namespace openstudio
