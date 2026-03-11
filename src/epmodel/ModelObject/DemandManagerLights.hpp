/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DEMANDMANAGERLIGHTS_HPP
#define EPMODEL_DEMANDMANAGERLIGHTS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class DemandManagerLights_Impl;
}

class EPMODEL_API DemandManagerLights : public ModelObject
{
 public:
  explicit DemandManagerLights(const Model& model);

  virtual ~DemandManagerLights() override = default;
  DemandManagerLights(const DemandManagerLights& other) = default;
  DemandManagerLights(DemandManagerLights&& other) = default;
  DemandManagerLights& operator=(const DemandManagerLights&) = default;
  DemandManagerLights& operator=(DemandManagerLights&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> limitControlValues();
  static std::vector<std::string> selectionControlValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Scalar APIs map directly to DemandManager:Lights scalar fields.
  // - Field Mapping: Availability Schedule Name and extensible Lights Name references remain excluded as relationship fields.
  // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
  std::string limitControl() const;
  bool setLimitControl(const std::string& limitControl);

  boost::optional<int> minimumLimitDuration() const;
  bool setMinimumLimitDuration(int minimumLimitDuration);
  void resetMinimumLimitDuration();

  boost::optional<double> maximumLimitFraction() const;
  bool setMaximumLimitFraction(double maximumLimitFraction);
  void resetMaximumLimitFraction();

  boost::optional<double> limitStepChange() const;
  bool setLimitStepChange(double limitStepChange);
  void resetLimitStepChange();

  std::string selectionControl() const;
  bool setSelectionControl(const std::string& selectionControl);

  boost::optional<int> rotationDuration() const;
  bool setRotationDuration(int rotationDuration);
  void resetRotationDuration();

 protected:
  using ImplType = detail::DemandManagerLights_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit DemandManagerLights(std::shared_ptr<detail::DemandManagerLights_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
