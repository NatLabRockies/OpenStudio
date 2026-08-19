/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONAIRBOUNDARY_HPP
#define EPMODEL_CONSTRUCTIONAIRBOUNDARY_HPP

#include "EPModelAPI.hpp"
#include "ConstructionBase/ConstructionBase.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ConstructionAirBoundary_Impl;
  }

  /** \brief Defines an air-boundary construction and its simple-mixing inputs.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#constructionairboundary,Construction:AirBoundary}.
   *
   * \par Important behavior
   * The legacy solar/daylighting and radiant-exchange methods are retained for
   * source compatibility, but their setters return false, their value lists
   * are empty, and their getters report the fixed legacy value
   * <code>GroupedZones</code>; those concepts no longer have EnergyPlus fields.
   * The constructor initializes simple-mixing air changes per hour to 0.0.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ConstructionAirBoundary</code>. EPModel exposes
   * the same legacy methods; its retained solar/radiant value helpers return
   * empty lists. Model's <code>simpleMixingSchedule()</code> relationship and
   * its setter/resetter are not available.
   *
   * \par Known limitations
   * A simple-mixing schedule cannot be assigned through this wrapper.
   */
  class EPMODEL_API ConstructionAirBoundary : public ConstructionBase
  {
   public:
    explicit ConstructionAirBoundary(const Model& model);

    virtual ~ConstructionAirBoundary() override = default;
    ConstructionAirBoundary(const ConstructionAirBoundary& other) = default;
    ConstructionAirBoundary(ConstructionAirBoundary&& other) = default;
    ConstructionAirBoundary& operator=(const ConstructionAirBoundary&) = default;
    ConstructionAirBoundary& operator=(ConstructionAirBoundary&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> solarAndDaylightingMethodValues();
    static std::vector<std::string> radiantExchangeMethodValues();
    static std::vector<std::string> airExchangeMethodValues();

    std::string solarAndDaylightingMethod() const;
    bool isSolarAndDaylightingMethodDefaulted() const;
    bool setSolarAndDaylightingMethod(const std::string& solarAndDaylightingMethod);
    void resetSolarAndDaylightingMethod();

    std::string radiantExchangeMethod() const;
    bool isRadiantExchangeMethodDefaulted() const;
    bool setRadiantExchangeMethod(const std::string& radiantExchangeMethod);
    void resetRadiantExchangeMethod();

    std::string airExchangeMethod() const;
    bool isAirExchangeMethodDefaulted() const;
    bool setAirExchangeMethod(const std::string& airExchangeMethod);
    void resetAirExchangeMethod();

    double simpleMixingAirChangesPerHour() const;
    bool isSimpleMixingAirChangesPerHourDefaulted() const;
    bool setSimpleMixingAirChangesPerHour(double simpleMixingAirChangesPerHour);
    void resetSimpleMixingAirChangesPerHour();

   protected:
    using ImplType = detail::ConstructionAirBoundary_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ConstructionAirBoundary(std::shared_ptr<detail::ConstructionAirBoundary_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
