/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingElectric.hpp"
#include "StraightComponent/CoilHeatingElectric_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  CoilHeatingElectric::CoilHeatingElectric(const Model& model) : StraightComponent(CoilHeatingElectric::iddObjectType(), model) {}

  CoilHeatingElectric::CoilHeatingElectric(std::shared_ptr<detail::CoilHeatingElectric_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingElectric::iddObjectType() {
    return IddObjectType::Coil_Heating_Electric;
  }

  double CoilHeatingElectric::efficiency() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->efficiency();
  }

  bool CoilHeatingElectric::isEfficiencyDefaulted() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->isEfficiencyDefaulted();
  }

  bool CoilHeatingElectric::setEfficiency(double efficiency) {
    return getImpl<detail::CoilHeatingElectric_Impl>()->setEfficiency(efficiency);
  }

  void CoilHeatingElectric::resetEfficiency() {
    getImpl<detail::CoilHeatingElectric_Impl>()->resetEfficiency();
  }

  boost::optional<double> CoilHeatingElectric::nominalCapacity() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->nominalCapacity();
  }

  bool CoilHeatingElectric::isNominalCapacityDefaulted() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->isNominalCapacityDefaulted();
  }

  bool CoilHeatingElectric::isNominalCapacityAutosized() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->isNominalCapacityAutosized();
  }

  bool CoilHeatingElectric::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::CoilHeatingElectric_Impl>()->setNominalCapacity(nominalCapacity);
  }

  void CoilHeatingElectric::resetNominalCapacity() {
    getImpl<detail::CoilHeatingElectric_Impl>()->resetNominalCapacity();
  }

  void CoilHeatingElectric::autosizeNominalCapacity() {
    getImpl<detail::CoilHeatingElectric_Impl>()->autosizeNominalCapacity();
  }

  boost::optional<double> CoilHeatingElectric::autosizedNominalCapacity() const {
    return getImpl<detail::CoilHeatingElectric_Impl>()->autosizedNominalCapacity();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool isAutosized(const ModelObject_Impl& impl, int fieldIndex) {
        if (const auto value = impl.getString(fieldIndex, true)) {
          return openstudio::istringEqual(*value, "autosize");
        }
        return false;
      }

    }  // namespace

    unsigned CoilHeatingElectric_Impl::inletPort() const {
      return openstudio::Coil_Heating_ElectricFields::AirInletNodeName;
    }

    unsigned CoilHeatingElectric_Impl::outletPort() const {
      return openstudio::Coil_Heating_ElectricFields::AirOutletNodeName;
    }

    double CoilHeatingElectric_Impl::efficiency() const {
      const auto value = getDouble(openstudio::Coil_Heating_ElectricFields::Efficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingElectric_Impl::isEfficiencyDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_ElectricFields::Efficiency);
    }

    bool CoilHeatingElectric_Impl::setEfficiency(double efficiency) {
      return setDouble(openstudio::Coil_Heating_ElectricFields::Efficiency, efficiency);
    }

    void CoilHeatingElectric_Impl::resetEfficiency() {
      const bool result = setString(openstudio::Coil_Heating_ElectricFields::Efficiency, "");
      OS_ASSERT(result);
    }

    boost::optional<double> CoilHeatingElectric_Impl::nominalCapacity() const {
      return getDouble(openstudio::Coil_Heating_ElectricFields::NominalCapacity, true);
    }

    bool CoilHeatingElectric_Impl::isNominalCapacityDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_ElectricFields::NominalCapacity);
    }

    bool CoilHeatingElectric_Impl::isNominalCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Heating_ElectricFields::NominalCapacity);
    }

    bool CoilHeatingElectric_Impl::setNominalCapacity(double nominalCapacity) {
      return setDouble(openstudio::Coil_Heating_ElectricFields::NominalCapacity, nominalCapacity);
    }

    void CoilHeatingElectric_Impl::resetNominalCapacity() {
      const bool result = setString(openstudio::Coil_Heating_ElectricFields::NominalCapacity, "");
      OS_ASSERT(result);
    }

    void CoilHeatingElectric_Impl::autosizeNominalCapacity() {
      const bool result = setString(openstudio::Coil_Heating_ElectricFields::NominalCapacity, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> CoilHeatingElectric_Impl::autosizedNominalCapacity() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
