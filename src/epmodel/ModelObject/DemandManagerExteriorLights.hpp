/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DEMANDMANAGEREXTERIORLIGHTS_HPP
#define EPMODEL_DEMANDMANAGEREXTERIORLIGHTS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class DemandManagerExteriorLights_Impl;
}

class EPMODEL_API DemandManagerExteriorLights : public ModelObject
{
 public:
  explicit DemandManagerExteriorLights(const Model& model);

  virtual ~DemandManagerExteriorLights() override = default;
  DemandManagerExteriorLights(const DemandManagerExteriorLights& other) = default;
  DemandManagerExteriorLights(DemandManagerExteriorLights&& other) = default;
  DemandManagerExteriorLights& operator=(const DemandManagerExteriorLights&) = default;
  DemandManagerExteriorLights& operator=(DemandManagerExteriorLights&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> limitControlValues();
  static std::vector<std::string> selectionControlValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Scalar APIs map directly to DemandManager:ExteriorLights scalar fields.
  // - Field Mapping: Availability Schedule Name and extensible Exterior Lights Name references remain excluded as relationship fields.
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
  using ImplType = detail::DemandManagerExteriorLights_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit DemandManagerExteriorLights(std::shared_ptr<detail::DemandManagerExteriorLights_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
