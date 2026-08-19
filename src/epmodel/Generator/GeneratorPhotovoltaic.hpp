/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORPHOTOVOLTAIC_HPP
#define EPMODEL_GENERATORPHOTOVOLTAIC_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeneratorPhotovoltaic_Impl;
  }

  /** \brief Represents a photovoltaic generator that references a performance object.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#generatorphotovoltaic-000,Generator:Photovoltaic}. The generator references a
   * <code>PhotovoltaicPerformance:*</code> object through its performance
   * fields.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::GeneratorPhotovoltaic</code>.
   *
   * - <b>Not yet available:</b> The Model factories
   *   <code>simple()</code>, <code>equivalentOneDiode()</code>,
   *   <code>sandia()</code>, and <code>fromSandiaDatabase(...)</code>.
   * - <b>Not yet available:</b> The surface relationship
   *   (<code>surface()</code>, <code>setSurface(...)</code>, and
   *   <code>resetSurface()</code>), the
   *   <code>photovoltaicPerformance()</code> getter, and the rated-power and
   *   availability-schedule methods with their setters and resetters.
   * - <b>Not yet available:</b> The Model Generator metadata methods
   *   <code>generatorObjectType()</code>,
   *   <code>ratedThermaltoElectricalPowerRatio()</code>, and
   *   <code>electricLoadCenterDistribution()</code>.
   *
   * \par Known limitations
   * The referenced performance object and generator relationships must be
   * connected through companion wrappers or lower-level object references.
   */
  class EPMODEL_API GeneratorPhotovoltaic : public ModelObject
  {
   public:
    explicit GeneratorPhotovoltaic(const Model& model);

    virtual ~GeneratorPhotovoltaic() override = default;
    GeneratorPhotovoltaic(const GeneratorPhotovoltaic& other) = default;
    GeneratorPhotovoltaic(GeneratorPhotovoltaic&& other) = default;
    GeneratorPhotovoltaic& operator=(const GeneratorPhotovoltaic&) = default;
    GeneratorPhotovoltaic& operator=(GeneratorPhotovoltaic&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatTransferIntegrationModeValues();

    std::string heatTransferIntegrationMode() const;
    bool isHeatTransferIntegrationModeDefaulted() const;
    bool setHeatTransferIntegrationMode(const std::string& heatTransferIntegrationMode);
    void resetHeatTransferIntegrationMode();

    double numberOfModulesInParallel() const;
    bool isNumberOfModulesInParallelDefaulted() const;
    bool setNumberOfModulesInParallel(double numberOfModulesInParallel);
    void resetNumberOfModulesInParallel();

    double numberOfModulesInSeries() const;
    bool isNumberOfModulesInSeriesDefaulted() const;
    bool setNumberOfModulesInSeries(double numberOfModulesInSeries);
    void resetNumberOfModulesInSeries();

   protected:
    using ImplType = detail::GeneratorPhotovoltaic_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorPhotovoltaic(std::shared_ptr<detail::GeneratorPhotovoltaic_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
