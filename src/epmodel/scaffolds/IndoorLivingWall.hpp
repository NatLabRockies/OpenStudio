/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_INDOORLIVINGWALL_HPP
#define EPMODEL_INDOORLIVINGWALL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class IndoorLivingWall_Impl;
  }

  class EPMODEL_API IndoorLivingWall : public ModelObject
  {
   public:
    explicit IndoorLivingWall(const Model& model);

    virtual ~IndoorLivingWall() override = default;
    IndoorLivingWall(const IndoorLivingWall& other) = default;
    IndoorLivingWall(IndoorLivingWall&& other) = default;
    IndoorLivingWall& operator=(const IndoorLivingWall&) = default;
    IndoorLivingWall& operator=(IndoorLivingWall&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> evapotranspirationCalculationMethodValues();
    static std::vector<std::string> lightingMethodValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to IndoorLivingWall scalar fields.
    // - Field Mapping: Surface Name, Schedule Name, LED Intensity Schedule Name,
    //   and LED-Daylight Targeted Lighting Intensity Schedule Name are relationship
    //   object-list fields and are intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs incrementally after scalar scaffold saturation.
    std::string evapotranspirationCalculationMethod() const;
    bool setEvapotranspirationCalculationMethod(const std::string& evapotranspirationCalculationMethod);
    bool isEvapotranspirationCalculationMethodDefaulted() const;
    void resetEvapotranspirationCalculationMethod();

    boost::optional<std::string> lightingMethod() const;
    bool setLightingMethod(const std::string& lightingMethod);
    void resetLightingMethod();

    boost::optional<std::string> daylightingControlName() const;
    bool setDaylightingControlName(const std::string& daylightingControlName);
    void resetDaylightingControlName();

    boost::optional<double> totalLeafArea() const;
    bool setTotalLeafArea(double totalLeafArea);
    void resetTotalLeafArea();

    boost::optional<double> lEDNominalIntensity() const;
    bool setLEDNominalIntensity(double lEDNominalIntensity);
    void resetLEDNominalIntensity();

    boost::optional<double> lEDNominalPower() const;
    bool setLEDNominalPower(double lEDNominalPower);
    void resetLEDNominalPower();

    double radiantFractionofLEDLights() const;
    bool isRadiantFractionofLEDLightsDefaulted() const;
    bool setRadiantFractionofLEDLights(double radiantFractionofLEDLights);
    void resetRadiantFractionofLEDLights();

   protected:
    using ImplType = detail::IndoorLivingWall_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit IndoorLivingWall(std::shared_ptr<detail::IndoorLivingWall_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
