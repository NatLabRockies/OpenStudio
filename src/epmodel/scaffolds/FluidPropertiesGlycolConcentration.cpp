/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FluidPropertiesGlycolConcentration.hpp"
#include "FluidPropertiesGlycolConcentration_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FluidProperties_GlycolConcentration_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  FluidPropertiesGlycolConcentration::FluidPropertiesGlycolConcentration(const Model& model)
    : ModelObject(FluidPropertiesGlycolConcentration::iddObjectType(), model) {}

  FluidPropertiesGlycolConcentration::FluidPropertiesGlycolConcentration(std::shared_ptr<detail::FluidPropertiesGlycolConcentration_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType FluidPropertiesGlycolConcentration::iddObjectType() {
    return IddObjectType::FluidProperties_GlycolConcentration;
  }

  std::vector<std::string> FluidPropertiesGlycolConcentration::glycolTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::FluidProperties_GlycolConcentrationFields::GlycolType);
  }

  // Glycol type accessors
  std::string FluidPropertiesGlycolConcentration::glycolType() const {
    return getImpl<detail::FluidPropertiesGlycolConcentration_Impl>()->glycolType();
  }

  bool FluidPropertiesGlycolConcentration::setGlycolType(const std::string& glycolType) {
    return getImpl<detail::FluidPropertiesGlycolConcentration_Impl>()->setGlycolType(glycolType);
  }

  // Glycol concentration accessors
  boost::optional<double> FluidPropertiesGlycolConcentration::glycolConcentration() const {
    return getImpl<detail::FluidPropertiesGlycolConcentration_Impl>()->glycolConcentration();
  }

  bool FluidPropertiesGlycolConcentration::setGlycolConcentration(double glycolConcentration) {
    return getImpl<detail::FluidPropertiesGlycolConcentration_Impl>()->setGlycolConcentration(glycolConcentration);
  }

  void FluidPropertiesGlycolConcentration::resetGlycolConcentration() {
    getImpl<detail::FluidPropertiesGlycolConcentration_Impl>()->resetGlycolConcentration();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    // Glycol type accessors
    std::string FluidPropertiesGlycolConcentration_Impl::glycolType() const {
      const auto value = getString(openstudio::FluidProperties_GlycolConcentrationFields::GlycolType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FluidPropertiesGlycolConcentration_Impl::setGlycolType(const std::string& glycolType) {
      return setString(openstudio::FluidProperties_GlycolConcentrationFields::GlycolType, glycolType);
    }

    // Glycol concentration accessors
    boost::optional<double> FluidPropertiesGlycolConcentration_Impl::glycolConcentration() const {
      return getDouble(openstudio::FluidProperties_GlycolConcentrationFields::GlycolConcentration, true);
    }

    bool FluidPropertiesGlycolConcentration_Impl::setGlycolConcentration(double glycolConcentration) {
      return setDouble(openstudio::FluidProperties_GlycolConcentrationFields::GlycolConcentration, glycolConcentration);
    }

    void FluidPropertiesGlycolConcentration_Impl::resetGlycolConcentration() {
      OS_ASSERT(setString(openstudio::FluidProperties_GlycolConcentrationFields::GlycolConcentration, ""));
    }

    std::vector<std::string> FluidPropertiesGlycolConcentration_Impl::glycolTypeValues() const {
      return openstudio::epmodel::FluidPropertiesGlycolConcentration::glycolTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
