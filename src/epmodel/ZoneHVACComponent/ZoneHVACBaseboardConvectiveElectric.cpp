/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACBaseboardConvectiveElectric.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardConvectiveElectric_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_Baseboard_Convective_Electric_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACBaseboardConvectiveElectric::ZoneHVACBaseboardConvectiveElectric(const Model& model)
    : ModelObject(ZoneHVACBaseboardConvectiveElectric::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACBaseboardConvectiveElectric_Impl>());

    autosizeNominalCapacity();
    OS_ASSERT(setEfficiency(1.0));
  }

  ZoneHVACBaseboardConvectiveElectric::ZoneHVACBaseboardConvectiveElectric(std::shared_ptr<detail::ZoneHVACBaseboardConvectiveElectric_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACBaseboardConvectiveElectric::iddObjectType() {
    return IddObjectType::ZoneHVAC_Baseboard_Convective_Electric;
  }

  boost::optional<double> ZoneHVACBaseboardConvectiveElectric::nominalCapacity() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveElectric_Impl>()->nominalCapacity();
  }

  bool ZoneHVACBaseboardConvectiveElectric::isNominalCapacityAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveElectric_Impl>()->isNominalCapacityAutosized();
  }

  bool ZoneHVACBaseboardConvectiveElectric::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveElectric_Impl>()->setNominalCapacity(nominalCapacity);
  }

  void ZoneHVACBaseboardConvectiveElectric::autosizeNominalCapacity() {
    getImpl<detail::ZoneHVACBaseboardConvectiveElectric_Impl>()->autosizeNominalCapacity();
  }

  boost::optional<double> ZoneHVACBaseboardConvectiveElectric::efficiency() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveElectric_Impl>()->efficiency();
  }

  bool ZoneHVACBaseboardConvectiveElectric::isEfficiencyDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveElectric_Impl>()->isEfficiencyDefaulted();
  }

  bool ZoneHVACBaseboardConvectiveElectric::setEfficiency(double efficiency) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveElectric_Impl>()->setEfficiency(efficiency);
  }

  void ZoneHVACBaseboardConvectiveElectric::resetEfficiency() {
    getImpl<detail::ZoneHVACBaseboardConvectiveElectric_Impl>()->resetEfficiency();
  }

  namespace detail {

    boost::optional<double> ZoneHVACBaseboardConvectiveElectric_Impl::nominalCapacity() const {
      return getDouble(ZoneHVAC_Baseboard_Convective_ElectricFields::HeatingDesignCapacity, true);
    }

    bool ZoneHVACBaseboardConvectiveElectric_Impl::isNominalCapacityAutosized() const {
      if (auto value = getString(ZoneHVAC_Baseboard_Convective_ElectricFields::HeatingDesignCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ZoneHVACBaseboardConvectiveElectric_Impl::setNominalCapacity(double nominalCapacity) {
      const bool result = setDouble(ZoneHVAC_Baseboard_Convective_ElectricFields::HeatingDesignCapacity, nominalCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardConvectiveElectric_Impl::autosizeNominalCapacity() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_ElectricFields::HeatingDesignCapacity, "autosize"));
    }

    boost::optional<double> ZoneHVACBaseboardConvectiveElectric_Impl::efficiency() const {
      return getDouble(ZoneHVAC_Baseboard_Convective_ElectricFields::Efficiency, true);
    }

    bool ZoneHVACBaseboardConvectiveElectric_Impl::isEfficiencyDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_Convective_ElectricFields::Efficiency);
    }

    bool ZoneHVACBaseboardConvectiveElectric_Impl::setEfficiency(double efficiency) {
      return setDouble(ZoneHVAC_Baseboard_Convective_ElectricFields::Efficiency, efficiency);
    }

    void ZoneHVACBaseboardConvectiveElectric_Impl::resetEfficiency() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_ElectricFields::Efficiency, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
