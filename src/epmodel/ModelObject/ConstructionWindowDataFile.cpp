/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ConstructionWindowDataFile.hpp"
#include "ConstructionWindowDataFile_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Construction_WindowDataFile_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ConstructionWindowDataFile::ConstructionWindowDataFile(const Model& model)
  : ModelObject(ConstructionWindowDataFile::iddObjectType(), model) {}

ConstructionWindowDataFile::ConstructionWindowDataFile(std::shared_ptr<detail::ConstructionWindowDataFile_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ConstructionWindowDataFile::iddObjectType() {
  return IddObjectType::Construction_WindowDataFile;
}

boost::optional<std::string> ConstructionWindowDataFile::fileName() const {
  return getImpl<detail::ConstructionWindowDataFile_Impl>()->fileName();
}

bool ConstructionWindowDataFile::setFileName(const std::string& fileName) {
  return getImpl<detail::ConstructionWindowDataFile_Impl>()->setFileName(fileName);
}

void ConstructionWindowDataFile::resetFileName() {
  getImpl<detail::ConstructionWindowDataFile_Impl>()->resetFileName();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<std::string> ConstructionWindowDataFile_Impl::fileName() const {
  return getString(openstudio::Construction_WindowDataFileFields::FileName, true);
}

bool ConstructionWindowDataFile_Impl::setFileName(const std::string& fileName) {
  const bool result = setString(openstudio::Construction_WindowDataFileFields::FileName, fileName);
  OS_ASSERT(result);
  return result;
}

void ConstructionWindowDataFile_Impl::resetFileName() {
  OS_ASSERT(setString(openstudio::Construction_WindowDataFileFields::FileName, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
