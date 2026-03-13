/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ModelObject/ZoneHVACExhaustControl.hpp"
#include "ModelObject/ZoneHVACExhaustControl_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_ExhaustControl_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACExhaustControl::ZoneHVACExhaustControl(const Model& model) : ModelObject(ZoneHVACExhaustControl::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACExhaustControl_Impl>());

    autosizeDesignExhaustFlowRate();
    OS_ASSERT(setFlowControlType("Scheduled"));
  }

  ZoneHVACExhaustControl::ZoneHVACExhaustControl(std::shared_ptr<detail::ZoneHVACExhaustControl_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACExhaustControl::iddObjectType() {
    return IddObjectType::ZoneHVAC_ExhaustControl;
  }

  std::vector<std::string> ZoneHVACExhaustControl::flowControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_ExhaustControlFields::FlowControlType);
  }

  std::string ZoneHVACExhaustControl::flowControlType() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->flowControlType();
  }

  bool ZoneHVACExhaustControl::setFlowControlType(const std::string& flowControlType) {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->setFlowControlType(flowControlType);
  }

  bool ZoneHVACExhaustControl::isFlowControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->isFlowControlTypeDefaulted();
  }

  void ZoneHVACExhaustControl::resetFlowControlType() {
    getImpl<detail::ZoneHVACExhaustControl_Impl>()->resetFlowControlType();
  }

  boost::optional<double> ZoneHVACExhaustControl::designExhaustFlowRate() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->designExhaustFlowRate();
  }

  bool ZoneHVACExhaustControl::isDesignExhaustFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->isDesignExhaustFlowRateAutosized();
  }

  bool ZoneHVACExhaustControl::setDesignExhaustFlowRate(double designExhaustFlowRate) {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->setDesignExhaustFlowRate(designExhaustFlowRate);
  }

  void ZoneHVACExhaustControl::autosizeDesignExhaustFlowRate() {
    getImpl<detail::ZoneHVACExhaustControl_Impl>()->autosizeDesignExhaustFlowRate();
  }

  void ZoneHVACExhaustControl::resetDesignExhaustFlowRate() {
    getImpl<detail::ZoneHVACExhaustControl_Impl>()->resetDesignExhaustFlowRate();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> ZoneHVACExhaustControl_Impl::flowControlTypeValues() const {
      return openstudio::epmodel::ZoneHVACExhaustControl::flowControlTypeValues();
    }

    std::string ZoneHVACExhaustControl_Impl::flowControlType() const {
      const auto value = getString(openstudio::ZoneHVAC_ExhaustControlFields::FlowControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACExhaustControl_Impl::isFlowControlTypeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_ExhaustControlFields::FlowControlType);
    }

    bool ZoneHVACExhaustControl_Impl::setFlowControlType(const std::string& flowControlType) {
      return setString(openstudio::ZoneHVAC_ExhaustControlFields::FlowControlType, flowControlType);
    }

    void ZoneHVACExhaustControl_Impl::resetFlowControlType() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_ExhaustControlFields::FlowControlType, ""));
    }

    boost::optional<double> ZoneHVACExhaustControl_Impl::designExhaustFlowRate() const {
      return getDouble(openstudio::ZoneHVAC_ExhaustControlFields::DesignExhaustFlowRate, true);
    }

    bool ZoneHVACExhaustControl_Impl::isDesignExhaustFlowRateAutosized() const {
      return !designExhaustFlowRate();
    }

    bool ZoneHVACExhaustControl_Impl::setDesignExhaustFlowRate(double designExhaustFlowRate) {
      const bool result = setDouble(openstudio::ZoneHVAC_ExhaustControlFields::DesignExhaustFlowRate, designExhaustFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACExhaustControl_Impl::autosizeDesignExhaustFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_ExhaustControlFields::DesignExhaustFlowRate, "autosize"));
    }

    void ZoneHVACExhaustControl_Impl::resetDesignExhaustFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_ExhaustControlFields::DesignExhaustFlowRate, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
