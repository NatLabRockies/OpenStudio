/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorRelativeHumidity.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorRelativeHumidity_Impl.hpp"

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
      enum RelativeHumidityRangeFields
      {
        RELATIVEHUMIDITYRANGEFIELDS_LOWERLIMIT,
        RELATIVEHUMIDITYRANGEFIELDS_UPPERLIMIT,
        RELATIVEHUMIDITYRANGEFIELDS_RANGEEQUIPMENTLISTNAME
      };
    }

    PlantEquipmentOperationOutdoorRelativeHumidity_Impl::PlantEquipmentOperationOutdoorRelativeHumidity_Impl(const IdfObject& idfObject,
                                                                                                             Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == PlantEquipmentOperationOutdoorRelativeHumidity::iddObjectType());
    }

    PlantEquipmentOperationOutdoorRelativeHumidity_Impl::PlantEquipmentOperationOutdoorRelativeHumidity_Impl(
      const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == PlantEquipmentOperationOutdoorRelativeHumidity::iddObjectType());
    }

    PlantEquipmentOperationOutdoorRelativeHumidity_Impl::PlantEquipmentOperationOutdoorRelativeHumidity_Impl(
      const PlantEquipmentOperationOutdoorRelativeHumidity_Impl& other, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    double PlantEquipmentOperationOutdoorRelativeHumidity_Impl::maximumUpperLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 100.0;
      }
      const auto& value = groups.back().getDouble(RELATIVEHUMIDITYRANGEFIELDS_UPPERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

    double PlantEquipmentOperationOutdoorRelativeHumidity_Impl::minimumLowerLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 0.0;
      }
      const auto& value = groups.front().getDouble(RELATIVEHUMIDITYRANGEFIELDS_LOWERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

  }  // namespace detail

  PlantEquipmentOperationOutdoorRelativeHumidity::PlantEquipmentOperationOutdoorRelativeHumidity(const Model& model)
    : ModelObject(PlantEquipmentOperationOutdoorRelativeHumidity::iddObjectType(), model) {
    setName("PlantEquipmentOperationOutdoorRelativeHumidity");
  }

  PlantEquipmentOperationOutdoorRelativeHumidity::PlantEquipmentOperationOutdoorRelativeHumidity(
    std::shared_ptr<detail::PlantEquipmentOperationOutdoorRelativeHumidity_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationOutdoorRelativeHumidity::iddObjectType() {
    return IddObjectType::PlantEquipmentOperation_OutdoorRelativeHumidity;
  }

  double PlantEquipmentOperationOutdoorRelativeHumidity::maximumUpperLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorRelativeHumidity_Impl>()->maximumUpperLimit();
  }

  double PlantEquipmentOperationOutdoorRelativeHumidity::minimumLowerLimit() const {
    return getImpl<detail::PlantEquipmentOperationOutdoorRelativeHumidity_Impl>()->minimumLowerLimit();
  }

}  // namespace epmodel
}  // namespace openstudio
