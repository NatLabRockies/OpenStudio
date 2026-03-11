/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/Version.hpp"
#include "ModelObject/Version_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Version_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  Version::Version(const Model& model) : ModelObject(Version::iddObjectType(), model) {}

  Version::Version(std::shared_ptr<detail::Version_Impl> impl) : ModelObject(std::move(impl)) {}

  std::string Version::versionIdentifier() const {
    return getImpl<detail::Version_Impl>()->versionIdentifier();
  }

  bool Version::isVersionIdentifierDefaulted() const {
    return getImpl<detail::Version_Impl>()->isVersionIdentifierDefaulted();
  }

  bool Version::setVersionIdentifier(const std::string& versionIdentifier) {
    return getImpl<detail::Version_Impl>()->setVersionIdentifier(versionIdentifier);
  }

  void Version::resetVersionIdentifier() {
    getImpl<detail::Version_Impl>()->resetVersionIdentifier();
  }

  IddObjectType Version::iddObjectType() {
    return IddObjectType::Version;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string Version_Impl::versionIdentifier() const {
      const auto value = getString(openstudio::VersionFields::VersionIdentifier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Version_Impl::isVersionIdentifierDefaulted() const {
      auto value = getString(openstudio::VersionFields::VersionIdentifier, false);
      if (value) {
        return value->empty();
      }
      return true;
    }

    bool Version_Impl::setVersionIdentifier(const std::string& versionIdentifier) {
      return setString(openstudio::VersionFields::VersionIdentifier, versionIdentifier);
    }

    void Version_Impl::resetVersionIdentifier() {
      OS_ASSERT(setString(openstudio::VersionFields::VersionIdentifier, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
