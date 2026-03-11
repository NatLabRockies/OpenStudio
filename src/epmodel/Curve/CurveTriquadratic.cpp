/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveTriquadratic.hpp"
#include "Curve/CurveTriquadratic_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_Triquadratic_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

CurveTriquadratic::CurveTriquadratic(const Model& model) : ModelObject(CurveTriquadratic::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::CurveTriquadratic_Impl>());
}

CurveTriquadratic::CurveTriquadratic(std::shared_ptr<detail::CurveTriquadratic_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType CurveTriquadratic::iddObjectType() {
  return IddObjectType::Curve_Triquadratic;
}

std::vector<std::string> CurveTriquadratic::validInputUnitTypeforXValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_TriquadraticFields::InputUnitTypeforX);
}

std::vector<std::string> CurveTriquadratic::validInputUnitTypeforYValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_TriquadraticFields::InputUnitTypeforY);
}

std::vector<std::string> CurveTriquadratic::validInputUnitTypeforZValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_TriquadraticFields::InputUnitTypeforZ);
}

std::vector<std::string> CurveTriquadratic::validOutputUnitTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_TriquadraticFields::OutputUnitType);
}

#define CURVE_TRIQUADRATIC_OPTIONAL_DOUBLE_FIELDS(X)                                                                                             \
  X(coefficient1Constant)                                                                                                                        \
  X(coefficient2xPOW2)                                                                                                                           \
  X(coefficient3x)                                                                                                                               \
  X(coefficient4yPOW2)                                                                                                                           \
  X(coefficient5y)                                                                                                                               \
  X(coefficient6zPOW2)                                                                                                                           \
  X(coefficient7z)                                                                                                                               \
  X(coefficient8xPOW2TIMESYPOW2)                                                                                                                 \
  X(coefficient9xTIMESY)                                                                                                                         \
  X(coefficient10xTIMESYPOW2)                                                                                                                    \
  X(coefficient11xPOW2TIMESY)                                                                                                                    \
  X(coefficient12xPOW2TIMESZPOW2)                                                                                                                \
  X(coefficient13xTIMESZ)                                                                                                                        \
  X(coefficient14xTIMESZPOW2)                                                                                                                    \
  X(coefficient15xPOW2TIMESZ)                                                                                                                    \
  X(coefficient16yPOW2TIMESZPOW2)                                                                                                                \
  X(coefficient17yTIMESZ)                                                                                                                        \
  X(coefficient18yTIMESZPOW2)                                                                                                                    \
  X(coefficient19yPOW2TIMESZ)                                                                                                                    \
  X(coefficient20xPOW2TIMESYPOW2TIMESZPOW2)                                                                                                      \
  X(coefficient21xPOW2TIMESYPOW2TIMESZ)                                                                                                          \
  X(coefficient22xPOW2TIMESYTIMESZPOW2)                                                                                                          \
  X(coefficient23xTIMESYPOW2TIMESZPOW2)                                                                                                          \
  X(coefficient24xPOW2TIMESYTIMESZ)                                                                                                              \
  X(coefficient25xTIMESYPOW2TIMESZ)                                                                                                              \
  X(coefficient26xTIMESYTIMESZPOW2)                                                                                                              \
  X(coefficient27xTIMESYTIMESZ)                                                                                                                  \
  X(minimumValueofx)                                                                                                                             \
  X(maximumValueofx)                                                                                                                             \
  X(minimumValueofy)                                                                                                                             \
  X(maximumValueofy)                                                                                                                             \
  X(minimumValueofz)                                                                                                                             \
  X(maximumValueofz)                                                                                                                             \
  X(minimumCurveOutput)                                                                                                                          \
  X(maximumCurveOutput)

#define CURVE_TRIQUADRATIC_STRING_FIELDS(X)                                                                                                      \
  X(inputUnitTypeforX)                                                                                                                           \
  X(inputUnitTypeforY)                                                                                                                           \
  X(inputUnitTypeforZ)                                                                                                                           \
  X(outputUnitType)

