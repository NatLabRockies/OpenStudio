/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PERFORMANCEPRECISIONTRADEOFFS_HPP
#define EPMODEL_PERFORMANCEPRECISIONTRADEOFFS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PerformancePrecisionTradeoffs_Impl;
  }

  /** \brief PerformancePrecisionTradeoffs.
   *
   * \par EnergyPlus object
   * \epobject{group-simulation-parameters.html#performanceprecisiontradeoffs,PerformancePrecisionTradeoffs}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::PerformancePrecisionTradeoffs</code>. The exposed performance and precision settings map directly to EnergyPlus.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API PerformancePrecisionTradeoffs : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~PerformancePrecisionTradeoffs() override = default;
    PerformancePrecisionTradeoffs(const PerformancePrecisionTradeoffs& other) = default;
    PerformancePrecisionTradeoffs(PerformancePrecisionTradeoffs&& other) = default;
    PerformancePrecisionTradeoffs& operator=(const PerformancePrecisionTradeoffs&) = default;
    PerformancePrecisionTradeoffs& operator=(PerformancePrecisionTradeoffs&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> zoneRadiantExchangeAlgorithmValues();
    static std::vector<std::string> validZoneRadiantExchangeAlgorithmValues();

    static std::vector<std::string> overrideModeValues();
    static std::vector<std::string> validOverrideModeValues();
    bool useCoilDirectSolutions() const;
    bool isUseCoilDirectSolutionsDefaulted() const;
    bool setUseCoilDirectSolutions(bool useCoilDirectSolutions);
    void resetUseCoilDirectSolutions();

    std::string zoneRadiantExchangeAlgorithm() const;
    bool isZoneRadiantExchangeAlgorithmDefaulted() const;
    bool setZoneRadiantExchangeAlgorithm(const std::string& zoneRadiantExchangeAlgorithm);
    void resetZoneRadiantExchangeAlgorithm();

    std::string overrideMode() const;
    bool isOverrideModeDefaulted() const;
    bool setOverrideMode(const std::string& overrideMode);
    void resetOverrideMode();

    double maxZoneTempDiff() const;
    bool isMaxZoneTempDiffDefaulted() const;
    bool setMaxZoneTempDiff(double maxZoneTempDiff);
    void resetMaxZoneTempDiff();

    double maxAllowedDelTemp() const;
    bool isMaxAllowedDelTempDefaulted() const;
    bool setMaxAllowedDelTemp(double maxAllowedDelTemp);
    void resetMaxAllowedDelTemp();

    bool useRepresentativeSurfacesforCalculations() const;
    bool isUseRepresentativeSurfacesforCalculationsDefaulted() const;
    bool setUseRepresentativeSurfacesforCalculations(bool useRepresentativeSurfacesforCalculations);
    void resetUseRepresentativeSurfacesforCalculations();

   protected:
    explicit PerformancePrecisionTradeoffs(const Model& model);

    using ImplType = detail::PerformancePrecisionTradeoffs_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PerformancePrecisionTradeoffs(std::shared_ptr<detail::PerformancePrecisionTradeoffs_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
