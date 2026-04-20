/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PipingSystemUndergroundPipeSegment.hpp"
#include "PipingSystemUndergroundPipeSegment_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/PipingSystem_Underground_PipeSegment_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PipingSystemUndergroundPipeSegment::PipingSystemUndergroundPipeSegment(const Model& model)
    : ModelObject(PipingSystemUndergroundPipeSegment::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::PipingSystemUndergroundPipeSegment_Impl>());

    bool ok = true;
    ok = setXPosition(1.0);
    OS_ASSERT(ok);
    ok = setYPosition(1.0);
    OS_ASSERT(ok);
    ok = setFlowDirection("IncreasingZ");
    OS_ASSERT(ok);
  }

  PipingSystemUndergroundPipeSegment::PipingSystemUndergroundPipeSegment(std::shared_ptr<detail::PipingSystemUndergroundPipeSegment_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType PipingSystemUndergroundPipeSegment::iddObjectType() {
    return IddObjectType::PipingSystem_Underground_PipeSegment;
  }

  std::vector<std::string> PipingSystemUndergroundPipeSegment::flowDirectionValues() {
    return {"IncreasingZ", "DecreasingZ"};
  }

  double PipingSystemUndergroundPipeSegment::xPosition() const {
    return getImpl<detail::PipingSystemUndergroundPipeSegment_Impl>()->xPosition();
  }

  bool PipingSystemUndergroundPipeSegment::setXPosition(double xPosition) {
    return getImpl<detail::PipingSystemUndergroundPipeSegment_Impl>()->setXPosition(xPosition);
  }

  double PipingSystemUndergroundPipeSegment::yPosition() const {
    return getImpl<detail::PipingSystemUndergroundPipeSegment_Impl>()->yPosition();
  }

  bool PipingSystemUndergroundPipeSegment::setYPosition(double yPosition) {
    return getImpl<detail::PipingSystemUndergroundPipeSegment_Impl>()->setYPosition(yPosition);
  }

  std::string PipingSystemUndergroundPipeSegment::flowDirection() const {
    return getImpl<detail::PipingSystemUndergroundPipeSegment_Impl>()->flowDirection();
  }

  bool PipingSystemUndergroundPipeSegment::setFlowDirection(const std::string& flowDirection) {
    return getImpl<detail::PipingSystemUndergroundPipeSegment_Impl>()->setFlowDirection(flowDirection);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double PipingSystemUndergroundPipeSegment_Impl::xPosition() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_PipeSegmentFields::XPosition, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundPipeSegment_Impl::setXPosition(double xPosition) {
      return setDouble(openstudio::PipingSystem_Underground_PipeSegmentFields::XPosition, xPosition);
    }

    double PipingSystemUndergroundPipeSegment_Impl::yPosition() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_PipeSegmentFields::YPosition, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundPipeSegment_Impl::setYPosition(double yPosition) {
      return setDouble(openstudio::PipingSystem_Underground_PipeSegmentFields::YPosition, yPosition);
    }

    std::string PipingSystemUndergroundPipeSegment_Impl::flowDirection() const {
      const auto value = getString(openstudio::PipingSystem_Underground_PipeSegmentFields::FlowDirection, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundPipeSegment_Impl::setFlowDirection(const std::string& flowDirection) {
      return setString(openstudio::PipingSystem_Underground_PipeSegmentFields::FlowDirection, flowDirection);
    }

    std::vector<std::string> PipingSystemUndergroundPipeSegment_Impl::flowDirectionValues() const {
      return openstudio::epmodel::PipingSystemUndergroundPipeSegment::flowDirectionValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
