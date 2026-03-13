/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDTEMPERATUREUNDISTURBEDXING_HPP
#define EPMODEL_SITEGROUNDTEMPERATUREUNDISTURBEDXING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SiteGroundTemperatureUndisturbedXing_Impl;
  }

  class EPMODEL_API SiteGroundTemperatureUndisturbedXing : public ModelObject
  {
   public:
    explicit SiteGroundTemperatureUndisturbedXing(const Model& model);

    virtual ~SiteGroundTemperatureUndisturbedXing() override = default;
    SiteGroundTemperatureUndisturbedXing(const SiteGroundTemperatureUndisturbedXing& other) = default;
    SiteGroundTemperatureUndisturbedXing(SiteGroundTemperatureUndisturbedXing&& other) = default;
    SiteGroundTemperatureUndisturbedXing& operator=(const SiteGroundTemperatureUndisturbedXing&) = default;
    SiteGroundTemperatureUndisturbedXing& operator=(SiteGroundTemperatureUndisturbedXing&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserved openstudio::model accessor names/signatures for counterpart parity.
    // - Field Mapping: Scalar APIs map directly to Site:GroundTemperature:Undisturbed:Xing numeric fields.
    // - Translator Evidence: ForwardTranslateSiteGroundTemperatureUndisturbedXing.cpp writes these same eight fields.
    // - Field Mapping: Name is a reference-provider field (UndisturbedGroundTemperatureModelNames) and is excluded from scalar APIs.
    // - TODO(parity): Keep relationship/link convenience APIs out of scalar scaffold scope.
    double soilThermalConductivity() const;
    bool setSoilThermalConductivity(double soilThermalConductivity);

    double soilDensity() const;
    bool setSoilDensity(double soilDensity);

    double soilSpecificHeat() const;
    bool setSoilSpecificHeat(double soilSpecificHeat);

    double averageSoilSurfaceTemperature() const;
    bool setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature);

    double soilSurfaceTemperatureAmplitude1() const;
    bool setSoilSurfaceTemperatureAmplitude1(double soilSurfaceTemperatureAmplitude1);

    double soilSurfaceTemperatureAmplitude2() const;
    bool setSoilSurfaceTemperatureAmplitude2(double soilSurfaceTemperatureAmplitude2);

    double phaseShiftofTemperatureAmplitude1() const;
    bool setPhaseShiftofTemperatureAmplitude1(double phaseShiftofTemperatureAmplitude1);

    double phaseShiftofTemperatureAmplitude2() const;
    bool setPhaseShiftofTemperatureAmplitude2(double phaseShiftofTemperatureAmplitude2);

   protected:
    using ImplType = detail::SiteGroundTemperatureUndisturbedXing_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteGroundTemperatureUndisturbedXing(std::shared_ptr<detail::SiteGroundTemperatureUndisturbedXing_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
