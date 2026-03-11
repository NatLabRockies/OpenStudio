/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneContaminantSourceAndSinkCarbonDioxide.hpp"
#include "ZoneContaminantSourceAndSinkCarbonDioxide_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ZoneContaminantSourceAndSink_CarbonDioxide_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneContaminantSourceAndSinkCarbonDioxide::ZoneContaminantSourceAndSinkCarbonDioxide(const Model& model)
    : ModelObject(ZoneContaminantSourceAndSinkCarbonDioxide::iddObjectType(), model) {}

  ZoneContaminantSourceAndSinkCarbonDioxide::ZoneContaminantSourceAndSinkCarbonDioxide(
    std::shared_ptr<detail::ZoneContaminantSourceAndSinkCarbonDioxide_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneContaminantSourceAndSinkCarbonDioxide::iddObjectType() {
    return IddObjectType::ZoneContaminantSourceAndSink_CarbonDioxide;
  }

  boost::optional<double> ZoneContaminantSourceAndSinkCarbonDioxide::designGenerationRate() const {
    return getImpl<detail::ZoneContaminantSourceAndSinkCarbonDioxide_Impl>()->designGenerationRate();
  }

  bool ZoneContaminantSourceAndSinkCarbonDioxide::setDesignGenerationRate(double designGenerationRate) {
    return getImpl<detail::ZoneContaminantSourceAndSinkCarbonDioxide_Impl>()->setDesignGenerationRate(designGenerationRate);
  }

  void ZoneContaminantSourceAndSinkCarbonDioxide::resetDesignGenerationRate() {
    getImpl<detail::ZoneContaminantSourceAndSinkCarbonDioxide_Impl>()->resetDesignGenerationRate();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ZoneContaminantSourceAndSinkCarbonDioxide_Impl::designGenerationRate() const {
      return getDouble(openstudio::ZoneContaminantSourceAndSink_CarbonDioxideFields::DesignGenerationRate, true);
    }

    bool ZoneContaminantSourceAndSinkCarbonDioxide_Impl::setDesignGenerationRate(double designGenerationRate) {
      const bool result = setDouble(openstudio::ZoneContaminantSourceAndSink_CarbonDioxideFields::DesignGenerationRate, designGenerationRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneContaminantSourceAndSinkCarbonDioxide_Impl::resetDesignGenerationRate() {
      OS_ASSERT(setString(openstudio::ZoneContaminantSourceAndSink_CarbonDioxideFields::DesignGenerationRate, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
