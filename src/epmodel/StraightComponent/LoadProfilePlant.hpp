/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LOADPROFILEPLANT_HPP
#define EPMODEL_LOADPROFILEPLANT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class LoadProfilePlant_Impl;
}

class EPMODEL_API LoadProfilePlant : public StraightComponent
{
 public:
  explicit LoadProfilePlant(const Model& model);

  virtual ~LoadProfilePlant() override = default;
  LoadProfilePlant(const LoadProfilePlant& other) = default;
  LoadProfilePlant(LoadProfilePlant&& other) = default;
  LoadProfilePlant& operator=(const LoadProfilePlant&) = default;
  LoadProfilePlant& operator=(LoadProfilePlant&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> plantLoopFluidTypeValues();

  // Schema Alignment Notes:
  // - Status: Scalar Parity. The canonical load-profile-plant scalar surface is present, while schedule and node-link helpers remain out of scope.
  // - Canonical Counterpart: openstudio::model::LoadProfilePlant.
  // - Implemented Parity: The preserved scalar API matches the flow, fluid-type, and subcooling accessors with matching default behavior.
  // - Documented Delta: Load/flow schedule and node-link helpers remain intentionally excluded from this scalar pass.
  // - Field/Storage Mapping: These accessors map directly to EnergyPlus `LoadProfile:Plant` scalar fields used by the forward translator.
  // - Evidence: `src/model/LoadProfilePlant.hpp`, `src/model/LoadProfilePlant.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateLoadProfilePlant.cpp`.
  // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
  double peakFlowRate() const;
  bool setPeakFlowRate(double peakFlowRate);

  std::string plantLoopFluidType() const;
  bool setPlantLoopFluidType(const std::string& plantLoopFluidType);
  bool isPlantLoopFluidTypeDefaulted() const;
  void resetPlantLoopFluidType();

  double degreeofSubCooling() const;
  bool setDegreeofSubCooling(double degreeofSubCooling);
  bool isDegreeofSubCoolingDefaulted() const;
  void resetDegreeofSubCooling();

  double degreeofLoopSubCooling() const;
  bool setDegreeofLoopSubCooling(double degreeofLoopSubCooling);
  bool isDegreeofLoopSubCoolingDefaulted() const;
  void resetDegreeofLoopSubCooling();

 protected:
  using ImplType = detail::LoadProfilePlant_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit LoadProfilePlant(std::shared_ptr<detail::LoadProfilePlant_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
