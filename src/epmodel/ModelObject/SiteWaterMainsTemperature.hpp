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

  /** \brief SiteWaterMainsTemperature.
   *
   * \par EnergyPlus object
   * \epobject{group-location-climate-weather-file-access.html#sitewatermainstemperature,Site:WaterMainsTemperature}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SiteWaterMainsTemperature</code>. The calculation and temperature fields are exposed. Model's <code>temperatureSchedule()</code>, <code>setTemperatureSchedule()</code>, and <code>resetTemperatureSchedule()</code> are not available.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SiteWaterMainsTemperature : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~SiteWaterMainsTemperature() override = default;
    SiteWaterMainsTemperature(const SiteWaterMainsTemperature& other) = default;
    SiteWaterMainsTemperature(SiteWaterMainsTemperature&& other) = default;
    SiteWaterMainsTemperature& operator=(const SiteWaterMainsTemperature&) = default;
    SiteWaterMainsTemperature& operator=(SiteWaterMainsTemperature&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> calculationMethodValues();

    static std::vector<std::string> validCalculationMethodValues();
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
    explicit SiteWaterMainsTemperature(const Model& model);

    using ImplType = detail::SiteWaterMainsTemperature_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteWaterMainsTemperature(std::shared_ptr<detail::SiteWaterMainsTemperature_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
