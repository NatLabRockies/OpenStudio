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

    PlantEquipmentOperationHeatingLoad_Impl::PlantEquipmentOperationHeatingLoad_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationScheme_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == PlantEquipmentOperationHeatingLoad::iddObjectType());
    }

    PlantEquipmentOperationHeatingLoad_Impl::PlantEquipmentOperationHeatingLoad_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationScheme_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == PlantEquipmentOperationHeatingLoad::iddObjectType());
    }

    PlantEquipmentOperationHeatingLoad_Impl::PlantEquipmentOperationHeatingLoad_Impl(const PlantEquipmentOperationHeatingLoad_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationScheme_Impl(other, model, keepHandle) {}

    double PlantEquipmentOperationHeatingLoad_Impl::maximumUpperLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 1E9;
      }
      const auto& value = groups.back().getDouble(LOADRANGEFIELDS_UPPERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

    double PlantEquipmentOperationHeatingLoad_Impl::minimumLowerLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 0.0;
      }
      const auto& value = groups.front().getDouble(LOADRANGEFIELDS_LOWERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

  }  // namespace detail

  PlantEquipmentOperationHeatingLoad::PlantEquipmentOperationHeatingLoad(const Model& model)
    : PlantEquipmentOperationScheme(PlantEquipmentOperationHeatingLoad::iddObjectType(), model) {
    setName("PlantEquipmentOperationHeatingLoad");
  }

  PlantEquipmentOperationHeatingLoad::PlantEquipmentOperationHeatingLoad(std::shared_ptr<detail::PlantEquipmentOperationHeatingLoad_Impl> impl)
    : PlantEquipmentOperationScheme(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationHeatingLoad::iddObjectType() {
    return IddObjectType::PlantEquipmentOperation_HeatingLoad;
  }

  double PlantEquipmentOperationHeatingLoad::maximumUpperLimit() const {
    return getImpl<detail::PlantEquipmentOperationHeatingLoad_Impl>()->maximumUpperLimit();
  }

  double PlantEquipmentOperationHeatingLoad::minimumLowerLimit() const {
    return getImpl<detail::PlantEquipmentOperationHeatingLoad_Impl>()->minimumLowerLimit();
  }

}  // namespace epmodel
}  // namespace openstudio
