/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYPHASECHANGEHYSTERESIS_HPP
#define EPMODEL_MATERIALPROPERTYPHASECHANGEHYSTERESIS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class MaterialPropertyPhaseChangeHysteresis_Impl;
}

/** MaterialPropertyPhaseChangeHysteresis is a ModelObject that wraps the EnergyPlus IDD object
 * 'MaterialProperty:PhaseChangeHysteresis'. */
class EPMODEL_API MaterialPropertyPhaseChangeHysteresis : public ModelObject
{
 public:
  explicit MaterialPropertyPhaseChangeHysteresis(const Model& model);

  virtual ~MaterialPropertyPhaseChangeHysteresis() override = default;
  MaterialPropertyPhaseChangeHysteresis(const MaterialPropertyPhaseChangeHysteresis& other) = default;
  MaterialPropertyPhaseChangeHysteresis(MaterialPropertyPhaseChangeHysteresis&& other) = default;
  MaterialPropertyPhaseChangeHysteresis& operator=(const MaterialPropertyPhaseChangeHysteresis&) = default;
  MaterialPropertyPhaseChangeHysteresis& operator=(MaterialPropertyPhaseChangeHysteresis&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::MaterialPropertyPhaseChangeHysteresis scalar accessor names/signatures.
  // - Field Mapping: all scalar APIs map 1:1 to E+ MaterialProperty:PhaseChangeHysteresis numeric fields.
  // - ForwardTranslator evidence: ForwardTranslateMaterialPropertyPhaseChangeHysteresis.cpp writes these exact APIs
  //   to matching MaterialProperty:PhaseChangeHysteresis fields.
  // - Exclusions: material/materialName relationship field (Name in E+) is intentionally excluded in this scalar-only pass.
  // - TODO(parity): Add material relationship APIs in a dedicated non-scalar parity pass.
  double latentHeatduringtheEntirePhaseChangeProcess() const;
  double liquidStateThermalConductivity() const;
  double liquidStateDensity() const;
  double liquidStateSpecificHeat() const;
  double highTemperatureDifferenceofMeltingCurve() const;
  double peakMeltingTemperature() const;
  double lowTemperatureDifferenceofMeltingCurve() const;
  double solidStateThermalConductivity() const;
  double solidStateDensity() const;
  double solidStateSpecificHeat() const;
  double highTemperatureDifferenceofFreezingCurve() const;
  double peakFreezingTemperature() const;
  double lowTemperatureDifferenceofFreezingCurve() const;

  bool setLatentHeatduringtheEntirePhaseChangeProcess(double latentHeatduringtheEntirePhaseChangeProcess);
  bool setLiquidStateThermalConductivity(double liquidStateThermalConductivity);
  bool setLiquidStateDensity(double liquidStateDensity);
  bool setLiquidStateSpecificHeat(double liquidStateSpecificHeat);
  bool setHighTemperatureDifferenceofMeltingCurve(double highTemperatureDifferenceofMeltingCurve);
  bool setPeakMeltingTemperature(double peakMeltingTemperature);
  bool setLowTemperatureDifferenceofMeltingCurve(double lowTemperatureDifferenceofMeltingCurve);
  bool setSolidStateThermalConductivity(double solidStateThermalConductivity);
  bool setSolidStateDensity(double solidStateDensity);
  bool setSolidStateSpecificHeat(double solidStateSpecificHeat);
  bool setHighTemperatureDifferenceofFreezingCurve(double highTemperatureDifferenceofFreezingCurve);
  bool setPeakFreezingTemperature(double peakFreezingTemperature);
  bool setLowTemperatureDifferenceofFreezingCurve(double lowTemperatureDifferenceofFreezingCurve);

 protected:
  using ImplType = detail::MaterialPropertyPhaseChangeHysteresis_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit MaterialPropertyPhaseChangeHysteresis(std::shared_ptr<detail::MaterialPropertyPhaseChangeHysteresis_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
