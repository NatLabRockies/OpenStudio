/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/PipeIndoor.hpp"
#include "StraightComponent/PipeIndoor_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Pipe_Indoor_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

PipeIndoor::PipeIndoor(const Model& model) : StraightComponent(PipeIndoor::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::PipeIndoor_Impl>());

  bool ok = true;
  ok = setEnvironmentType("Zone");
  OS_ASSERT(ok);
  ok = setPipeInsideDiameter(0.05);
  OS_ASSERT(ok);
  ok = setPipeLength(100.0);
  OS_ASSERT(ok);
}

PipeIndoor::PipeIndoor(std::shared_ptr<detail::PipeIndoor_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType PipeIndoor::iddObjectType() {
  return IddObjectType::Pipe_Indoor;
}

std::vector<std::string> PipeIndoor::environmentTypeValues() {
  return {"Zone", "Schedule"};
}

std::string PipeIndoor::environmentType() const {
  return getImpl<detail::PipeIndoor_Impl>()->environmentType();
}

bool PipeIndoor::setEnvironmentType(const std::string& environmentType) {
  return getImpl<detail::PipeIndoor_Impl>()->setEnvironmentType(environmentType);
}

double PipeIndoor::pipeInsideDiameter() const {
  return getImpl<detail::PipeIndoor_Impl>()->pipeInsideDiameter();
}

bool PipeIndoor::setPipeInsideDiameter(double pipeInsideDiameter) {
  return getImpl<detail::PipeIndoor_Impl>()->setPipeInsideDiameter(pipeInsideDiameter);
}

double PipeIndoor::pipeLength() const {
  return getImpl<detail::PipeIndoor_Impl>()->pipeLength();
}

bool PipeIndoor::setPipeLength(double pipeLength) {
  return getImpl<detail::PipeIndoor_Impl>()->setPipeLength(pipeLength);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned PipeIndoor_Impl::inletPort() const {
  return openstudio::Pipe_IndoorFields::FluidInletNodeName;
}

unsigned PipeIndoor_Impl::outletPort() const {
  return openstudio::Pipe_IndoorFields::FluidOutletNodeName;
}

std::string PipeIndoor_Impl::environmentType() const {
  const auto value = getString(openstudio::Pipe_IndoorFields::EnvironmentType, true);
  OS_ASSERT(value);
  return *value;
}

bool PipeIndoor_Impl::setEnvironmentType(const std::string& environmentType) {
  return setString(openstudio::Pipe_IndoorFields::EnvironmentType, environmentType);
}

double PipeIndoor_Impl::pipeInsideDiameter() const {
  const auto value = getDouble(openstudio::Pipe_IndoorFields::PipeInsideDiameter, true);
  OS_ASSERT(value);
  return *value;
}

bool PipeIndoor_Impl::setPipeInsideDiameter(double pipeInsideDiameter) {
  return setDouble(openstudio::Pipe_IndoorFields::PipeInsideDiameter, pipeInsideDiameter);
}

double PipeIndoor_Impl::pipeLength() const {
  const auto value = getDouble(openstudio::Pipe_IndoorFields::PipeLength, true);
  OS_ASSERT(value);
  return *value;
}

bool PipeIndoor_Impl::setPipeLength(double pipeLength) {
  return setDouble(openstudio::Pipe_IndoorFields::PipeLength, pipeLength);
}

std::vector<std::string> PipeIndoor_Impl::environmentTypeValues() const {
  return openstudio::epmodel::PipeIndoor::environmentTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