#define EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_GETTER(name)                                                                                       \
  boost::optional<double> CurveTriquadratic::name() const {                                                                                      \
    return getImpl<detail::CurveTriquadratic_Impl>()->name();                                                                                    \
  }
CURVE_TRIQUADRATIC_OPTIONAL_DOUBLE_FIELDS(EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_GETTER)
#undef EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_GETTER

#define EPMODEL_DEFINE_PUBLIC_STRING_GETTER(name)                                                                                                \
  std::string CurveTriquadratic::name() const {                                                                                                  \
    return getImpl<detail::CurveTriquadratic_Impl>()->name();                                                                                    \
  }
CURVE_TRIQUADRATIC_STRING_FIELDS(EPMODEL_DEFINE_PUBLIC_STRING_GETTER)
#undef EPMODEL_DEFINE_PUBLIC_STRING_GETTER

bool CurveTriquadratic::isInputUnitTypeforXDefaulted() const {
  return getImpl<detail::CurveTriquadratic_Impl>()->isInputUnitTypeforXDefaulted();
}

bool CurveTriquadratic::isInputUnitTypeforYDefaulted() const {
  return getImpl<detail::CurveTriquadratic_Impl>()->isInputUnitTypeforYDefaulted();
}

bool CurveTriquadratic::isInputUnitTypeforZDefaulted() const {
  return getImpl<detail::CurveTriquadratic_Impl>()->isInputUnitTypeforZDefaulted();
}

bool CurveTriquadratic::isOutputUnitTypeDefaulted() const {
  return getImpl<detail::CurveTriquadratic_Impl>()->isOutputUnitTypeDefaulted();
}

#define EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(name, ArgName)                                                                             \
  bool CurveTriquadratic::set##ArgName(double ArgName) {                                                                                         \
    return getImpl<detail::CurveTriquadratic_Impl>()->set##ArgName(ArgName);                                                                    \
  }
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient1Constant, Coefficient1Constant)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient2xPOW2, Coefficient2xPOW2)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient3x, Coefficient3x)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient4yPOW2, Coefficient4yPOW2)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient5y, Coefficient5y)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient6zPOW2, Coefficient6zPOW2)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient7z, Coefficient7z)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient8xPOW2TIMESYPOW2, Coefficient8xPOW2TIMESYPOW2)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient9xTIMESY, Coefficient9xTIMESY)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient10xTIMESYPOW2, Coefficient10xTIMESYPOW2)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient11xPOW2TIMESY, Coefficient11xPOW2TIMESY)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient12xPOW2TIMESZPOW2, Coefficient12xPOW2TIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient13xTIMESZ, Coefficient13xTIMESZ)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient14xTIMESZPOW2, Coefficient14xTIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient15xPOW2TIMESZ, Coefficient15xPOW2TIMESZ)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient16yPOW2TIMESZPOW2, Coefficient16yPOW2TIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient17yTIMESZ, Coefficient17yTIMESZ)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient18yTIMESZPOW2, Coefficient18yTIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient19yPOW2TIMESZ, Coefficient19yPOW2TIMESZ)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient20xPOW2TIMESYPOW2TIMESZPOW2, Coefficient20xPOW2TIMESYPOW2TIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient21xPOW2TIMESYPOW2TIMESZ, Coefficient21xPOW2TIMESYPOW2TIMESZ)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient22xPOW2TIMESYTIMESZPOW2, Coefficient22xPOW2TIMESYTIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient23xTIMESYPOW2TIMESZPOW2, Coefficient23xTIMESYPOW2TIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient24xPOW2TIMESYTIMESZ, Coefficient24xPOW2TIMESYTIMESZ)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient25xTIMESYPOW2TIMESZ, Coefficient25xTIMESYPOW2TIMESZ)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient26xTIMESYTIMESZPOW2, Coefficient26xTIMESYTIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(coefficient27xTIMESYTIMESZ, Coefficient27xTIMESYTIMESZ)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(minimumValueofx, MinimumValueofx)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(maximumValueofx, MaximumValueofx)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(minimumValueofy, MinimumValueofy)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(maximumValueofy, MaximumValueofy)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(minimumValueofz, MinimumValueofz)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(maximumValueofz, MaximumValueofz)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(minimumCurveOutput, MinimumCurveOutput)
EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER(maximumCurveOutput, MaximumCurveOutput)
#undef EPMODEL_DEFINE_PUBLIC_OPTIONAL_DOUBLE_SETTER

