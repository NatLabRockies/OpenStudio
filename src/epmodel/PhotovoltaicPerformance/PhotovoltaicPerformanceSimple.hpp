/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PHOTOVOLTAICPERFORMANCESIMPLE_HPP
#define EPMODEL_PHOTOVOLTAICPERFORMANCESIMPLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PhotovoltaicPerformanceSimple_Impl;
  }

  /** \brief Represents simple photovoltaic performance parameters.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#photovoltaicperformancesimple,PhotovoltaicPerformance:Simple}
   *
   * \par Important behavior
   * Setting <code>fixedEfficiency</code> selects the <code>Fixed</code>
   * conversion mode; resetting it restores the EPModel default fixed
   * efficiency.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::PhotovoltaicPerformanceSimple</code>.
   *
   * - <b>Not yet available:</b> <code>efficiencySchedule()</code>,
   *   <code>setEfficiencySchedule(...)</code>, and
   *   <code>resetEfficiencySchedule()</code>.
   * - <b>Added:</b> <code>conversionEfficiencyInputModeValues()</code> and
   *   <code>setConversionEfficiencyInputMode(...)</code> expose and edit the
   *   EnergyPlus input-mode choice directly.
   *
   * \par Known limitations
   * A caller that needs scheduled efficiency must bind the schedule through a
   * lower-level object reference.
   */
  class EPMODEL_API PhotovoltaicPerformanceSimple : public ModelObject
  {
   public:
    explicit PhotovoltaicPerformanceSimple(const Model& model);

    virtual ~PhotovoltaicPerformanceSimple() override = default;
    PhotovoltaicPerformanceSimple(const PhotovoltaicPerformanceSimple& other) = default;
    PhotovoltaicPerformanceSimple(PhotovoltaicPerformanceSimple&& other) = default;
    PhotovoltaicPerformanceSimple& operator=(const PhotovoltaicPerformanceSimple&) = default;
    PhotovoltaicPerformanceSimple& operator=(PhotovoltaicPerformanceSimple&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> conversionEfficiencyInputModeValues();

    double fractionOfSurfaceAreaWithActiveSolarCells() const;
    bool isfractionOfSurfaceAreaWithActiveSolarCellsDefaulted() const;
    bool setFractionOfSurfaceAreaWithActiveSolarCells(double fractionOfSurfaceAreaWithActiveSolarCells);
    void resetFractionOfSurfaceAreaWithActiveSolarCells();

    std::string conversionEfficiencyInputMode() const;
    bool setConversionEfficiencyInputMode(const std::string& conversionEfficiencyInputMode);

    boost::optional<double> fixedEfficiency() const;
    bool setFixedEfficiency(double fixedEfficiency);
    void resetFixedEfficiency();

   protected:
    using ImplType = detail::PhotovoltaicPerformanceSimple_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PhotovoltaicPerformanceSimple(std::shared_ptr<detail::PhotovoltaicPerformanceSimple_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
