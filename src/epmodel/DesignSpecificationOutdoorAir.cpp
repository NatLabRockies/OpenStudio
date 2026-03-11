/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DesignSpecificationOutdoorAir.hpp"
#include "DesignSpecificationOutdoorAir_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DesignSpecification_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

DesignSpecificationOutdoorAir::DesignSpecificationOutdoorAir(const Model& model)
  : ModelObject(DesignSpecificationOutdoorAir::iddObjectType(), model) {
  auto impl = getImpl<detail::DesignSpecificationOutdoorAir_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

DesignSpecificationOutdoorAir::DesignSpecificationOutdoorAir(std::shared_ptr<detail::DesignSpecificationOutdoorAir_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType DesignSpecificationOutdoorAir::iddObjectType() {
  return IddObjectType::DesignSpecification_OutdoorAir;
}

std::string DesignSpecificationOutdoorAir::outdoorAirMethod() const {
  return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->outdoorAirMethod();
}

bool DesignSpecificationOutdoorAir::setOutdoorAirMethod(const std::string& value) {
  return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->setOutdoorAirMethod(value);
}

double DesignSpecificationOutdoorAir::outdoorAirFlowperPerson() const {
  return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->outdoorAirFlowperPerson();
}

bool DesignSpecificationOutdoorAir::setOutdoorAirFlowperPerson(double value) {
  return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->setOutdoorAirFlowperPerson(value);
}

double DesignSpecificationOutdoorAir::outdoorAirFlowperFloorArea() const {
  return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->outdoorAirFlowperFloorArea();
}

bool DesignSpecificationOutdoorAir::setOutdoorAirFlowperFloorArea(double value) {
  return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->setOutdoorAirFlowperFloorArea(value);
}

double DesignSpecificationOutdoorAir::outdoorAirFlowRate() const {
  return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->outdoorAirFlowRate();
}

bool DesignSpecificationOutdoorAir::setOutdoorAirFlowRate(double value) {
  return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->setOutdoorAirFlowRate(value);
}

double DesignSpecificationOutdoorAir::outdoorAirFlowAirChangesperHour() const {
  return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->outdoorAirFlowAirChangesperHour();
}

bool DesignSpecificationOutdoorAir::setOutdoorAirFlowAirChangesperHour(double value) {
  return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->setOutdoorAirFlowAirChangesperHour(value);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string DesignSpecificationOutdoorAir_Impl::outdoorAirMethod() const {
  if (auto value = getString(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirMethod, true)) {
    if (!value->empty()) {
      return *value;
    }
  }
  return "Sum";
}

bool DesignSpecificationOutdoorAir_Impl::setOutdoorAirMethod(const std::string& value) {
  return setString(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirMethod, value);
}

double DesignSpecificationOutdoorAir_Impl::outdoorAirFlowperPerson() const {
  if (auto value = getDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperPerson, true)) {
    return *value;
  }
  return 0.0;
}

bool DesignSpecificationOutdoorAir_Impl::setOutdoorAirFlowperPerson(double value) {
  return setDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperPerson, value);
}

double DesignSpecificationOutdoorAir_Impl::outdoorAirFlowperFloorArea() const {
  if (auto value = getDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZoneFloorArea, true)) {
    return *value;
  }
  return 0.0;
}

bool DesignSpecificationOutdoorAir_Impl::setOutdoorAirFlowperFloorArea(double value) {
  return setDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZoneFloorArea, value);
}

double DesignSpecificationOutdoorAir_Impl::outdoorAirFlowRate() const {
  if (auto value = getDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZone, true)) {
    return *value;
  }
  return 0.0;
}

bool DesignSpecificationOutdoorAir_Impl::setOutdoorAirFlowRate(double value) {
  return setDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZone, value);
}

double DesignSpecificationOutdoorAir_Impl::outdoorAirFlowAirChangesperHour() const {
  if (auto value = getDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowAirChangesperHour, true)) {
    return *value;
  }
  return 0.0;
}

bool DesignSpecificationOutdoorAir_Impl::setOutdoorAirFlowAirChangesperHour(double value) {
  return setDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowAirChangesperHour, value);
}

void DesignSpecificationOutdoorAir_Impl::doCanonicalize(LoadContext& context) {
  auto dsoa = getObject<openstudio::epmodel::DesignSpecificationOutdoorAir>();
  if (!getString(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirMethod, true)) {
    OS_ASSERT(setString(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirMethod, "Sum"));
    detail::addLoadInfo(context, "Set default Outdoor Air Method to 'Sum' for DesignSpecification:OutdoorAir '" + dsoa.nameString() + "'.");
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
