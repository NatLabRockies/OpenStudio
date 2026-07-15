/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelHumiditySensorOffsetOutdoorAir.hpp"
#include "FaultModelHumiditySensorOffsetOutdoorAir_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_HumiditySensorOffset_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  FaultModelHumiditySensorOffsetOutdoorAir::FaultModelHumiditySensorOffsetOutdoorAir(const Model& model)
    : ModelObject(FaultModelHumiditySensorOffsetOutdoorAir::iddObjectType(), model) {}

  FaultModelHumiditySensorOffsetOutdoorAir::FaultModelHumiditySensorOffsetOutdoorAir(
    std::shared_ptr<detail::FaultModelHumiditySensorOffsetOutdoorAir_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType FaultModelHumiditySensorOffsetOutdoorAir::iddObjectType() {
    return IddObjectType::FaultModel_HumiditySensorOffset_OutdoorAir;
  }

  double FaultModelHumiditySensorOffsetOutdoorAir::humiditySensorOffset() const {
    return getImpl<detail::FaultModelHumiditySensorOffsetOutdoorAir_Impl>()->humiditySensorOffset();
  }

  bool FaultModelHumiditySensorOffsetOutdoorAir::isHumiditySensorOffsetDefaulted() const {
    return getImpl<detail::FaultModelHumiditySensorOffsetOutdoorAir_Impl>()->isHumiditySensorOffsetDefaulted();
  }

  bool FaultModelHumiditySensorOffsetOutdoorAir::setHumiditySensorOffset(double humiditySensorOffset) {
    return getImpl<detail::FaultModelHumiditySensorOffsetOutdoorAir_Impl>()->setHumiditySensorOffset(humiditySensorOffset);
  }

  void FaultModelHumiditySensorOffsetOutdoorAir::resetHumiditySensorOffset() {
    getImpl<detail::FaultModelHumiditySensorOffsetOutdoorAir_Impl>()->resetHumiditySensorOffset();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double FaultModelHumiditySensorOffsetOutdoorAir_Impl::humiditySensorOffset() const {
      const auto value = getDouble(openstudio::FaultModel_HumiditySensorOffset_OutdoorAirFields::HumiditySensorOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelHumiditySensorOffsetOutdoorAir_Impl::isHumiditySensorOffsetDefaulted() const {
      return isEmpty(openstudio::FaultModel_HumiditySensorOffset_OutdoorAirFields::HumiditySensorOffset);
    }

    bool FaultModelHumiditySensorOffsetOutdoorAir_Impl::setHumiditySensorOffset(double humiditySensorOffset) {
      return setDouble(openstudio::FaultModel_HumiditySensorOffset_OutdoorAirFields::HumiditySensorOffset, humiditySensorOffset);
    }

    void FaultModelHumiditySensorOffsetOutdoorAir_Impl::resetHumiditySensorOffset() {
      OS_ASSERT(setString(openstudio::FaultModel_HumiditySensorOffset_OutdoorAirFields::HumiditySensorOffset, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
