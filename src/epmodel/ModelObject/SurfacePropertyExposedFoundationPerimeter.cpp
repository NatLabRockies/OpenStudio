/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfacePropertyExposedFoundationPerimeter.hpp"
#include "SurfacePropertyExposedFoundationPerimeter_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/SurfaceProperty_ExposedFoundationPerimeter_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SurfacePropertyExposedFoundationPerimeter::SurfacePropertyExposedFoundationPerimeter(const Model& model)
    : ModelObject(SurfacePropertyExposedFoundationPerimeter::iddObjectType(), model) {}

  SurfacePropertyExposedFoundationPerimeter::SurfacePropertyExposedFoundationPerimeter(
    std::shared_ptr<detail::SurfacePropertyExposedFoundationPerimeter_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertyExposedFoundationPerimeter::iddObjectType() {
    return IddObjectType::SurfaceProperty_ExposedFoundationPerimeter;
  }

  std::vector<std::string> SurfacePropertyExposedFoundationPerimeter::exposedPerimeterCalculationMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_ExposedFoundationPerimeterFields::ExposedPerimeterCalculationMethod);
  }

  std::string SurfacePropertyExposedFoundationPerimeter::exposedPerimeterCalculationMethod() const {
    return getImpl<detail::SurfacePropertyExposedFoundationPerimeter_Impl>()->exposedPerimeterCalculationMethod();
  }

  bool SurfacePropertyExposedFoundationPerimeter::setExposedPerimeterCalculationMethod(const std::string& exposedPerimeterCalculationMethod) {
    return getImpl<detail::SurfacePropertyExposedFoundationPerimeter_Impl>()->setExposedPerimeterCalculationMethod(exposedPerimeterCalculationMethod);
  }

  boost::optional<double> SurfacePropertyExposedFoundationPerimeter::totalExposedPerimeter() const {
    return getImpl<detail::SurfacePropertyExposedFoundationPerimeter_Impl>()->totalExposedPerimeter();
  }

  bool SurfacePropertyExposedFoundationPerimeter::setTotalExposedPerimeter(double totalExposedPerimeter) {
    return getImpl<detail::SurfacePropertyExposedFoundationPerimeter_Impl>()->setTotalExposedPerimeter(totalExposedPerimeter);
  }

  double SurfacePropertyExposedFoundationPerimeter::exposedPerimeterFraction() const {
    return getImpl<detail::SurfacePropertyExposedFoundationPerimeter_Impl>()->exposedPerimeterFraction();
  }

  bool SurfacePropertyExposedFoundationPerimeter::setExposedPerimeterFraction(double exposedPerimeterFraction) {
    return getImpl<detail::SurfacePropertyExposedFoundationPerimeter_Impl>()->setExposedPerimeterFraction(exposedPerimeterFraction);
  }

  bool SurfacePropertyExposedFoundationPerimeter::isExposedPerimeterFractionDefaulted() const {
    return getImpl<detail::SurfacePropertyExposedFoundationPerimeter_Impl>()->isExposedPerimeterFractionDefaulted();
  }

  void SurfacePropertyExposedFoundationPerimeter::resetExposedPerimeterFraction() {
    getImpl<detail::SurfacePropertyExposedFoundationPerimeter_Impl>()->resetExposedPerimeterFraction();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SurfacePropertyExposedFoundationPerimeter_Impl::exposedPerimeterCalculationMethod() const {
      boost::optional<std::string> value =
        getString(openstudio::SurfaceProperty_ExposedFoundationPerimeterFields::ExposedPerimeterCalculationMethod, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyExposedFoundationPerimeter_Impl::setExposedPerimeterCalculationMethod(const std::string& exposedPerimeterCalculationMethod) {
      return setString(openstudio::SurfaceProperty_ExposedFoundationPerimeterFields::ExposedPerimeterCalculationMethod,
                       exposedPerimeterCalculationMethod);
    }

    boost::optional<double> SurfacePropertyExposedFoundationPerimeter_Impl::totalExposedPerimeter() const {
      return getDouble(openstudio::SurfaceProperty_ExposedFoundationPerimeterFields::TotalExposedPerimeter, true);
    }

    bool SurfacePropertyExposedFoundationPerimeter_Impl::setTotalExposedPerimeter(double totalExposedPerimeter) {
      const bool result = setDouble(openstudio::SurfaceProperty_ExposedFoundationPerimeterFields::TotalExposedPerimeter, totalExposedPerimeter);
      return result;
    }

    double SurfacePropertyExposedFoundationPerimeter_Impl::exposedPerimeterFraction() const {
      boost::optional<double> value = getDouble(openstudio::SurfaceProperty_ExposedFoundationPerimeterFields::ExposedPerimeterFraction, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyExposedFoundationPerimeter_Impl::setExposedPerimeterFraction(double exposedPerimeterFraction) {
      const bool result = setDouble(openstudio::SurfaceProperty_ExposedFoundationPerimeterFields::ExposedPerimeterFraction, exposedPerimeterFraction);
      return result;
    }

    bool SurfacePropertyExposedFoundationPerimeter_Impl::isExposedPerimeterFractionDefaulted() const {
      return isEmpty(openstudio::SurfaceProperty_ExposedFoundationPerimeterFields::ExposedPerimeterFraction);
    }

    void SurfacePropertyExposedFoundationPerimeter_Impl::resetExposedPerimeterFraction() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ExposedFoundationPerimeterFields::ExposedPerimeterFraction, ""));
    }

    std::vector<std::string> SurfacePropertyExposedFoundationPerimeter_Impl::exposedPerimeterCalculationMethodValues() const {
      return openstudio::epmodel::SurfacePropertyExposedFoundationPerimeter::exposedPerimeterCalculationMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
