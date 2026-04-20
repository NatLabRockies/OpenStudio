/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECROSSMIXING_HPP
#define EPMODEL_ZONECROSSMIXING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneCrossMixing_Impl;
  }

  class EPMODEL_API ZoneCrossMixing : public ModelObject
  {
   public:
    explicit ZoneCrossMixing(const Model& model);

    virtual ~ZoneCrossMixing() override = default;
    ZoneCrossMixing(const ZoneCrossMixing& other) = default;
    ZoneCrossMixing(ZoneCrossMixing&& other) = default;
    ZoneCrossMixing& operator=(const ZoneCrossMixing&) = default;
    ZoneCrossMixing& operator=(ZoneCrossMixing&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> designFlowRateCalculationMethodValues();

    // Schema Alignment Notes:
    // - API: IDD-derived scalar accessors directly mirror EnergyPlus ZoneCrossMixing choice and numeric fields.
    // - Field Mapping: designFlowRateCalculationMethod tracks the E+ Design Flow Rate Calculation Method choice, the numeric fields map one-to-one to the corresponding flow-rate/air-change fields, and deltaTemperature falls back to the E+ default of 0.
    // - Field Mapping: Relationship targets (zone/space names and schedule references) are excluded under this scalar-only pass.
    // - TODO(parity): Add the zone/space/schedule relationship APIs in a later relationship-focused iteration.
    std::string designFlowRateCalculationMethod() const;
    bool isDesignFlowRateCalculationMethodDefaulted() const;
    bool setDesignFlowRateCalculationMethod(const std::string& designFlowRateCalculationMethod);
    void resetDesignFlowRateCalculationMethod();

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

    double deltaTemperature() const;
    bool isDeltaTemperatureDefaulted() const;
    bool setDeltaTemperature(double deltaTemperature);
    void resetDeltaTemperature();

   protected:
    using ImplType = detail::ZoneCrossMixing_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneCrossMixing(std::shared_ptr<detail::ZoneCrossMixing_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
