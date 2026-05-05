/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoilSystemHeatingDX.hpp"
#include "CoilSystemHeatingDX_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/CoilSystem_Heating_DX_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  CoilSystemHeatingDX::CoilSystemHeatingDX(const Model& model) : ModelObject(CoilSystemHeatingDX::iddObjectType(), model) {}

  CoilSystemHeatingDX::CoilSystemHeatingDX(std::shared_ptr<detail::CoilSystemHeatingDX_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType CoilSystemHeatingDX::iddObjectType() {
    return IddObjectType::CoilSystem_Heating_DX;
  }

  std::vector<std::string> CoilSystemHeatingDX::heatingCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoilSystem_Heating_DXFields::HeatingCoilObjectType);
  }

  std::string CoilSystemHeatingDX::heatingCoilObjectType() const {
    return getImpl<detail::CoilSystemHeatingDX_Impl>()->heatingCoilObjectType();
  }

  bool CoilSystemHeatingDX::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
    return getImpl<detail::CoilSystemHeatingDX_Impl>()->setHeatingCoilObjectType(heatingCoilObjectType);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string CoilSystemHeatingDX_Impl::heatingCoilObjectType() const {
      const auto value = getString(openstudio::CoilSystem_Heating_DXFields::HeatingCoilObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilSystemHeatingDX_Impl::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
      return setString(openstudio::CoilSystem_Heating_DXFields::HeatingCoilObjectType, heatingCoilObjectType);
    }

    std::vector<std::string> CoilSystemHeatingDX_Impl::heatingCoilObjectTypeValues() const {
      return openstudio::epmodel::CoilSystemHeatingDX::heatingCoilObjectTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