#define EPMODEL_DEFINE_PUBLIC_RESETTER(name, ArgName)                                                                                            \
  void CurveTriquadratic::reset##ArgName() {                                                                                                     \
    getImpl<detail::CurveTriquadratic_Impl>()->reset##ArgName();                                                                                 \
  }
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient1Constant, Coefficient1Constant)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient2xPOW2, Coefficient2xPOW2)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient3x, Coefficient3x)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient4yPOW2, Coefficient4yPOW2)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient5y, Coefficient5y)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient6zPOW2, Coefficient6zPOW2)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient7z, Coefficient7z)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient8xPOW2TIMESYPOW2, Coefficient8xPOW2TIMESYPOW2)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient9xTIMESY, Coefficient9xTIMESY)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient10xTIMESYPOW2, Coefficient10xTIMESYPOW2)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient11xPOW2TIMESY, Coefficient11xPOW2TIMESY)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient12xPOW2TIMESZPOW2, Coefficient12xPOW2TIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient13xTIMESZ, Coefficient13xTIMESZ)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient14xTIMESZPOW2, Coefficient14xTIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient15xPOW2TIMESZ, Coefficient15xPOW2TIMESZ)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient16yPOW2TIMESZPOW2, Coefficient16yPOW2TIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient17yTIMESZ, Coefficient17yTIMESZ)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient18yTIMESZPOW2, Coefficient18yTIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient19yPOW2TIMESZ, Coefficient19yPOW2TIMESZ)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient20xPOW2TIMESYPOW2TIMESZPOW2, Coefficient20xPOW2TIMESYPOW2TIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient21xPOW2TIMESYPOW2TIMESZ, Coefficient21xPOW2TIMESYPOW2TIMESZ)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient22xPOW2TIMESYTIMESZPOW2, Coefficient22xPOW2TIMESYTIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient23xTIMESYPOW2TIMESZPOW2, Coefficient23xTIMESYPOW2TIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient24xPOW2TIMESYTIMESZ, Coefficient24xPOW2TIMESYTIMESZ)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient25xTIMESYPOW2TIMESZ, Coefficient25xTIMESYPOW2TIMESZ)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient26xTIMESYTIMESZPOW2, Coefficient26xTIMESYTIMESZPOW2)
EPMODEL_DEFINE_PUBLIC_RESETTER(coefficient27xTIMESYTIMESZ, Coefficient27xTIMESYTIMESZ)
EPMODEL_DEFINE_PUBLIC_RESETTER(minimumValueofx, MinimumValueofx)
EPMODEL_DEFINE_PUBLIC_RESETTER(maximumValueofx, MaximumValueofx)
EPMODEL_DEFINE_PUBLIC_RESETTER(minimumValueofy, MinimumValueofy)
EPMODEL_DEFINE_PUBLIC_RESETTER(maximumValueofy, MaximumValueofy)
EPMODEL_DEFINE_PUBLIC_RESETTER(minimumValueofz, MinimumValueofz)
EPMODEL_DEFINE_PUBLIC_RESETTER(maximumValueofz, MaximumValueofz)
EPMODEL_DEFINE_PUBLIC_RESETTER(minimumCurveOutput, MinimumCurveOutput)
EPMODEL_DEFINE_PUBLIC_RESETTER(maximumCurveOutput, MaximumCurveOutput)
#undef EPMODEL_DEFINE_PUBLIC_RESETTER

