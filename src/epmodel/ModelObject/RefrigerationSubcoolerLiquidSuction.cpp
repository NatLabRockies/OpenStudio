/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/RefrigerationSubcoolerLiquidSuction.hpp"
#include "ModelObject/RefrigerationSubcoolerLiquidSuction_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Refrigeration_Subcooler_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {
    std::shared_ptr<detail::RefrigerationSubcoolerLiquidSuction_Impl> makeLiquidSuctionImpl(const Model& model) {
      auto modelImpl = model.getImpl<detail::Model_Impl>();
      IdfObject idfObject(RefrigerationSubcoolerLiquidSuction::iddObjectType());
      OS_ASSERT(idfObject.setString(openstudio::Refrigeration_SubcoolerFields::SubcoolerType, "LiquidSuction"));

      auto impl = modelImpl->createObject(idfObject, false);
      auto typedImpl = std::dynamic_pointer_cast<detail::RefrigerationSubcoolerLiquidSuction_Impl>(impl);
      OS_ASSERT(typedImpl);

      openstudio::detail::WorkspaceObject_ImplPtrVector impls;
      impls.push_back(impl);
      modelImpl->addObjects(impls, openstudio::UHPointerVector(), openstudio::HUPointerVector(), false, false, false);

      return typedImpl;
    }
  }  // namespace

  RefrigerationSubcoolerLiquidSuction::RefrigerationSubcoolerLiquidSuction(const Model& model)
    : RefrigerationSubcooler(makeLiquidSuctionImpl(model)) {
    OS_ASSERT(setLiquidSuctionDesignSubcoolingTemperatureDifference(6.0));
    OS_ASSERT(setDesignLiquidInletTemperature(16.0));
    OS_ASSERT(setDesignVaporInletTemperature(0.0));
  }

  RefrigerationSubcoolerLiquidSuction::RefrigerationSubcoolerLiquidSuction(std::shared_ptr<detail::RefrigerationSubcoolerLiquidSuction_Impl> impl)
    : RefrigerationSubcooler(std::move(impl)) {}

  IddObjectType RefrigerationSubcoolerLiquidSuction::iddObjectType() {
    return IddObjectType::Refrigeration_Subcooler;
  }

  boost::optional<double> RefrigerationSubcoolerLiquidSuction::liquidSuctionDesignSubcoolingTemperatureDifference() const {
    return RefrigerationSubcooler::liquidSuctionDesignSubcoolingTemperatureDifference();
  }

  bool RefrigerationSubcoolerLiquidSuction::setLiquidSuctionDesignSubcoolingTemperatureDifference(
    double liquidSuctionDesignSubcoolingTemperatureDifference) {
    return RefrigerationSubcooler::setLiquidSuctionDesignSubcoolingTemperatureDifference(liquidSuctionDesignSubcoolingTemperatureDifference);
  }

  void RefrigerationSubcoolerLiquidSuction::resetLiquidSuctionDesignSubcoolingTemperatureDifference() {
    RefrigerationSubcooler::resetLiquidSuctionDesignSubcoolingTemperatureDifference();
  }

  boost::optional<double> RefrigerationSubcoolerLiquidSuction::designLiquidInletTemperature() const {
    return RefrigerationSubcooler::designLiquidInletTemperature();
  }

  bool RefrigerationSubcoolerLiquidSuction::setDesignLiquidInletTemperature(double designLiquidInletTemperature) {
    return RefrigerationSubcooler::setDesignLiquidInletTemperature(designLiquidInletTemperature);
  }

  void RefrigerationSubcoolerLiquidSuction::resetDesignLiquidInletTemperature() {
    RefrigerationSubcooler::resetDesignLiquidInletTemperature();
  }

  boost::optional<double> RefrigerationSubcoolerLiquidSuction::designVaporInletTemperature() const {
    return RefrigerationSubcooler::designVaporInletTemperature();
  }

  bool RefrigerationSubcoolerLiquidSuction::setDesignVaporInletTemperature(double designVaporInletTemperature) {
    return RefrigerationSubcooler::setDesignVaporInletTemperature(designVaporInletTemperature);
  }

  void RefrigerationSubcoolerLiquidSuction::resetDesignVaporInletTemperature() {
    RefrigerationSubcooler::resetDesignVaporInletTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio
