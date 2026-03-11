/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FOUNDATIONKIVA_HPP
#define EPMODEL_FOUNDATIONKIVA_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FoundationKiva_Impl;
}

class EPMODEL_API FoundationKiva : public ModelObject
{
 public:
  explicit FoundationKiva(const Model& model);

  virtual ~FoundationKiva() override = default;
  FoundationKiva(const FoundationKiva& other) = default;
  FoundationKiva(FoundationKiva&& other) = default;
  FoundationKiva& operator=(const FoundationKiva&) = default;
  FoundationKiva& operator=(FoundationKiva&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: Scalar APIs map directly to same-named EnergyPlus Foundation:Kiva numeric fields.
  // - Field Mapping: Material/construction references, linked surfaces, and custom block extensible groups are excluded as relationship APIs.
  // - TODO(parity): Add excluded relationship/extensible APIs after scalar saturation without changing these scalar signatures.
  boost::optional<double> initialIndoorAirTemperature();
  bool setInitialIndoorAirTemperature(double initialIndoorAirTemperature);

  double interiorHorizontalInsulationDepth() const;
  bool isInteriorHorizontalInsulationDepthDefaulted() const;
  bool setInteriorHorizontalInsulationDepth(double interiorHorizontalInsulationDepth);
  void resetInteriorHorizontalInsulationDepth();

  boost::optional<double> interiorHorizontalInsulationWidth();
  bool setInteriorHorizontalInsulationWidth(double interiorHorizontalInsulationWidth);

  boost::optional<double> interiorVerticalInsulationDepth();
  bool setInteriorVerticalInsulationDepth(double interiorVerticalInsulationDepth);

  boost::optional<double> exteriorHorizontalInsulationDepth();
  bool setExteriorHorizontalInsulationDepth(double exteriorHorizontalInsulationDepth);

  double exteriorHorizontalInsulationWidth() const;
  bool isExteriorHorizontalInsulationWidthDefaulted() const;
  bool setExteriorHorizontalInsulationWidth(double exteriorHorizontalInsulationWidth);
  void resetExteriorHorizontalInsulationWidth();

  boost::optional<double> exteriorVerticalInsulationDepth();
  bool setExteriorVerticalInsulationDepth(double exteriorVerticalInsulationDepth);

  double wallHeightAboveGrade() const;
  bool isWallHeightAboveGradeDefaulted() const;
  bool setWallHeightAboveGrade(double wallHeightAboveGrade);
  void resetWallHeightAboveGrade();

  double wallDepthBelowSlab() const;
  bool isWallDepthBelowSlabDefaulted() const;
  bool setWallDepthBelowSlab(double wallDepthBelowSlab);
  void resetWallDepthBelowSlab();

  double footingDepth() const;
  bool isFootingDepthDefaulted() const;
  bool setFootingDepth(double footingDepth);
  void resetFootingDepth();

 protected:
  using ImplType = detail::FoundationKiva_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FoundationKiva(std::shared_ptr<detail::FoundationKiva_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
