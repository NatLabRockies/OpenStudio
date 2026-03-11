/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/OutputConstructions.hpp"
#include "ModelObject/OutputConstructions_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Output_Constructions_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputConstructions::OutputConstructions(const Model& model) : ModelObject(OutputConstructions::iddObjectType(), model) {
  const bool ok = setReportConstructions(true);
  OS_ASSERT(ok);
  const bool ok2 = setReportMaterials(false);
  OS_ASSERT(ok2);
}

OutputConstructions::OutputConstructions(std::shared_ptr<detail::OutputConstructions_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputConstructions::iddObjectType() {
  return IddObjectType::Output_Constructions;
}

bool OutputConstructions::reportConstructions() const {
  return getImpl<detail::OutputConstructions_Impl>()->reportConstructions();
}

bool OutputConstructions::reportMaterials() const {
  return getImpl<detail::OutputConstructions_Impl>()->reportMaterials();
}

bool OutputConstructions::setReportConstructions(bool reportConstructions) {
  return getImpl<detail::OutputConstructions_Impl>()->setReportConstructions(reportConstructions);
}

bool OutputConstructions::setReportMaterials(bool reportMaterials) {
  return getImpl<detail::OutputConstructions_Impl>()->setReportMaterials(reportMaterials);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

constexpr int kDetailsType1 = openstudio::Output_ConstructionsFields::DetailsType1;
constexpr int kDetailsType2 = openstudio::Output_ConstructionsFields::DetailsType2;

bool hasDetail(const ModelObject_Impl& object, const std::string& detailValue) {
  for (int index : {kDetailsType1, kDetailsType2}) {
    if (auto value = object.getString(index, true)) {
      if (openstudio::istringEqual(*value, detailValue)) {
        return true;
      }
    }
  }
  return false;
}

}  // namespace

bool OutputConstructions_Impl::reportConstructions() const {
  return hasDetail(*this, "Constructions");
}

bool OutputConstructions_Impl::reportMaterials() const {
  return hasDetail(*this, "Materials");
}

bool OutputConstructions_Impl::setReportConstructions(bool reportConstructions) {
  return setReportFlags(reportConstructions, reportMaterials());
}

bool OutputConstructions_Impl::setReportMaterials(bool reportMaterials) {
  return setReportFlags(reportConstructions(), reportMaterials);
}

bool OutputConstructions_Impl::setReportFlags(bool reportConstructions, bool reportMaterials) {
  bool result = true;
  if (reportConstructions) {
    result = setString(kDetailsType1, "Constructions") && result;
    result = setString(kDetailsType2, reportMaterials ? "Materials" : "") && result;
  } else if (reportMaterials) {
    result = setString(kDetailsType1, "Materials") && result;
    result = setString(kDetailsType2, "") && result;
  } else {
    result = setString(kDetailsType1, "") && result;
    result = setString(kDetailsType2, "") && result;
  }

  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