bool CurveTriquadratic::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
  return getImpl<detail::CurveTriquadratic_Impl>()->setInputUnitTypeforX(inputUnitTypeforX);
}

void CurveTriquadratic::resetInputUnitTypeforX() {
  getImpl<detail::CurveTriquadratic_Impl>()->resetInputUnitTypeforX();
}

bool CurveTriquadratic::setInputUnitTypeforY(const std::string& inputUnitTypeforY) {
  return getImpl<detail::CurveTriquadratic_Impl>()->setInputUnitTypeforY(inputUnitTypeforY);
}

void CurveTriquadratic::resetInputUnitTypeforY() {
  getImpl<detail::CurveTriquadratic_Impl>()->resetInputUnitTypeforY();
}

bool CurveTriquadratic::setInputUnitTypeforZ(const std::string& inputUnitTypeforZ) {
  return getImpl<detail::CurveTriquadratic_Impl>()->setInputUnitTypeforZ(inputUnitTypeforZ);
}

void CurveTriquadratic::resetInputUnitTypeforZ() {
  getImpl<detail::CurveTriquadratic_Impl>()->resetInputUnitTypeforZ();
}

bool CurveTriquadratic::setOutputUnitType(const std::string& outputUnitType) {
  return getImpl<detail::CurveTriquadratic_Impl>()->setOutputUnitType(outputUnitType);
}

void CurveTriquadratic::resetOutputUnitType() {
  getImpl<detail::CurveTriquadratic_Impl>()->resetOutputUnitType();
}

#undef CURVE_TRIQUADRATIC_OPTIONAL_DOUBLE_FIELDS
#undef CURVE_TRIQUADRATIC_STRING_FIELDS

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

