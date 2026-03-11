/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEMIXING_HPP
#define EPMODEL_ZONEMIXING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneMixing_Impl;
  }

  class EPMODEL_API ZoneMixing : public ModelObject
  {
   public:
    explicit ZoneMixing(const Model& model);

    virtual ~ZoneMixing() override = default;
    ZoneMixing(const ZoneMixing& other) = default;
    ZoneMixing(ZoneMixing&& other) = default;
    ZoneMixing& operator=(const ZoneMixing&) = default;
    ZoneMixing& operator=(ZoneMixing&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names/signatures for ZoneMixing flow-rate choices and delta temperature.
    // - Field Mapping: designFlowRate, flowRateperFloorArea, flowRateperPerson, airChangesperHour, and deltaTemperature map directly to the EnergyPlus ZoneMixing numeric fields while designFlowRateCalculationMethod reflects the required choice string (see ForwardTranslateZoneMixing.cpp for the upstream mapping).
    // - Field Mapping: Relationship targets (Zone/Space pointers and schedule references) are intentionally excluded from this scalar-only pass.
    // - TODO(parity): Reintroduce zone/space/schedule relationship APIs once the relationship-focused iteration begins.
    std::string designFlowRateCalculationMethod() const;

    boost::optional<double> designFlowRate() const;
    bool setDesignFlowRate(double designFlowRate);
    void resetDesignFlowRate();

    boost::optional<double> flowRateperFloorArea() const;
    bool setFlowRateperFloorArea(double flowRateperFloorArea);
    void resetFlowRateperFloorArea();

    boost::optional<double> flowRateperPerson() const;
    bool setFlowRateperPerson(double flowRateperPerson);
    void resetFlowRateperPerson();

    boost::optional<double> airChangesperHour() const;
    bool setAirChangesperHour(double airChangesperHour);
    void resetAirChangesperHour();

    boost::optional<double> deltaTemperature() const;
    bool setDeltaTemperature(double deltaTemperature);
    void resetDeltaTemperature();

   protected:
    using ImplType = detail::ZoneMixing_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneMixing(std::shared_ptr<detail::ZoneMixing_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
