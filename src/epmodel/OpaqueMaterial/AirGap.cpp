/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OpaqueMaterial/AirGap.hpp"
#include "OpaqueMaterial/AirGap_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Material_AirGap_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirGap::AirGap(const Model& model, double thermalResistance) : OpaqueMaterial(AirGap::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::AirGap_Impl>());
    const bool ok = setThermalResistance(thermalResistance);
    OS_ASSERT(ok);
  }

  AirGap::AirGap(std::shared_ptr<detail::AirGap_Impl> impl) : OpaqueMaterial(std::move(impl)) {}

  IddObjectType AirGap::iddObjectType() {
    return IddObjectType::Material_AirGap;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double AirGap_Impl::thermalResistance() const {
      const auto value = getDouble(openstudio::Material_AirGapFields::ThermalResistance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirGap_Impl::setThermalResistance(double thermalResistance) {
      const bool result = setDouble(openstudio::Material_AirGapFields::ThermalResistance, thermalResistance);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