#define CURVE_TRIQUADRATIC_OPTIONAL_DOUBLE_FIELD_MAPPINGS(X)                                                                                     \
  X(coefficient1Constant, Coefficient1Constant)                                                                                                  \
  X(coefficient2xPOW2, Coefficient2x_POW_2)                                                                                                      \
  X(coefficient3x, Coefficient3x)                                                                                                                \
  X(coefficient4yPOW2, Coefficient4y_POW_2)                                                                                                      \
  X(coefficient5y, Coefficient5y)                                                                                                                \
  X(coefficient6zPOW2, Coefficient6z_POW_2)                                                                                                      \
  X(coefficient7z, Coefficient7z)                                                                                                                \
  X(coefficient8xPOW2TIMESYPOW2, Coefficient8x_POW_2_TIMES_y_POW_2)                                                                              \
  X(coefficient9xTIMESY, Coefficient9x_TIMES_y)                                                                                                  \
  X(coefficient10xTIMESYPOW2, Coefficient10x_TIMES_y_POW_2)                                                                                      \
  X(coefficient11xPOW2TIMESY, Coefficient11x_POW_2_TIMES_y)                                                                                      \
  X(coefficient12xPOW2TIMESZPOW2, Coefficient12x_POW_2_TIMES_z_POW_2)                                                                            \
  X(coefficient13xTIMESZ, Coefficient13x_TIMES_z)                                                                                                \
  X(coefficient14xTIMESZPOW2, Coefficient14x_TIMES_z_POW_2)                                                                                      \
  X(coefficient15xPOW2TIMESZ, Coefficient15x_POW_2_TIMES_z)                                                                                      \
  X(coefficient16yPOW2TIMESZPOW2, Coefficient16y_POW_2_TIMES_z_POW_2)                                                                            \
  X(coefficient17yTIMESZ, Coefficient17y_TIMES_z)                                                                                                \
  X(coefficient18yTIMESZPOW2, Coefficient18y_TIMES_z_POW_2)                                                                                      \
  X(coefficient19yPOW2TIMESZ, Coefficient19y_POW_2_TIMES_z)                                                                                      \
  X(coefficient20xPOW2TIMESYPOW2TIMESZPOW2, Coefficient20x_POW_2_TIMES_y_POW_2_TIMES_z_POW_2)                                                   \
  X(coefficient21xPOW2TIMESYPOW2TIMESZ, Coefficient21x_POW_2_TIMES_y_POW_2_TIMES_z)                                                             \
  X(coefficient22xPOW2TIMESYTIMESZPOW2, Coefficient22x_POW_2_TIMES_y_TIMES_z_POW_2)                                                             \
  X(coefficient23xTIMESYPOW2TIMESZPOW2, Coefficient23x_TIMES_y_POW_2_TIMES_z_POW_2)                                                             \
  X(coefficient24xPOW2TIMESYTIMESZ, Coefficient24x_POW_2_TIMES_y_TIMES_z)                                                                        \
  X(coefficient25xTIMESYPOW2TIMESZ, Coefficient25x_TIMES_y_POW_2_TIMES_z)                                                                        \
  X(coefficient26xTIMESYTIMESZPOW2, Coefficient26x_TIMES_y_TIMES_z_POW_2)                                                                        \
  X(coefficient27xTIMESYTIMESZ, Coefficient27x_TIMES_y_TIMES_z)                                                                                  \
  X(minimumValueofx, MinimumValueofx)                                                                                                            \
  X(maximumValueofx, MaximumValueofx)                                                                                                            \
  X(minimumValueofy, MinimumValueofy)                                                                                                            \
  X(maximumValueofy, MaximumValueofy)                                                                                                            \
  X(minimumValueofz, MinimumValueofz)                                                                                                            \
  X(maximumValueofz, MaximumValueofz)                                                                                                            \
  X(minimumCurveOutput, MinimumCurveOutput)                                                                                                      \
  X(maximumCurveOutput, MaximumCurveOutput)

#define EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_GETTER(name, field)                                                                                  \
  boost::optional<double> CurveTriquadratic_Impl::name() const {                                                                                 \
    return getDouble(openstudio::Curve_TriquadraticFields::field, true);                                                                         \
  }
CURVE_TRIQUADRATIC_OPTIONAL_DOUBLE_FIELD_MAPPINGS(EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_GETTER)
#undef EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_GETTER

