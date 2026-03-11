/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/RefrigerationSubcoolerLiquidSuction.hpp"
#include "ModelObject/RefrigerationSubcoolerLiquidSuction_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Refrigeration_Subcooler_FieldEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  RefrigerationSubcoolerLiquidSuction::RefrigerationSubcoolerLiquidSuction(const Model& model)
    : ModelObject(RefrigerationSubcoolerLiquidSuction::iddObjectType(), model) {
    auto impl = getImpl<detail::RefrigerationSubcoolerLiquidSuction_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(impl->setString(Refrigeration_SubcoolerFields::SubcoolerType, "LiquidSuction"));
    OS_ASSERT(setLiquidSuctionDesignSubcoolingTemperatureDifference(6.0));
    OS_ASSERT(setDesignLiquidInletTemperature(16.0));
    OS_ASSERT(setDesignVaporInletTemperature(0.0));
  }

  RefrigerationSubcoolerLiquidSuction::RefrigerationSubcoolerLiquidSuction(std::shared_ptr<detail::RefrigerationSubcoolerLiquidSuction_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType RefrigerationSubcoolerLiquidSuction::iddObjectType() {
    return IddObjectType::Refrigeration_Subcooler;
  }

  boost::optional<double> RefrigerationSubcoolerLiquidSuction::liquidSuctionDesignSubcoolingTemperatureDifference() const {
    return getImpl<detail::RefrigerationSubcoolerLiquidSuction_Impl>()->liquidSuctionDesignSubcoolingTemperatureDifference();
  }

  boost::optional<double> RefrigerationSubcoolerLiquidSuction::designLiquidInletTemperature() const {
    return getImpl<detail::RefrigerationSubcoolerLiquidSuction_Impl>()->designLiquidInletTemperature();
  }

  boost::optional<double> RefrigerationSubcoolerLiquidSuction::designVaporInletTemperature() const {
    return getImpl<detail::RefrigerationSubcoolerLiquidSuction_Impl>()->designVaporInletTemperature();
  }

  bool RefrigerationSubcoolerLiquidSuction::setLiquidSuctionDesignSubcoolingTemperatureDifference(
    double liquidSuctionDesignSubcoolingTemperatureDifference) {
    return getImpl<detail::RefrigerationSubcoolerLiquidSuction_Impl>()->setLiquidSuctionDesignSubcoolingTemperatureDifference(
      liquidSuctionDesignSubcoolingTemperatureDifference);
  }

  void RefrigerationSubcoolerLiquidSuction::resetLiquidSuctionDesignSubcoolingTemperatureDifference() {
    getImpl<detail::RefrigerationSubcoolerLiquidSuction_Impl>()->resetLiquidSuctionDesignSubcoolingTemperatureDifference();
  }

  bool RefrigerationSubcoolerLiquidSuction::setDesignLiquidInletTemperature(double designLiquidInletTemperature) {
    return getImpl<detail::RefrigerationSubcoolerLiquidSuction_Impl>()->setDesignLiquidInletTemperature(designLiquidInletTemperature);
  }

  void RefrigerationSubcoolerLiquidSuction::resetDesignLiquidInletTemperature() {
    getImpl<detail::RefrigerationSubcoolerLiquidSuction_Impl>()->resetDesignLiquidInletTemperature();
  }

  bool RefrigerationSubcoolerLiquidSuction::setDesignVaporInletTemperature(double designVaporInletTemperature) {
    return getImpl<detail::RefrigerationSubcoolerLiquidSuction_Impl>()->setDesignVaporInletTemperature(designVaporInletTemperature);
  }

  void RefrigerationSubcoolerLiquidSuction::resetDesignVaporInletTemperature() {
    getImpl<detail::RefrigerationSubcoolerLiquidSuction_Impl>()->resetDesignVaporInletTemperature();
  }

  namespace detail {

    boost::optional<double> RefrigerationSubcoolerLiquidSuction_Impl::liquidSuctionDesignSubcoolingTemperatureDifference() const {
      return getDouble(Refrigeration_SubcoolerFields::LiquidSuctionDesignSubcoolingTemperatureDifference, true);
    }

    boost::optional<double> RefrigerationSubcoolerLiquidSuction_Impl::designLiquidInletTemperature() const {
      return getDouble(Refrigeration_SubcoolerFields::DesignLiquidInletTemperature, true);
    }

    boost::optional<double> RefrigerationSubcoolerLiquidSuction_Impl::designVaporInletTemperature() const {
      return getDouble(Refrigeration_SubcoolerFields::DesignVaporInletTemperature, true);
    }

    bool RefrigerationSubcoolerLiquidSuction_Impl::setLiquidSuctionDesignSubcoolingTemperatureDifference(
      boost::optional<double> liquidSuctionDesignSubcoolingTemperatureDifference) {
      bool result(false);
      if (liquidSuctionDesignSubcoolingTemperatureDifference) {
        result = setDouble(Refrigeration_SubcoolerFields::LiquidSuctionDesignSubcoolingTemperatureDifference,
                           liquidSuctionDesignSubcoolingTemperatureDifference.get());
      } else {
        resetLiquidSuctionDesignSubcoolingTemperatureDifference();
        result = true;
      }
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSubcoolerLiquidSuction_Impl::resetLiquidSuctionDesignSubcoolingTemperatureDifference() {
      const bool result = setString(Refrigeration_SubcoolerFields::LiquidSuctionDesignSubcoolingTemperatureDifference, "");
      OS_ASSERT(result);
    }

    bool RefrigerationSubcoolerLiquidSuction_Impl::setDesignLiquidInletTemperature(boost::optional<double> designLiquidInletTemperature) {
      bool result(false);
      if (designLiquidInletTemperature) {
        result = setDouble(Refrigeration_SubcoolerFields::DesignLiquidInletTemperature, designLiquidInletTemperature.get());
      } else {
        resetDesignLiquidInletTemperature();
        result = true;
      }
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSubcoolerLiquidSuction_Impl::resetDesignLiquidInletTemperature() {
      const bool result = setString(Refrigeration_SubcoolerFields::DesignLiquidInletTemperature, "");
      OS_ASSERT(result);
    }

    bool RefrigerationSubcoolerLiquidSuction_Impl::setDesignVaporInletTemperature(boost::optional<double> designVaporInletTemperature) {
      bool result(false);
      if (designVaporInletTemperature) {
        result = setDouble(Refrigeration_SubcoolerFields::DesignVaporInletTemperature, designVaporInletTemperature.get());
      } else {
        resetDesignVaporInletTemperature();
        result = true;
      }
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationSubcoolerLiquidSuction_Impl::resetDesignVaporInletTemperature() {
      const bool result = setString(Refrigeration_SubcoolerFields::DesignVaporInletTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
