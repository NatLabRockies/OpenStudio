/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEWATERMAINSTEMPERATURE_HPP
#define EPMODEL_SITEWATERMAINSTEMPERATURE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SiteWaterMainsTemperature_Impl;
  }

  class EPMODEL_API SiteWaterMainsTemperature : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    explicit SiteWaterMainsTemperature(const Model& model);

    virtual ~SiteWaterMainsTemperature() override = default;
    SiteWaterMainsTemperature(const SiteWaterMainsTemperature& other) = default;
    SiteWaterMainsTemperature(SiteWaterMainsTemperature&& other) = default;
    SiteWaterMainsTemperature& operator=(const SiteWaterMainsTemperature&) = default;
    SiteWaterMainsTemperature& operator=(SiteWaterMainsTemperature&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> calculationMethodValues();

    static std::vector<std::string> validCalculationMethodValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model SiteWaterMainsTemperature scalar accessor names/signatures.
    // - Field Mapping: calculationMethod, annualAverageOutdoorAirTemperature,
    //   maximumDifferenceInMonthlyAverageOutdoorAirTemperatures, temperatureMultiplier, and temperatureOffset map directly
    //   to EnergyPlus Site:WaterMainsTemperature scalar fields.
    // - Field Mapping: temperatureSchedule is intentionally excluded in this scalar-only pass because it is an object-list relationship field.
    // - TODO(parity): Add relationship helpers in a dedicated non-scalar parity pass.
    std::string calculationMethod() const;
    bool setCalculationMethod(const std::string& calculationMethod);

    boost::optional<double> annualAverageOutdoorAirTemperature() const;
    bool setAnnualAverageOutdoorAirTemperature(double annualAverageOutdoorAirTemperature);
    void resetAnnualAverageOutdoorAirTemperature();

    boost::optional<double> maximumDifferenceInMonthlyAverageOutdoorAirTemperatures() const;
    bool setMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures(double maximumDifferenceInMonthlyAverageOutdoorAirTemperatures);
    void resetMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures();

    double temperatureMultiplier() const;
    bool setTemperatureMultiplier(double temperatureMultiplier);

    double temperatureOffset() const;
    bool setTemperatureOffset(double temperatureOffset);

   protected:
    using ImplType = detail::SiteWaterMainsTemperature_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteWaterMainsTemperature(std::shared_ptr<detail::SiteWaterMainsTemperature_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
