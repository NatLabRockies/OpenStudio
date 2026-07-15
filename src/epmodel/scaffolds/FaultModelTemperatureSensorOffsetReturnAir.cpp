/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelTemperatureSensorOffsetReturnAir.hpp"
#include "FaultModelTemperatureSensorOffsetReturnAir_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_TemperatureSensorOffset_ReturnAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  FaultModelTemperatureSensorOffsetReturnAir::FaultModelTemperatureSensorOffsetReturnAir(const Model& model)
    : ModelObject(FaultModelTemperatureSensorOffsetReturnAir::iddObjectType(), model) {}

  FaultModelTemperatureSensorOffsetReturnAir::FaultModelTemperatureSensorOffsetReturnAir(
    std::shared_ptr<detail::FaultModelTemperatureSensorOffsetReturnAir_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType FaultModelTemperatureSensorOffsetReturnAir::iddObjectType() {
    return IddObjectType::FaultModel_TemperatureSensorOffset_ReturnAir;
  }

  double FaultModelTemperatureSensorOffsetReturnAir::temperatureSensorOffset() const {
    return getImpl<detail::FaultModelTemperatureSensorOffsetReturnAir_Impl>()->temperatureSensorOffset();
  }

  bool FaultModelTemperatureSensorOffsetReturnAir::isTemperatureSensorOffsetDefaulted() const {
    return getImpl<detail::FaultModelTemperatureSensorOffsetReturnAir_Impl>()->isTemperatureSensorOffsetDefaulted();
  }

  bool FaultModelTemperatureSensorOffsetReturnAir::setTemperatureSensorOffset(double temperatureSensorOffset) {
    return getImpl<detail::FaultModelTemperatureSensorOffsetReturnAir_Impl>()->setTemperatureSensorOffset(temperatureSensorOffset);
  }

  void FaultModelTemperatureSensorOffsetReturnAir::resetTemperatureSensorOffset() {
    getImpl<detail::FaultModelTemperatureSensorOffsetReturnAir_Impl>()->resetTemperatureSensorOffset();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double FaultModelTemperatureSensorOffsetReturnAir_Impl::temperatureSensorOffset() const {
      const auto value = getDouble(openstudio::FaultModel_TemperatureSensorOffset_ReturnAirFields::TemperatureSensorOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelTemperatureSensorOffsetReturnAir_Impl::isTemperatureSensorOffsetDefaulted() const {
      return isEmpty(openstudio::FaultModel_TemperatureSensorOffset_ReturnAirFields::TemperatureSensorOffset);
    }

    bool FaultModelTemperatureSensorOffsetReturnAir_Impl::setTemperatureSensorOffset(double temperatureSensorOffset) {
      return setDouble(openstudio::FaultModel_TemperatureSensorOffset_ReturnAirFields::TemperatureSensorOffset, temperatureSensorOffset);
    }

    void FaultModelTemperatureSensorOffsetReturnAir_Impl::resetTemperatureSensorOffset() {
      OS_ASSERT(setString(openstudio::FaultModel_TemperatureSensorOffset_ReturnAirFields::TemperatureSensorOffset, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
