/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORPERFORMANCEPHOTOVOLTAICTHERMALBIPVT_HPP
#define EPMODEL_SOLARCOLLECTORPERFORMANCEPHOTOVOLTAICTHERMALBIPVT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl;
  }

  /** \brief SolarCollectorPerformancePhotovoltaicThermalBIPVT.
   *
   * \par EnergyPlus object
   * \epobject{group-solar-collectors.html#solarcollectorperformancephotovoltaicthermalBIPVT,SolarCollectorPerformance:PhotovoltaicThermal:BIPVT}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SolarCollectorPerformancePhotovoltaicThermalBIPVT</code>. The scalar BIPVT performance fields map directly to EnergyPlus. Model's <code>boundaryConditionsModel()</code>, <code>setBoundaryConditionsModel()</code>, <code>availabilitySchedule()</code>, and <code>setAvailabilitySchedule()</code> relationships are not available.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SolarCollectorPerformancePhotovoltaicThermalBIPVT : public ModelObject
  {
   public:
    explicit SolarCollectorPerformancePhotovoltaicThermalBIPVT(const Model& model);

    virtual ~SolarCollectorPerformancePhotovoltaicThermalBIPVT() override = default;
    SolarCollectorPerformancePhotovoltaicThermalBIPVT(const SolarCollectorPerformancePhotovoltaicThermalBIPVT& other) = default;
    SolarCollectorPerformancePhotovoltaicThermalBIPVT(SolarCollectorPerformancePhotovoltaicThermalBIPVT&& other) = default;
    SolarCollectorPerformancePhotovoltaicThermalBIPVT& operator=(const SolarCollectorPerformancePhotovoltaicThermalBIPVT&) = default;
    SolarCollectorPerformancePhotovoltaicThermalBIPVT& operator=(SolarCollectorPerformancePhotovoltaicThermalBIPVT&&) = default;

    static IddObjectType iddObjectType();
    double effectivePlenumGapThicknessBehindPVModules() const;
    bool setEffectivePlenumGapThicknessBehindPVModules(double effectivePlenumGapThicknessBehindPVModules);

    double pVCellNormalTransmittanceAbsorptanceProduct() const;
    bool setPVCellNormalTransmittanceAbsorptanceProduct(double pVCellNormalTransmittanceAbsorptanceProduct);

    double backingMaterialNormalTransmittanceAbsorptanceProduct() const;
    bool setBackingMaterialNormalTransmittanceAbsorptanceProduct(double backingMaterialNormalTransmittanceAbsorptanceProduct);

    double claddingNormalTransmittanceAbsorptanceProduct() const;
    bool setCladdingNormalTransmittanceAbsorptanceProduct(double claddingNormalTransmittanceAbsorptanceProduct);

    double fractionofCollectorGrossAreaCoveredbyPVModule() const;
    bool setFractionofCollectorGrossAreaCoveredbyPVModule(double fractionofCollectorGrossAreaCoveredbyPVModule);

    double fractionofPVCellAreatoPVModuleArea() const;
    bool setFractionofPVCellAreatoPVModuleArea(double fractionofPVCellAreatoPVModuleArea);

    double pVModuleTopThermalResistance() const;
    bool setPVModuleTopThermalResistance(double pVModuleTopThermalResistance);

    double pVModuleBottomThermalResistance() const;
    bool setPVModuleBottomThermalResistance(double pVModuleBottomThermalResistance);

    double pVModuleFrontLongwaveEmissivity() const;
    bool setPVModuleFrontLongwaveEmissivity(double pVModuleFrontLongwaveEmissivity);

    double pVModuleBackLongwaveEmissivity() const;
    bool setPVModuleBackLongwaveEmissivity(double pVModuleBackLongwaveEmissivity);

    double glassThickness() const;
    bool setGlassThickness(double glassThickness);

    double glassRefractionIndex() const;
    bool setGlassRefractionIndex(double glassRefractionIndex);

    double glassExtinctionCoefficient() const;
    bool setGlassExtinctionCoefficient(double glassExtinctionCoefficient);

   protected:
    using ImplType = detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SolarCollectorPerformancePhotovoltaicThermalBIPVT(std::shared_ptr<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
