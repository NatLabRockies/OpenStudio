/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneContaminantSourceAndSinkGenericConstant.hpp"
#include "ZoneContaminantSourceAndSinkGenericConstant_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneContaminantSourceAndSink_Generic_Constant_FieldEnums.hxx>
#include <utilities/core/Assert.hpp>

namespace openstudio {
namespace epmodel {

  ZoneContaminantSourceAndSinkGenericConstant::ZoneContaminantSourceAndSinkGenericConstant(const Model& model)
    : ModelObject(ZoneContaminantSourceAndSinkGenericConstant::iddObjectType(), model) {}

  ZoneContaminantSourceAndSinkGenericConstant::ZoneContaminantSourceAndSinkGenericConstant(
    std::shared_ptr<detail::ZoneContaminantSourceAndSinkGenericConstant_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneContaminantSourceAndSinkGenericConstant::iddObjectType() {
    return IddObjectType::ZoneContaminantSourceAndSink_Generic_Constant;
  }

  boost::optional<double> ZoneContaminantSourceAndSinkGenericConstant::designGenerationRate() const {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericConstant_Impl>()->designGenerationRate();
  }

  bool ZoneContaminantSourceAndSinkGenericConstant::setDesignGenerationRate(double designGenerationRate) {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericConstant_Impl>()->setDesignGenerationRate(designGenerationRate);
  }

  void ZoneContaminantSourceAndSinkGenericConstant::resetDesignGenerationRate() {
    getImpl<detail::ZoneContaminantSourceAndSinkGenericConstant_Impl>()->resetDesignGenerationRate();
  }

  boost::optional<double> ZoneContaminantSourceAndSinkGenericConstant::designRemovalCoefficient() const {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericConstant_Impl>()->designRemovalCoefficient();
  }

  bool ZoneContaminantSourceAndSinkGenericConstant::setDesignRemovalCoefficient(double designRemovalCoefficient) {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericConstant_Impl>()->setDesignRemovalCoefficient(designRemovalCoefficient);
  }

  void ZoneContaminantSourceAndSinkGenericConstant::resetDesignRemovalCoefficient() {
    getImpl<detail::ZoneContaminantSourceAndSinkGenericConstant_Impl>()->resetDesignRemovalCoefficient();
  }

  namespace detail {

    boost::optional<double> ZoneContaminantSourceAndSinkGenericConstant_Impl::designGenerationRate() const {
      return getDouble(openstudio::ZoneContaminantSourceAndSink_Generic_ConstantFields::DesignGenerationRate, true);
    }

    bool ZoneContaminantSourceAndSinkGenericConstant_Impl::setDesignGenerationRate(double designGenerationRate) {
      return setDouble(openstudio::ZoneContaminantSourceAndSink_Generic_ConstantFields::DesignGenerationRate, designGenerationRate);
    }

    void ZoneContaminantSourceAndSinkGenericConstant_Impl::resetDesignGenerationRate() {
      const bool result = setString(openstudio::ZoneContaminantSourceAndSink_Generic_ConstantFields::DesignGenerationRate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneContaminantSourceAndSinkGenericConstant_Impl::designRemovalCoefficient() const {
      return getDouble(openstudio::ZoneContaminantSourceAndSink_Generic_ConstantFields::DesignRemovalCoefficient, true);
    }

    bool ZoneContaminantSourceAndSinkGenericConstant_Impl::setDesignRemovalCoefficient(double designRemovalCoefficient) {
      return setDouble(openstudio::ZoneContaminantSourceAndSink_Generic_ConstantFields::DesignRemovalCoefficient, designRemovalCoefficient);
    }

    void ZoneContaminantSourceAndSinkGenericConstant_Impl::resetDesignRemovalCoefficient() {
      const bool result = setString(openstudio::ZoneContaminantSourceAndSink_Generic_ConstantFields::DesignRemovalCoefficient, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
