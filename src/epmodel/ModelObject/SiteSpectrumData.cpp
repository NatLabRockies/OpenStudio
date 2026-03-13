/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteSpectrumData.hpp"
#include "SiteSpectrumData_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Site_SpectrumData_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SiteSpectrumData::SiteSpectrumData(const Model& model) : ModelObject(SiteSpectrumData::iddObjectType(), model) {}

  SiteSpectrumData::SiteSpectrumData(std::shared_ptr<detail::SiteSpectrumData_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SiteSpectrumData::iddObjectType() {
    return IddObjectType::Site_SpectrumData;
  }

  std::vector<std::string> SiteSpectrumData::spectrumDataTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Site_SpectrumDataFields::SpectrumDataType);
  }

  // Spectrum Data Type
  std::string SiteSpectrumData::spectrumDataType() const {
    return getImpl<detail::SiteSpectrumData_Impl>()->spectrumDataType();
  }

  bool SiteSpectrumData::setSpectrumDataType(const std::string& spectrumDataType) {
    return getImpl<detail::SiteSpectrumData_Impl>()->setSpectrumDataType(spectrumDataType);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> SiteSpectrumData_Impl::spectrumDataTypeValues() const {
      return openstudio::epmodel::SiteSpectrumData::spectrumDataTypeValues();
    }

    // Spectrum Data Type
    std::string SiteSpectrumData_Impl::spectrumDataType() const {
      const auto value = getString(openstudio::Site_SpectrumDataFields::SpectrumDataType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteSpectrumData_Impl::setSpectrumDataType(const std::string& spectrumDataType) {
      return setString(openstudio::Site_SpectrumDataFields::SpectrumDataType, spectrumDataType);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
