/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDTEMPERATUREUNDISTURBEDFINITEDIFFERENCE_HPP
#define EPMODEL_SITEGROUNDTEMPERATUREUNDISTURBEDFINITEDIFFERENCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SiteGroundTemperatureUndisturbedFiniteDifference_Impl;
  }

  /** \brief SiteGroundTemperatureUndisturbedFiniteDifference.
   *
   * \par EnergyPlus object
   * \epobject{group-location-climate-weather-file-access.html#sitegroundtemperatureundisturbedfinitedifference,Site:GroundTemperature:Undisturbed:FiniteDifference}.
   *
   * \par OpenStudio Model API
   * There is no corresponding OpenStudio Model class. EPModel exposes the scalar soil and evapotranspiration inputs; the EnergyPlus name/reference relationship is not exposed as a typed API.
   *
   * \par Known limitations
   * The wrapper is limited to the persisted scalar soil and evapotranspiration inputs; it does not provide higher-level ground-temperature ownership or workflow helpers.
   */
  class EPMODEL_API SiteGroundTemperatureUndisturbedFiniteDifference : public ModelObject
  {
   public:
    explicit SiteGroundTemperatureUndisturbedFiniteDifference(const Model& model);

    virtual ~SiteGroundTemperatureUndisturbedFiniteDifference() override = default;
    SiteGroundTemperatureUndisturbedFiniteDifference(const SiteGroundTemperatureUndisturbedFiniteDifference& other) = default;
    SiteGroundTemperatureUndisturbedFiniteDifference(SiteGroundTemperatureUndisturbedFiniteDifference&& other) = default;
    SiteGroundTemperatureUndisturbedFiniteDifference& operator=(const SiteGroundTemperatureUndisturbedFiniteDifference&) = default;
    SiteGroundTemperatureUndisturbedFiniteDifference& operator=(SiteGroundTemperatureUndisturbedFiniteDifference&&) = default;

    static IddObjectType iddObjectType();
    double soilThermalConductivity() const;
    bool setSoilThermalConductivity(double soilThermalConductivity);

    double soilDensity() const;
    bool setSoilDensity(double soilDensity);

    double soilSpecificHeat() const;
    bool setSoilSpecificHeat(double soilSpecificHeat);

    double soilMoistureContentVolumeFraction() const;
    bool isSoilMoistureContentVolumeFractionDefaulted() const;
    bool setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction);
    void resetSoilMoistureContentVolumeFraction();

    double soilMoistureContentVolumeFractionatSaturation() const;
    bool isSoilMoistureContentVolumeFractionatSaturationDefaulted() const;
    bool setSoilMoistureContentVolumeFractionatSaturation(double soilMoistureContentVolumeFractionatSaturation);
    void resetSoilMoistureContentVolumeFractionatSaturation();

    double evapotranspirationGroundCoverParameter() const;
    bool isEvapotranspirationGroundCoverParameterDefaulted() const;
    bool setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter);
    void resetEvapotranspirationGroundCoverParameter();

   protected:
    using ImplType = detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteGroundTemperatureUndisturbedFiniteDifference(std::shared_ptr<detail::SiteGroundTemperatureUndisturbedFiniteDifference_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
