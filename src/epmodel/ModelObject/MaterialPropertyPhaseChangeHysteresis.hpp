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
  /** \brief MaterialPropertyPhaseChangeHysteresis.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#materialpropertyphasechangehysteresis,MaterialProperty:PhaseChangeHysteresis}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::MaterialPropertyPhaseChangeHysteresis</code>. The scalar phase-change and hysteresis fields are exposed. Model's material relationship is not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
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
    double latentHeatduringtheEntirePhaseChangeProcess() const;
    bool setLatentHeatduringtheEntirePhaseChangeProcess(double latentHeatduringtheEntirePhaseChangeProcess);

    double liquidStateThermalConductivity() const;
    bool setLiquidStateThermalConductivity(double liquidStateThermalConductivity);

    double liquidStateDensity() const;
    bool setLiquidStateDensity(double liquidStateDensity);

    double liquidStateSpecificHeat() const;
    bool setLiquidStateSpecificHeat(double liquidStateSpecificHeat);

    double highTemperatureDifferenceofMeltingCurve() const;
    bool setHighTemperatureDifferenceofMeltingCurve(double highTemperatureDifferenceofMeltingCurve);

    double peakMeltingTemperature() const;
    bool setPeakMeltingTemperature(double peakMeltingTemperature);

    double lowTemperatureDifferenceofMeltingCurve() const;
    bool setLowTemperatureDifferenceofMeltingCurve(double lowTemperatureDifferenceofMeltingCurve);

    double solidStateThermalConductivity() const;
    bool setSolidStateThermalConductivity(double solidStateThermalConductivity);

    double solidStateDensity() const;
    bool setSolidStateDensity(double solidStateDensity);

    double solidStateSpecificHeat() const;
    bool setSolidStateSpecificHeat(double solidStateSpecificHeat);

    double highTemperatureDifferenceofFreezingCurve() const;
    bool setHighTemperatureDifferenceofFreezingCurve(double highTemperatureDifferenceofFreezingCurve);

    double peakFreezingTemperature() const;
    bool setPeakFreezingTemperature(double peakFreezingTemperature);

    double lowTemperatureDifferenceofFreezingCurve() const;
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
