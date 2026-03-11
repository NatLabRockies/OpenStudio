/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/RefrigerationSubcooler.hpp"
#include "ModelObject/RefrigerationSubcooler_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Refrigeration_Subcooler_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RefrigerationSubcooler::RefrigerationSubcooler(const Model& model) : ModelObject(RefrigerationSubcooler::iddObjectType(), model) {
    OS_ASSERT(setSubcoolerType("LiquidSuction"));
  }

  RefrigerationSubcooler::RefrigerationSubcooler(std::shared_ptr<detail::RefrigerationSubcooler_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType RefrigerationSubcooler::iddObjectType() {
    return IddObjectType::Refrigeration_Subcooler;
  }

  std::vector<std::string> RefrigerationSubcooler::subcoolerTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Refrigeration_SubcoolerFields::SubcoolerType);
  }

  std::string RefrigerationSubcooler::subcoolerType() const {
    return getImpl<detail::RefrigerationSubcooler_Impl>()->subcoolerType();
  }

  bool RefrigerationSubcooler::setSubcoolerType(const std::string& subcoolerType) {
    return getImpl<detail::RefrigerationSubcooler_Impl>()->setSubcoolerType(subcoolerType);
  }

  boost::optional<double> RefrigerationSubcooler::liquidSuctionDesignSubcoolingTemperatureDifference() const {
    return getImpl<detail::RefrigerationSubcooler_Impl>()->liquidSuctionDesignSubcoolingTemperatureDifference();
  }

  boost::optional<double> RefrigerationSubcooler::designLiquidInletTemperature() const {
    return getImpl<detail::RefrigerationSubcooler_Impl>()->designLiquidInletTemperature();
  }

  boost::optional<double> RefrigerationSubcooler::designVaporInletTemperature() const {
    return getImpl<detail::RefrigerationSubcooler_Impl>()->designVaporInletTemperature();
  }

  boost::optional<double> RefrigerationSubcooler::outletControlTemperature() const {
    return getImpl<detail::RefrigerationSubcooler_Impl>()->outletControlTemperature();
  }

  bool RefrigerationSubcooler::setLiquidSuctionDesignSubcoolingTemperatureDifference(double value) {
    return getImpl<detail::RefrigerationSubcooler_Impl>()->setLiquidSuctionDesignSubcoolingTemperatureDifference(value);
  }

  void RefrigerationSubcooler::resetLiquidSuctionDesignSubcoolingTemperatureDifference() {
    getImpl<detail::RefrigerationSubcooler_Impl>()->resetLiquidSuctionDesignSubcoolingTemperatureDifference();
  }

  bool RefrigerationSubcooler::setDesignLiquidInletTemperature(double value) {
    return getImpl<detail::RefrigerationSubcooler_Impl>()->setDesignLiquidInletTemperature(value);
  }

  void RefrigerationSubcooler::resetDesignLiquidInletTemperature() {
    getImpl<detail::RefrigerationSubcooler_Impl>()->resetDesignLiquidInletTemperature();
  }

  bool RefrigerationSubcooler::setDesignVaporInletTemperature(double value) {
    return getImpl<detail::RefrigerationSubcooler_Impl>()->setDesignVaporInletTemperature(value);
  }

  void RefrigerationSubcooler::resetDesignVaporInletTemperature() {
    getImpl<detail::RefrigerationSubcooler_Impl>()->resetDesignVaporInletTemperature();
  }

  bool RefrigerationSubcooler::setOutletControlTemperature(double value) {
    return getImpl<detail::RefrigerationSubcooler_Impl>()->setOutletControlTemperature(value);
  }

  void RefrigerationSubcooler::resetOutletControlTemperature() {
    getImpl<detail::RefrigerationSubcooler_Impl>()->resetOutletControlTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string RefrigerationSubcooler_Impl::subcoolerType() const {
      auto value = getString(openstudio::Refrigeration_SubcoolerFields::SubcoolerType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationSubcooler_Impl::setSubcoolerType(const std::string& subcoolerType) {
      return setString(openstudio::Refrigeration_SubcoolerFields::SubcoolerType, subcoolerType, true);
    }

    boost::optional<double> RefrigerationSubcooler_Impl::liquidSuctionDesignSubcoolingTemperatureDifference() const {
      return getDouble(openstudio::Refrigeration_SubcoolerFields::LiquidSuctionDesignSubcoolingTemperatureDifference, true);
    }

    boost::optional<double> RefrigerationSubcooler_Impl::designLiquidInletTemperature() const {
      return getDouble(openstudio::Refrigeration_SubcoolerFields::DesignLiquidInletTemperature, true);
    }

    boost::optional<double> RefrigerationSubcooler_Impl::designVaporInletTemperature() const {
      return getDouble(openstudio::Refrigeration_SubcoolerFields::DesignVaporInletTemperature, true);
    }

    boost::optional<double> RefrigerationSubcooler_Impl::outletControlTemperature() const {
      return getDouble(openstudio::Refrigeration_SubcoolerFields::OutletControlTemperature, true);
    }

    bool RefrigerationSubcooler_Impl::setLiquidSuctionDesignSubcoolingTemperatureDifference(boost::optional<double> value) {
      if (value) {
        return setDouble(openstudio::Refrigeration_SubcoolerFields::LiquidSuctionDesignSubcoolingTemperatureDifference, *value);
      }
      resetLiquidSuctionDesignSubcoolingTemperatureDifference();
      return true;
    }

    void RefrigerationSubcooler_Impl::resetLiquidSuctionDesignSubcoolingTemperatureDifference() {
      OS_ASSERT(setString(openstudio::Refrigeration_SubcoolerFields::LiquidSuctionDesignSubcoolingTemperatureDifference, ""));
    }

    bool RefrigerationSubcooler_Impl::setDesignLiquidInletTemperature(boost::optional<double> value) {
      if (value) {
        return setDouble(openstudio::Refrigeration_SubcoolerFields::DesignLiquidInletTemperature, *value);
      }
      resetDesignLiquidInletTemperature();
      return true;
    }

    void RefrigerationSubcooler_Impl::resetDesignLiquidInletTemperature() {
      OS_ASSERT(setString(openstudio::Refrigeration_SubcoolerFields::DesignLiquidInletTemperature, ""));
    }

    bool RefrigerationSubcooler_Impl::setDesignVaporInletTemperature(boost::optional<double> value) {
      if (value) {
        return setDouble(openstudio::Refrigeration_SubcoolerFields::DesignVaporInletTemperature, *value);
      }
      resetDesignVaporInletTemperature();
      return true;
    }

    void RefrigerationSubcooler_Impl::resetDesignVaporInletTemperature() {
      OS_ASSERT(setString(openstudio::Refrigeration_SubcoolerFields::DesignVaporInletTemperature, ""));
    }

    bool RefrigerationSubcooler_Impl::setOutletControlTemperature(boost::optional<double> value) {
      if (value) {
        return setDouble(openstudio::Refrigeration_SubcoolerFields::OutletControlTemperature, *value);
      }
      resetOutletControlTemperature();
      return true;
    }

    void RefrigerationSubcooler_Impl::resetOutletControlTemperature() {
      OS_ASSERT(setString(openstudio::Refrigeration_SubcoolerFields::OutletControlTemperature, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
