/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PEOPLE_HPP
#define EPMODEL_PEOPLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class People_Impl;
}

class EPMODEL_API People : public ModelObject
{
 public:
  explicit People(const Model& model);

  virtual ~People() override = default;
  People(const People& other) = default;
  People(People&& other) = default;
  People& operator=(const People&) = default;
  People& operator=(People&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> clothingInsulationCalculationMethodValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::People scalar API names/signatures where present.
  // - Field Mapping: clothingInsulationCalculationMethod/coldStressTemperatureThreshold/heatStressTemperatureThreshold map directly
  //   to E+ People fields with the same semantic meaning.
  // - Field Mapping: schedule and space/space-type target references are relationship fields and intentionally excluded.
  // - Field Mapping: setMultiplier/resetMultiplier are preserved compatibility methods; E+ People has no dedicated multiplier field.
  // - ForwardTranslator evidence: ForwardTranslatePeople.cpp applies model multiplier directly to translated Number of People,
  //   People per Floor Area, and Floor Area per Person scalar fields.
  // - TODO(parity): Add relationship and definition-backed APIs without changing preserved scalar signatures.
  std::string clothingInsulationCalculationMethod() const;
  bool setClothingInsulationCalculationMethod(const std::string& clothingInsulationCalculationMethod);

  double coldStressTemperatureThreshold() const;
  bool isColdStressTemperatureThresholdDefaulted() const;
  bool setColdStressTemperatureThreshold(double coldStressTemperatureThreshold);
  void resetColdStressTemperatureThreshold();

  double heatStressTemperatureThreshold() const;
  bool isHeatStressTemperatureThresholdDefaulted() const;
  bool setHeatStressTemperatureThreshold(double heatStressTemperatureThreshold);
  void resetHeatStressTemperatureThreshold();

  bool setMultiplier(double multiplier);
  void resetMultiplier();

 protected:
  using ImplType = detail::People_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit People(std::shared_ptr<detail::People_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