std::string CurveTriquadratic_Impl::inputUnitTypeforX() const {
  const auto value = getString(openstudio::Curve_TriquadraticFields::InputUnitTypeforX, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveTriquadratic_Impl::isInputUnitTypeforXDefaulted() const {
  return isEmpty(openstudio::Curve_TriquadraticFields::InputUnitTypeforX);
}

std::string CurveTriquadratic_Impl::inputUnitTypeforY() const {
  const auto value = getString(openstudio::Curve_TriquadraticFields::InputUnitTypeforY, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveTriquadratic_Impl::isInputUnitTypeforYDefaulted() const {
  return isEmpty(openstudio::Curve_TriquadraticFields::InputUnitTypeforY);
}

std::string CurveTriquadratic_Impl::inputUnitTypeforZ() const {
  const auto value = getString(openstudio::Curve_TriquadraticFields::InputUnitTypeforZ, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveTriquadratic_Impl::isInputUnitTypeforZDefaulted() const {
  return isEmpty(openstudio::Curve_TriquadraticFields::InputUnitTypeforZ);
}

std::string CurveTriquadratic_Impl::outputUnitType() const {
  const auto value = getString(openstudio::Curve_TriquadraticFields::OutputUnitType, true);
  OS_ASSERT(value);
  return *value;
}

bool CurveTriquadratic_Impl::isOutputUnitTypeDefaulted() const {
  return isEmpty(openstudio::Curve_TriquadraticFields::OutputUnitType);
}

#define EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(name, field, ArgName)                                                                         \
  bool CurveTriquadratic_Impl::set##ArgName(boost::optional<double> ArgName) {                                                                   \
    bool result = false;                                                                                                                          \
    if (ArgName) {                                                                                                                                 \
      result = setDouble(openstudio::Curve_TriquadraticFields::field, ArgName.get());                                                            \
    } else {                                                                                                                                       \
      result = setString(openstudio::Curve_TriquadraticFields::field, "");                                                                      \
    }                                                                                                                                              \
    OS_ASSERT(result);                                                                                                                             \
    return result;                                                                                                                                 \
  }
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient1Constant, Coefficient1Constant, Coefficient1Constant)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient2xPOW2, Coefficient2x_POW_2, Coefficient2xPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient3x, Coefficient3x, Coefficient3x)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient4yPOW2, Coefficient4y_POW_2, Coefficient4yPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient5y, Coefficient5y, Coefficient5y)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient6zPOW2, Coefficient6z_POW_2, Coefficient6zPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient7z, Coefficient7z, Coefficient7z)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient8xPOW2TIMESYPOW2, Coefficient8x_POW_2_TIMES_y_POW_2, Coefficient8xPOW2TIMESYPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient9xTIMESY, Coefficient9x_TIMES_y, Coefficient9xTIMESY)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient10xTIMESYPOW2, Coefficient10x_TIMES_y_POW_2, Coefficient10xTIMESYPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient11xPOW2TIMESY, Coefficient11x_POW_2_TIMES_y, Coefficient11xPOW2TIMESY)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient12xPOW2TIMESZPOW2, Coefficient12x_POW_2_TIMES_z_POW_2, Coefficient12xPOW2TIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient13xTIMESZ, Coefficient13x_TIMES_z, Coefficient13xTIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient14xTIMESZPOW2, Coefficient14x_TIMES_z_POW_2, Coefficient14xTIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient15xPOW2TIMESZ, Coefficient15x_POW_2_TIMES_z, Coefficient15xPOW2TIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient16yPOW2TIMESZPOW2, Coefficient16y_POW_2_TIMES_z_POW_2, Coefficient16yPOW2TIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient17yTIMESZ, Coefficient17y_TIMES_z, Coefficient17yTIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient18yTIMESZPOW2, Coefficient18y_TIMES_z_POW_2, Coefficient18yTIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient19yPOW2TIMESZ, Coefficient19y_POW_2_TIMES_z, Coefficient19yPOW2TIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient20xPOW2TIMESYPOW2TIMESZPOW2, Coefficient20x_POW_2_TIMES_y_POW_2_TIMES_z_POW_2,
                                           Coefficient20xPOW2TIMESYPOW2TIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient21xPOW2TIMESYPOW2TIMESZ, Coefficient21x_POW_2_TIMES_y_POW_2_TIMES_z,
                                           Coefficient21xPOW2TIMESYPOW2TIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient22xPOW2TIMESYTIMESZPOW2, Coefficient22x_POW_2_TIMES_y_TIMES_z_POW_2,
                                           Coefficient22xPOW2TIMESYTIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient23xTIMESYPOW2TIMESZPOW2, Coefficient23x_TIMES_y_POW_2_TIMES_z_POW_2,
                                           Coefficient23xTIMESYPOW2TIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient24xPOW2TIMESYTIMESZ, Coefficient24x_POW_2_TIMES_y_TIMES_z, Coefficient24xPOW2TIMESYTIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient25xTIMESYPOW2TIMESZ, Coefficient25x_TIMES_y_POW_2_TIMES_z, Coefficient25xTIMESYPOW2TIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient26xTIMESYTIMESZPOW2, Coefficient26x_TIMES_y_TIMES_z_POW_2,
                                           Coefficient26xTIMESYTIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(coefficient27xTIMESYTIMESZ, Coefficient27x_TIMES_y_TIMES_z, Coefficient27xTIMESYTIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(minimumValueofx, MinimumValueofx, MinimumValueofx)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(maximumValueofx, MaximumValueofx, MaximumValueofx)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(minimumValueofy, MinimumValueofy, MinimumValueofy)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(maximumValueofy, MaximumValueofy, MaximumValueofy)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(minimumValueofz, MinimumValueofz, MinimumValueofz)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(maximumValueofz, MaximumValueofz, MaximumValueofz)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(minimumCurveOutput, MinimumCurveOutput, MinimumCurveOutput)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER(maximumCurveOutput, MaximumCurveOutput, MaximumCurveOutput)
#undef EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_SETTER

#define EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(name, field, ArgName)                                                                       \
  void CurveTriquadratic_Impl::reset##ArgName() {                                                                                                 \
    const bool result = setString(openstudio::Curve_TriquadraticFields::field, "");                                                             \
    OS_ASSERT(result);                                                                                                                             \
  }
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient1Constant, Coefficient1Constant, Coefficient1Constant)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient2xPOW2, Coefficient2x_POW_2, Coefficient2xPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient3x, Coefficient3x, Coefficient3x)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient4yPOW2, Coefficient4y_POW_2, Coefficient4yPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient5y, Coefficient5y, Coefficient5y)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient6zPOW2, Coefficient6z_POW_2, Coefficient6zPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient7z, Coefficient7z, Coefficient7z)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient8xPOW2TIMESYPOW2, Coefficient8x_POW_2_TIMES_y_POW_2, Coefficient8xPOW2TIMESYPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient9xTIMESY, Coefficient9x_TIMES_y, Coefficient9xTIMESY)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient10xTIMESYPOW2, Coefficient10x_TIMES_y_POW_2, Coefficient10xTIMESYPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient11xPOW2TIMESY, Coefficient11x_POW_2_TIMES_y, Coefficient11xPOW2TIMESY)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient12xPOW2TIMESZPOW2, Coefficient12x_POW_2_TIMES_z_POW_2, Coefficient12xPOW2TIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient13xTIMESZ, Coefficient13x_TIMES_z, Coefficient13xTIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient14xTIMESZPOW2, Coefficient14x_TIMES_z_POW_2, Coefficient14xTIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient15xPOW2TIMESZ, Coefficient15x_POW_2_TIMES_z, Coefficient15xPOW2TIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient16yPOW2TIMESZPOW2, Coefficient16y_POW_2_TIMES_z_POW_2, Coefficient16yPOW2TIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient17yTIMESZ, Coefficient17y_TIMES_z, Coefficient17yTIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient18yTIMESZPOW2, Coefficient18y_TIMES_z_POW_2, Coefficient18yTIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient19yPOW2TIMESZ, Coefficient19y_POW_2_TIMES_z, Coefficient19yPOW2TIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient20xPOW2TIMESYPOW2TIMESZPOW2, Coefficient20x_POW_2_TIMES_y_POW_2_TIMES_z_POW_2,
                                             Coefficient20xPOW2TIMESYPOW2TIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient21xPOW2TIMESYPOW2TIMESZ, Coefficient21x_POW_2_TIMES_y_POW_2_TIMES_z,
                                             Coefficient21xPOW2TIMESYPOW2TIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient22xPOW2TIMESYTIMESZPOW2, Coefficient22x_POW_2_TIMES_y_TIMES_z_POW_2,
                                             Coefficient22xPOW2TIMESYTIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient23xTIMESYPOW2TIMESZPOW2, Coefficient23x_TIMES_y_POW_2_TIMES_z_POW_2,
                                             Coefficient23xTIMESYPOW2TIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient24xPOW2TIMESYTIMESZ, Coefficient24x_POW_2_TIMES_y_TIMES_z,
                                             Coefficient24xPOW2TIMESYTIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient25xTIMESYPOW2TIMESZ, Coefficient25x_TIMES_y_POW_2_TIMES_z,
                                             Coefficient25xTIMESYPOW2TIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient26xTIMESYTIMESZPOW2, Coefficient26x_TIMES_y_TIMES_z_POW_2,
                                             Coefficient26xTIMESYTIMESZPOW2)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(coefficient27xTIMESYTIMESZ, Coefficient27x_TIMES_y_TIMES_z, Coefficient27xTIMESYTIMESZ)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(minimumValueofx, MinimumValueofx, MinimumValueofx)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(maximumValueofx, MaximumValueofx, MaximumValueofx)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(minimumValueofy, MinimumValueofy, MinimumValueofy)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(maximumValueofy, MaximumValueofy, MaximumValueofy)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(minimumValueofz, MinimumValueofz, MinimumValueofz)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(maximumValueofz, MaximumValueofz, MaximumValueofz)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(minimumCurveOutput, MinimumCurveOutput, MinimumCurveOutput)
EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER(maximumCurveOutput, MaximumCurveOutput, MaximumCurveOutput)
#undef EPMODEL_DEFINE_IMPL_OPTIONAL_DOUBLE_RESETTER

bool CurveTriquadratic_Impl::setInputUnitTypeforX(const std::string& inputUnitTypeforX) {
  return setString(openstudio::Curve_TriquadraticFields::InputUnitTypeforX, inputUnitTypeforX);
}

void CurveTriquadratic_Impl::resetInputUnitTypeforX() {
  const bool result = setString(openstudio::Curve_TriquadraticFields::InputUnitTypeforX, "");
  OS_ASSERT(result);
}

bool CurveTriquadratic_Impl::setInputUnitTypeforY(const std::string& inputUnitTypeforY) {
  return setString(openstudio::Curve_TriquadraticFields::InputUnitTypeforY, inputUnitTypeforY);
}

void CurveTriquadratic_Impl::resetInputUnitTypeforY() {
  const bool result = setString(openstudio::Curve_TriquadraticFields::InputUnitTypeforY, "");
  OS_ASSERT(result);
}

bool CurveTriquadratic_Impl::setInputUnitTypeforZ(const std::string& inputUnitTypeforZ) {
  return setString(openstudio::Curve_TriquadraticFields::InputUnitTypeforZ, inputUnitTypeforZ);
}

