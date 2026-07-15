/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteSolarAndVisibleSpectrum.hpp"
#include "SiteSolarAndVisibleSpectrum_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Site_SolarAndVisibleSpectrum_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SiteSolarAndVisibleSpectrum::SiteSolarAndVisibleSpectrum(const Model& model) : ModelObject(SiteSolarAndVisibleSpectrum::iddObjectType(), model) {}

  SiteSolarAndVisibleSpectrum::SiteSolarAndVisibleSpectrum(std::shared_ptr<detail::SiteSolarAndVisibleSpectrum_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SiteSolarAndVisibleSpectrum::iddObjectType() {
    return IddObjectType::Site_SolarAndVisibleSpectrum;
  }

  std::vector<std::string> SiteSolarAndVisibleSpectrum::spectrumDataMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Site_SolarAndVisibleSpectrumFields::SpectrumDataMethod);
  }

  std::string SiteSolarAndVisibleSpectrum::spectrumDataMethod() const {
    return getImpl<detail::SiteSolarAndVisibleSpectrum_Impl>()->spectrumDataMethod();
  }

  bool SiteSolarAndVisibleSpectrum::isSpectrumDataMethodDefaulted() const {
    return getImpl<detail::SiteSolarAndVisibleSpectrum_Impl>()->isSpectrumDataMethodDefaulted();
  }

  bool SiteSolarAndVisibleSpectrum::setSpectrumDataMethod(const std::string& spectrumDataMethod) {
    return getImpl<detail::SiteSolarAndVisibleSpectrum_Impl>()->setSpectrumDataMethod(spectrumDataMethod);
  }

  void SiteSolarAndVisibleSpectrum::resetSpectrumDataMethod() {
    getImpl<detail::SiteSolarAndVisibleSpectrum_Impl>()->resetSpectrumDataMethod();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SiteSolarAndVisibleSpectrum_Impl::spectrumDataMethod() const {
      const auto value = getString(openstudio::Site_SolarAndVisibleSpectrumFields::SpectrumDataMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteSolarAndVisibleSpectrum_Impl::isSpectrumDataMethodDefaulted() const {
      return isEmpty(openstudio::Site_SolarAndVisibleSpectrumFields::SpectrumDataMethod);
    }

    bool SiteSolarAndVisibleSpectrum_Impl::setSpectrumDataMethod(const std::string& spectrumDataMethod) {
      return setString(openstudio::Site_SolarAndVisibleSpectrumFields::SpectrumDataMethod, spectrumDataMethod);
    }

    void SiteSolarAndVisibleSpectrum_Impl::resetSpectrumDataMethod() {
      OS_ASSERT(setString(openstudio::Site_SolarAndVisibleSpectrumFields::SpectrumDataMethod, ""));
    }

    std::vector<std::string> SiteSolarAndVisibleSpectrum_Impl::spectrumDataMethodValues() const {
      return openstudio::epmodel::SiteSolarAndVisibleSpectrum::spectrumDataMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
