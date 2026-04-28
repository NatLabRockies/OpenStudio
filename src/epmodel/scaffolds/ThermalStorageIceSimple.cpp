/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ThermalStorageIceSimple.hpp"
#include "ThermalStorageIceSimple_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/ThermalStorage_Ice_Simple_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  ThermalStorageIceSimple::ThermalStorageIceSimple(const Model& model) : ModelObject(ThermalStorageIceSimple::iddObjectType(), model) {}

  ThermalStorageIceSimple::ThermalStorageIceSimple(std::shared_ptr<detail::ThermalStorageIceSimple_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ThermalStorageIceSimple::iddObjectType() {
    return IddObjectType::ThermalStorage_Ice_Simple;
  }

  std::vector<std::string> ThermalStorageIceSimple::iceStorageTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ThermalStorage_Ice_SimpleFields::IceStorageType);
  }

  boost::optional<double> ThermalStorageIceSimple::capacity() const {
    return getImpl<detail::ThermalStorageIceSimple_Impl>()->capacity();
  }

  bool ThermalStorageIceSimple::setCapacity(double capacity) {
    return getImpl<detail::ThermalStorageIceSimple_Impl>()->setCapacity(capacity);
  }

  bool ThermalStorageIceSimple::isCapacityAutosized() const {
    return getImpl<detail::ThermalStorageIceSimple_Impl>()->isCapacityAutosized();
  }

  void ThermalStorageIceSimple::autosizeCapacity() {
    getImpl<detail::ThermalStorageIceSimple_Impl>()->autosizeCapacity();
  }

  std::string ThermalStorageIceSimple::iceStorageType() const {
    return getImpl<detail::ThermalStorageIceSimple_Impl>()->iceStorageType();
  }

  bool ThermalStorageIceSimple::setIceStorageType(const std::string& iceStorageType) {
    return getImpl<detail::ThermalStorageIceSimple_Impl>()->setIceStorageType(iceStorageType);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ThermalStorageIceSimple_Impl::capacity() const {
      return getDouble(ThermalStorage_Ice_SimpleFields::Capacity, true);
    }

    bool ThermalStorageIceSimple_Impl::setCapacity(double capacity) {
      const bool result = setDouble(ThermalStorage_Ice_SimpleFields::Capacity, capacity);
      OS_ASSERT(result);
      return result;
    }

    bool ThermalStorageIceSimple_Impl::isCapacityAutosized() const {
      if (auto value = getString(ThermalStorage_Ice_SimpleFields::Capacity, true)) {
        return istringEqual(*value, "autosize");
      }
      return false;
    }

    void ThermalStorageIceSimple_Impl::autosizeCapacity() {
      OS_ASSERT(setString(ThermalStorage_Ice_SimpleFields::Capacity, "autosize"));
    }

    std::string ThermalStorageIceSimple_Impl::iceStorageType() const {
      const auto value = getString(ThermalStorage_Ice_SimpleFields::IceStorageType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageIceSimple_Impl::setIceStorageType(const std::string& iceStorageType) {
      return setString(ThermalStorage_Ice_SimpleFields::IceStorageType, iceStorageType);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
