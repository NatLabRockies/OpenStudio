/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/RefrigerationSubcoolerMechanical.hpp"
#include "ModelObject/RefrigerationSubcoolerMechanical_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Refrigeration_Subcooler_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {
    std::shared_ptr<detail::RefrigerationSubcoolerMechanical_Impl> makeMechanicalImpl(const Model& model) {
      auto modelImpl = model.getImpl<detail::Model_Impl>();
      IdfObject idfObject(RefrigerationSubcoolerMechanical::iddObjectType());
      OS_ASSERT(idfObject.setString(openstudio::Refrigeration_SubcoolerFields::SubcoolerType, "Mechanical"));

      auto impl = modelImpl->createObject(idfObject, false);
      auto typedImpl = std::dynamic_pointer_cast<detail::RefrigerationSubcoolerMechanical_Impl>(impl);
      OS_ASSERT(typedImpl);

      openstudio::detail::WorkspaceObject_ImplPtrVector impls;
      impls.push_back(impl);
      modelImpl->addObjects(impls, openstudio::UHPointerVector(), openstudio::HUPointerVector(), false, false, false);

      return typedImpl;
    }
  }  // namespace

  RefrigerationSubcoolerMechanical::RefrigerationSubcoolerMechanical(const Model& model) : RefrigerationSubcooler(makeMechanicalImpl(model)) {
    OS_ASSERT(setOutletControlTemperature(10.0));
  }

  RefrigerationSubcoolerMechanical::RefrigerationSubcoolerMechanical(std::shared_ptr<detail::RefrigerationSubcoolerMechanical_Impl> impl)
    : RefrigerationSubcooler(std::move(impl)) {}

  IddObjectType RefrigerationSubcoolerMechanical::iddObjectType() {
    return IddObjectType::Refrigeration_Subcooler;
  }

  boost::optional<double> RefrigerationSubcoolerMechanical::outletControlTemperature() const {
    return RefrigerationSubcooler::outletControlTemperature();
  }

  bool RefrigerationSubcoolerMechanical::setOutletControlTemperature(double value) {
    return RefrigerationSubcooler::setOutletControlTemperature(value);
  }

  void RefrigerationSubcoolerMechanical::resetOutletControlTemperature() {
    RefrigerationSubcooler::resetOutletControlTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio
