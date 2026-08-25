/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORPERFORMANCEPHOTOVOLTAICTHERMALSIMPLE_HPP
#define EPMODEL_SOLARCOLLECTORPERFORMANCEPHOTOVOLTAICTHERMALSIMPLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SolarCollectorPerformancePhotovoltaicThermalSimple_Impl;
  }

  /** \brief SolarCollectorPerformancePhotovoltaicThermalSimple.
   *
   * \par EnergyPlus object
   * \epobject{group-solar-collectors.html#solarcollectorperformancephotovoltaicthermalsimple,SolarCollectorPerformance:PhotovoltaicThermal:Simple}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SolarCollectorPerformancePhotovoltaicThermalSimple</code>. The scalar photovoltaic-thermal performance fields map directly to EnergyPlus. Model's <code>thermalConversionEfficiencySchedule()</code>, <code>setThermalConversionEfficiencySchedule()</code>, and <code>resetThermalConversionEfficiencySchedule()</code> are not available.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SolarCollectorPerformancePhotovoltaicThermalSimple : public ModelObject
  {
   public:
    explicit SolarCollectorPerformancePhotovoltaicThermalSimple(const Model& model);

    virtual ~SolarCollectorPerformancePhotovoltaicThermalSimple() override = default;
    SolarCollectorPerformancePhotovoltaicThermalSimple(const SolarCollectorPerformancePhotovoltaicThermalSimple& other) = default;
    SolarCollectorPerformancePhotovoltaicThermalSimple(SolarCollectorPerformancePhotovoltaicThermalSimple&& other) = default;
    SolarCollectorPerformancePhotovoltaicThermalSimple& operator=(const SolarCollectorPerformancePhotovoltaicThermalSimple&) = default;
    SolarCollectorPerformancePhotovoltaicThermalSimple& operator=(SolarCollectorPerformancePhotovoltaicThermalSimple&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> thermalConversionEfficiencyInputModeTypeValues();

    double fractionOfSurfaceAreaWithActiveThermalCollector() const;
    bool setFractionOfSurfaceAreaWithActiveThermalCollector(double fractionofSurfaceAreawithActiveThermalCollector);

    std::string thermalConversionEfficiencyInputModeType() const;

    boost::optional<double> thermalConversionEfficiency() const;
    bool setThermalConversionEfficiency(double valueforThermalConversionEfficiencyifFixed);
    void resetThermalConversionEfficiency();

    double frontSurfaceEmittance() const;
    bool isFrontSurfaceEmittanceDefaulted() const;
    bool setFrontSurfaceEmittance(double frontSurfaceEmittance);
    void resetFrontSurfaceEmittance();

   protected:
    using ImplType = detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SolarCollectorPerformancePhotovoltaicThermalSimple(
      std::shared_ptr<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
