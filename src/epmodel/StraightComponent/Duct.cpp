/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/Duct.hpp"
#include "StraightComponent/Duct_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/Duct_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  Duct::Duct(const Model& model) : StraightComponent(Duct::iddObjectType(), model) {}

  Duct::Duct(std::shared_ptr<detail::Duct_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType Duct::iddObjectType() {
    return IddObjectType::Duct;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned Duct_Impl::inletPort() const {
      // Relationship mapping only: Duct Inlet Node Name
      return openstudio::DuctFields::InletNodeName;
    }

    unsigned Duct_Impl::outletPort() const {
      // Relationship mapping only: Duct Outlet Node Name
      return openstudio::DuctFields::OutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
