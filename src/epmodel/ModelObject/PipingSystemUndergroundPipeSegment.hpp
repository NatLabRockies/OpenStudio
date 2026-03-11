/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPINGSYSTEMUNDERGROUNDPIPESEGMENT_HPP
#define EPMODEL_PIPINGSYSTEMUNDERGROUNDPIPESEGMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class PipingSystemUndergroundPipeSegment_Impl;
}

class EPMODEL_API PipingSystemUndergroundPipeSegment : public ModelObject
{
 public:
  explicit PipingSystemUndergroundPipeSegment(const Model& model);

  virtual ~PipingSystemUndergroundPipeSegment() override = default;
  PipingSystemUndergroundPipeSegment(const PipingSystemUndergroundPipeSegment& other) = default;
  PipingSystemUndergroundPipeSegment(PipingSystemUndergroundPipeSegment&& other) = default;
  PipingSystemUndergroundPipeSegment& operator=(const PipingSystemUndergroundPipeSegment&) = default;
  PipingSystemUndergroundPipeSegment& operator=(PipingSystemUndergroundPipeSegment&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> flowDirectionValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: xPosition, yPosition, and flowDirection map directly to
  //   PipingSystem:Underground:PipeSegment scalar fields.
  // - Field Mapping: Name remains available via base ModelObject API.
  // - TODO(parity): Add typed relationship APIs after scalar scaffold saturation.
  double xPosition() const;
  double yPosition() const;
  std::string flowDirection() const;

  bool setXPosition(double xPosition);
  bool setYPosition(double yPosition);
  bool setFlowDirection(const std::string& flowDirection);

 protected:
  using ImplType = detail::PipingSystemUndergroundPipeSegment_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit PipingSystemUndergroundPipeSegment(std::shared_ptr<detail::PipingSystemUndergroundPipeSegment_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
