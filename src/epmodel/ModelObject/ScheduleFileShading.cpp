/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleFileShading.hpp"
#include "ScheduleFileShading_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Schedule_File_Shading_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ScheduleFileShading::ScheduleFileShading(const Model& model) : ModelObject(ScheduleFileShading::iddObjectType(), model) {}

  ScheduleFileShading::ScheduleFileShading(std::shared_ptr<detail::ScheduleFileShading_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ScheduleFileShading::iddObjectType() {
    return IddObjectType::Schedule_File_Shading;
  }

  // File Name field accessors
  std::string ScheduleFileShading::fileName() const {
    return getImpl<detail::ScheduleFileShading_Impl>()->fileName();
  }

  bool ScheduleFileShading::setFileName(const std::string& fileName) {
    return getImpl<detail::ScheduleFileShading_Impl>()->setFileName(fileName);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    // File Name field accessors
    std::string ScheduleFileShading_Impl::fileName() const {
      const auto value = getString(openstudio::Schedule_File_ShadingFields::FileName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ScheduleFileShading_Impl::setFileName(const std::string& fileName) {
      const bool result = setString(openstudio::Schedule_File_ShadingFields::FileName, fileName);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
