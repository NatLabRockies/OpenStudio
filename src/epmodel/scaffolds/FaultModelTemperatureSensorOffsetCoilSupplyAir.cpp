/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelTemperatureSensorOffsetCoilSupplyAir.hpp"
#include "FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_TemperatureSensorOffset_CoilSupplyAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  FaultModelTemperatureSensorOffsetCoilSupplyAir::FaultModelTemperatureSensorOffsetCoilSupplyAir(const Model& model)
    : ModelObject(FaultModelTemperatureSensorOffsetCoilSupplyAir::iddObjectType(), model) {}

  FaultModelTemperatureSensorOffsetCoilSupplyAir::FaultModelTemperatureSensorOffsetCoilSupplyAir(
    std::shared_ptr<detail::FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType FaultModelTemperatureSensorOffsetCoilSupplyAir::iddObjectType() {
    return IddObjectType::FaultModel_TemperatureSensorOffset_CoilSupplyAir;
  }

  double FaultModelTemperatureSensorOffsetCoilSupplyAir::referenceSensorOffset() const {
    return getImpl<detail::FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl>()->referenceSensorOffset();
  }

  bool FaultModelTemperatureSensorOffsetCoilSupplyAir::isReferenceSensorOffsetDefaulted() const {
    return getImpl<detail::FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl>()->isReferenceSensorOffsetDefaulted();
  }

  bool FaultModelTemperatureSensorOffsetCoilSupplyAir::setReferenceSensorOffset(double referenceSensorOffset) {
    return getImpl<detail::FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl>()->setReferenceSensorOffset(referenceSensorOffset);
  }

  void FaultModelTemperatureSensorOffsetCoilSupplyAir::resetReferenceSensorOffset() {
    getImpl<detail::FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl>()->resetReferenceSensorOffset();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl::referenceSensorOffset() const {
      const auto value = getDouble(openstudio::FaultModel_TemperatureSensorOffset_CoilSupplyAirFields::ReferenceSensorOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl::isReferenceSensorOffsetDefaulted() const {
      return isEmpty(openstudio::FaultModel_TemperatureSensorOffset_CoilSupplyAirFields::ReferenceSensorOffset);
    }

    bool FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl::setReferenceSensorOffset(double referenceSensorOffset) {
      return setDouble(openstudio::FaultModel_TemperatureSensorOffset_CoilSupplyAirFields::ReferenceSensorOffset, referenceSensorOffset);
    }

    void FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl::resetReferenceSensorOffset() {
      OS_ASSERT(setString(openstudio::FaultModel_TemperatureSensorOffset_CoilSupplyAirFields::ReferenceSensorOffset, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
