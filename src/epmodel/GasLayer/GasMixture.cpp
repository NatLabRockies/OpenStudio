/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GasMixture.hpp"
#include "GasMixture_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WindowMaterial_GasMixture_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  GasMixture::GasMixture(const Model& model) : ModelObject(GasMixture::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::GasMixture_Impl>());

    bool ok = true;
    ok = setThickness(0.003);
    OS_ASSERT(ok);
    ok = setNumberofGasesinMixture(4);
    OS_ASSERT(ok);
    ok = setGas1Type("Air");
    OS_ASSERT(ok);
    ok = setGas1Fraction(0.97);
    OS_ASSERT(ok);
    ok = setGas2Type("Argon");
    OS_ASSERT(ok);
    ok = setGas2Fraction(0.01);
    OS_ASSERT(ok);
    ok = setGas3Type("Krypton");
    OS_ASSERT(ok);
    ok = setGas3Fraction(0.01);
    OS_ASSERT(ok);
    ok = setGas4Type("Xenon");
    OS_ASSERT(ok);
    ok = setGas4Fraction(0.01);
    OS_ASSERT(ok);
  }

  IddObjectType GasMixture::iddObjectType() {
    return IddObjectType::WindowMaterial_GasMixture;
  }

  std::vector<std::string> GasMixture::validGasTypes() {
    static const StringVector result =
      getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowMaterial_GasMixtureFields::Gas1Type);
    OS_ASSERT(!result.empty());
    return result;
  }

  std::vector<std::string> GasMixture::gas1TypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowMaterial_GasMixtureFields::Gas1Type);
  }
  std::vector<std::string> GasMixture::gas2TypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowMaterial_GasMixtureFields::Gas2Type);
  }
  std::vector<std::string> GasMixture::gas3TypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowMaterial_GasMixtureFields::Gas3Type);
  }
  std::vector<std::string> GasMixture::gas4TypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowMaterial_GasMixtureFields::Gas4Type);
  }

  double GasMixture::thickness() const {
    return getImpl<detail::GasMixture_Impl>()->thickness();
  }

  bool GasMixture::setThickness(double thickness) {
    return getImpl<detail::GasMixture_Impl>()->setThickness(thickness);
  }

  int GasMixture::numberofGasesinMixture() const {
    return getImpl<detail::GasMixture_Impl>()->numberofGasesinMixture();
  }

  bool GasMixture::setNumberofGasesinMixture(int numberofGasesinMixture) {
    return getImpl<detail::GasMixture_Impl>()->setNumberofGasesinMixture(numberofGasesinMixture);
  }

  unsigned GasMixture::numGases() const {
    return getImpl<detail::GasMixture_Impl>()->numGases();
  }

  std::string GasMixture::gas1Type() const {
    return getImpl<detail::GasMixture_Impl>()->gas1Type();
  }

  double GasMixture::gas1Fraction() const {
    return getImpl<detail::GasMixture_Impl>()->gas1Fraction();
  }

  bool GasMixture::setGas1Type(const std::string& gas1Type) {
    return getImpl<detail::GasMixture_Impl>()->setGas1Type(gas1Type);
  }

  void GasMixture::resetGas1Type() {
    getImpl<detail::GasMixture_Impl>()->resetGas1Type();
  }

  bool GasMixture::setGas1Fraction(double gas1Fraction) {
    return getImpl<detail::GasMixture_Impl>()->setGas1Fraction(gas1Fraction);
  }

  void GasMixture::resetGas1Fraction() {
    getImpl<detail::GasMixture_Impl>()->resetGas1Fraction();
  }

  std::string GasMixture::gas2Type() const {
    return getImpl<detail::GasMixture_Impl>()->gas2Type();
  }

  double GasMixture::gas2Fraction() const {
    return getImpl<detail::GasMixture_Impl>()->gas2Fraction();
  }

  bool GasMixture::setGas2Type(const std::string& gas2Type) {
    return getImpl<detail::GasMixture_Impl>()->setGas2Type(gas2Type);
  }

  void GasMixture::resetGas2Type() {
    getImpl<detail::GasMixture_Impl>()->resetGas2Type();
  }

  bool GasMixture::setGas2Fraction(double gas2Fraction) {
    return getImpl<detail::GasMixture_Impl>()->setGas2Fraction(gas2Fraction);
  }

  void GasMixture::resetGas2Fraction() {
    getImpl<detail::GasMixture_Impl>()->resetGas2Fraction();
  }

  std::string GasMixture::gas3Type() const {
    return getImpl<detail::GasMixture_Impl>()->gas3Type();
  }

  boost::optional<double> GasMixture::gas3Fraction() const {
    return getImpl<detail::GasMixture_Impl>()->gas3Fraction();
  }

  bool GasMixture::setGas3Type(const std::string& gas3Type) {
    return getImpl<detail::GasMixture_Impl>()->setGas3Type(gas3Type);
  }

  void GasMixture::resetGas3Type() {
    getImpl<detail::GasMixture_Impl>()->resetGas3Type();
  }

  bool GasMixture::setGas3Fraction(double gas3Fraction) {
    return getImpl<detail::GasMixture_Impl>()->setGas3Fraction(gas3Fraction);
  }

  void GasMixture::resetGas3Fraction() {
    getImpl<detail::GasMixture_Impl>()->resetGas3Fraction();
  }

  std::string GasMixture::gas4Type() const {
    return getImpl<detail::GasMixture_Impl>()->gas4Type();
  }

  boost::optional<double> GasMixture::gas4Fraction() const {
    return getImpl<detail::GasMixture_Impl>()->gas4Fraction();
  }

  bool GasMixture::setGas4Type(const std::string& gas4Type) {
    return getImpl<detail::GasMixture_Impl>()->setGas4Type(gas4Type);
  }

  void GasMixture::resetGas4Type() {
    getImpl<detail::GasMixture_Impl>()->resetGas4Type();
  }

  bool GasMixture::setGas4Fraction(double gas4Fraction) {
    return getImpl<detail::GasMixture_Impl>()->setGas4Fraction(gas4Fraction);
  }

  void GasMixture::resetGas4Fraction() {
    getImpl<detail::GasMixture_Impl>()->resetGas4Fraction();
  }

  GasMixture::GasMixture(std::shared_ptr<detail::GasMixture_Impl> impl) : ModelObject(std::move(impl)) {}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double GasMixture_Impl::thickness() const {
      auto value = getDouble(openstudio::WindowMaterial_GasMixtureFields::Thickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GasMixture_Impl::setThickness(double thickness) {
      return setDouble(openstudio::WindowMaterial_GasMixtureFields::Thickness, thickness);
    }

    int GasMixture_Impl::numberofGasesinMixture() const {
      auto value = getInt(openstudio::WindowMaterial_GasMixtureFields::NumberofGasesinMixture, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GasMixture_Impl::setNumberofGasesinMixture(int numberofGasesinMixture) {
      return setInt(openstudio::WindowMaterial_GasMixtureFields::NumberofGasesinMixture, numberofGasesinMixture);
    }

    unsigned GasMixture_Impl::numGases() const {
      auto value = getUnsigned(openstudio::WindowMaterial_GasMixtureFields::NumberofGasesinMixture, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string GasMixture_Impl::gas1Type() const {
      auto value = getString(openstudio::WindowMaterial_GasMixtureFields::Gas1Type, true);
      OS_ASSERT(value);
      return *value;
    }

    double GasMixture_Impl::gas1Fraction() const {
      auto value = getDouble(openstudio::WindowMaterial_GasMixtureFields::Gas1Fraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GasMixture_Impl::setGas1Type(const std::string& gas1Type) {
      return setString(openstudio::WindowMaterial_GasMixtureFields::Gas1Type, gas1Type);
    }

    void GasMixture_Impl::resetGas1Type() {
      bool result = setString(openstudio::WindowMaterial_GasMixtureFields::Gas1Type, "");
      OS_ASSERT(result);
    }

    bool GasMixture_Impl::setGas1Fraction(double gas1Fraction) {
      return setDouble(openstudio::WindowMaterial_GasMixtureFields::Gas1Fraction, gas1Fraction);
    }

    void GasMixture_Impl::resetGas1Fraction() {
      bool result = setString(openstudio::WindowMaterial_GasMixtureFields::Gas1Fraction, "");
      OS_ASSERT(result);
    }

    std::string GasMixture_Impl::gas2Type() const {
      auto value = getString(openstudio::WindowMaterial_GasMixtureFields::Gas2Type, true);
      OS_ASSERT(value);
      return *value;
    }

    double GasMixture_Impl::gas2Fraction() const {
      auto value = getDouble(openstudio::WindowMaterial_GasMixtureFields::Gas2Fraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GasMixture_Impl::setGas2Type(const std::string& gas2Type) {
      return setString(openstudio::WindowMaterial_GasMixtureFields::Gas2Type, gas2Type);
    }

    void GasMixture_Impl::resetGas2Type() {
      bool result = setString(openstudio::WindowMaterial_GasMixtureFields::Gas2Type, "");
      OS_ASSERT(result);
    }

    bool GasMixture_Impl::setGas2Fraction(double gas2Fraction) {
      return setDouble(openstudio::WindowMaterial_GasMixtureFields::Gas2Fraction, gas2Fraction);
    }

    void GasMixture_Impl::resetGas2Fraction() {
      bool result = setString(openstudio::WindowMaterial_GasMixtureFields::Gas2Fraction, "");
      OS_ASSERT(result);
    }

    std::string GasMixture_Impl::gas3Type() const {
      auto value = getString(openstudio::WindowMaterial_GasMixtureFields::Gas3Type, true);
      if (value) {
        return *value;
      }
      return {};
    }

    boost::optional<double> GasMixture_Impl::gas3Fraction() const {
      return getDouble(openstudio::WindowMaterial_GasMixtureFields::Gas3Fraction, true);
    }

    bool GasMixture_Impl::setGas3Type(const std::string& gas3Type) {
      return setString(openstudio::WindowMaterial_GasMixtureFields::Gas3Type, gas3Type);
    }

    void GasMixture_Impl::resetGas3Type() {
      bool result = setString(openstudio::WindowMaterial_GasMixtureFields::Gas3Type, "");
      OS_ASSERT(result);
    }

    bool GasMixture_Impl::setGas3Fraction(double gas3Fraction) {
      return setDouble(openstudio::WindowMaterial_GasMixtureFields::Gas3Fraction, gas3Fraction);
    }

    void GasMixture_Impl::resetGas3Fraction() {
      bool result = setString(openstudio::WindowMaterial_GasMixtureFields::Gas3Fraction, "");
      OS_ASSERT(result);
    }

    std::string GasMixture_Impl::gas4Type() const {
      auto value = getString(openstudio::WindowMaterial_GasMixtureFields::Gas4Type, true);
      if (value) {
        return *value;
      }
      return {};
    }

    boost::optional<double> GasMixture_Impl::gas4Fraction() const {
      return getDouble(openstudio::WindowMaterial_GasMixtureFields::Gas4Fraction, true);
    }

    bool GasMixture_Impl::setGas4Type(const std::string& gas4Type) {
      return setString(openstudio::WindowMaterial_GasMixtureFields::Gas4Type, gas4Type);
    }

    void GasMixture_Impl::resetGas4Type() {
      bool result = setString(openstudio::WindowMaterial_GasMixtureFields::Gas4Type, "");
      OS_ASSERT(result);
    }

    bool GasMixture_Impl::setGas4Fraction(double gas4Fraction) {
      return setDouble(openstudio::WindowMaterial_GasMixtureFields::Gas4Fraction, gas4Fraction);
    }

    void GasMixture_Impl::resetGas4Fraction() {
      bool result = setString(openstudio::WindowMaterial_GasMixtureFields::Gas4Fraction, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