void CurveTriquadratic_Impl::resetInputUnitTypeforZ() {
  const bool result = setString(openstudio::Curve_TriquadraticFields::InputUnitTypeforZ, "");
  OS_ASSERT(result);
}

bool CurveTriquadratic_Impl::setOutputUnitType(const std::string& outputUnitType) {
  return setString(openstudio::Curve_TriquadraticFields::OutputUnitType, outputUnitType);
}

void CurveTriquadratic_Impl::resetOutputUnitType() {
  const bool result = setString(openstudio::Curve_TriquadraticFields::OutputUnitType, "");
  OS_ASSERT(result);
}

std::vector<std::string> CurveTriquadratic_Impl::validInputUnitTypeforXValues() const {
  return openstudio::epmodel::CurveTriquadratic::validInputUnitTypeforXValues();
}

std::vector<std::string> CurveTriquadratic_Impl::validInputUnitTypeforYValues() const {
  return openstudio::epmodel::CurveTriquadratic::validInputUnitTypeforYValues();
}

std::vector<std::string> CurveTriquadratic_Impl::validInputUnitTypeforZValues() const {
  return openstudio::epmodel::CurveTriquadratic::validInputUnitTypeforZValues();
}

std::vector<std::string> CurveTriquadratic_Impl::validOutputUnitTypeValues() const {
  return openstudio::epmodel::CurveTriquadratic::validOutputUnitTypeValues();
}

#undef CURVE_TRIQUADRATIC_OPTIONAL_DOUBLE_FIELD_MAPPINGS

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
