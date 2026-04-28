/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DEMANDMANAGERTHERMOSTATS_HPP
#define EPMODEL_DEMANDMANAGERTHERMOSTATS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class DemandManagerThermostats_Impl;
}

class EPMODEL_API DemandManagerThermostats : public ModelObject
{
 public:
  explicit DemandManagerThermostats(const Model& model);

  virtual ~DemandManagerThermostats() override = default;
  DemandManagerThermostats(const DemandManagerThermostats& other) = default;
  DemandManagerThermostats(DemandManagerThermostats&& other) = default;
  DemandManagerThermostats& operator=(const DemandManagerThermostats&) = default;
  DemandManagerThermostats& operator=(DemandManagerThermostats&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> resetControlValues();
  static std::vector<std::string> selectionControlValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Scalar APIs map directly to DemandManager:Thermostats scalar fields.
  // - Field Mapping: Availability Schedule Name and extensible Thermostat Name references remain excluded as relationship fields.
  // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
  std::string resetControl() const;
  bool setResetControl(const std::string& resetControl);

  boost::optional<int> minimumResetDuration() const;
  bool setMinimumResetDuration(int minimumResetDuration);
  void resetMinimumResetDuration();

  double maximumHeatingSetpointReset() const;
  bool setMaximumHeatingSetpointReset(double maximumHeatingSetpointReset);

  double maximumCoolingSetpointReset() const;
  bool setMaximumCoolingSetpointReset(double maximumCoolingSetpointReset);

  boost::optional<double> resetStepChange() const;
  bool setResetStepChange(double resetStepChange);
  void resetResetStepChange();

  std::string selectionControl() const;
  bool setSelectionControl(const std::string& selectionControl);

  boost::optional<int> rotationDuration() const;
  bool setRotationDuration(int rotationDuration);
  void resetRotationDuration();

 protected:
  using ImplType = detail::DemandManagerThermostats_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit DemandManagerThermostats(std::shared_ptr<detail::DemandManagerThermostats_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
