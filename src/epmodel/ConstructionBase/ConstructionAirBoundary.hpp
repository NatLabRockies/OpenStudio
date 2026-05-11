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

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ConstructionAirBoundary scalar accessor names/signatures, including legacy
    //   solar/radiant methods retained for compatibility.
    // - Field Mapping: airExchangeMethod and simpleMixingAirChangesPerHour map directly to E+
    //   Construction:AirBoundary fields Air Exchange Method and Simple Mixing Air Changes per Hour.
    // - Field Mapping: Legacy solar/radiant methods no longer map to current E+ fields and intentionally retain
    //   model-side compatibility behavior.
    // - ForwardTranslator evidence: ForwardTranslateConstructionAirBoundary.cpp writes only airExchangeMethod,
    //   simpleMixingAirChangesPerHour, and optional SimpleMixingScheduleName.
    // - Field Mapping: simpleMixingSchedule is an object-link field and is intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship API for simpleMixingSchedule later without changing preserved scalar signatures.
    // - Ruby parity: required/default-backed scalar getters remain strict (non-optional) with impl-level presence asserts.
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
