/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LIGHTS_HPP
#define EPMODEL_LIGHTS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Lights_Impl;
  }

  class EPMODEL_API Lights : public ModelObject
  {
   public:
    explicit Lights(const Model& model);

    virtual ~Lights() override = default;
    Lights(const Lights& other) = default;
    Lights(Lights&& other) = default;
    Lights& operator=(const Lights&) = default;
    Lights& operator=(Lights&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> designLevelCalculationMethodValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::Lights scalar API names/signatures where present.
    // - Field Mapping: lightingLevel/powerPerFloorArea/powerPerPerson map to E+ fields Lighting Level/Watts per Floor Area/Watts per Person.
    // - Field Mapping: schedule and zone/space target references are relationship fields and intentionally excluded.
    // - Field Mapping: setMultiplier/resetMultiplier are preserved compatibility methods; no dedicated E+ multiplier field exists.
    // - ForwardTranslator evidence: ForwardTranslateLights.cpp applies model multiplier directly to translated design-level scalar fields in Lights.
    // - TODO(parity): Add relationship APIs and definition-backed behavior without changing scalar signatures.
    std::string designLevelCalculationMethod() const;
    bool isDesignLevelCalculationMethodDefaulted() const;
    bool setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod);
    void resetDesignLevelCalculationMethod();

    boost::optional<double> lightingLevel() const;
    bool setLightingLevel(double lightingLevel);
    void resetLightingLevel();

    boost::optional<double> powerPerFloorArea() const;
    bool setPowerPerFloorArea(double powerPerFloorArea);
    void resetPowerPerFloorArea();

    boost::optional<double> powerPerPerson() const;
    bool setPowerPerPerson(double powerPerPerson);
    void resetPowerPerPerson();

    double returnAirFraction() const;
    bool isReturnAirFractionDefaulted() const;
    bool setReturnAirFraction(double returnAirFraction);
    void resetReturnAirFraction();

    double fractionRadiant() const;
    bool isFractionRadiantDefaulted() const;
    bool setFractionRadiant(double fractionRadiant);
    void resetFractionRadiant();

    double fractionVisible() const;
    bool isFractionVisibleDefaulted() const;
    bool setFractionVisible(double fractionVisible);
    void resetFractionVisible();

    double fractionReplaceable() const;
    bool isFractionReplaceableDefaulted() const;
    bool setFractionReplaceable(double fractionReplaceable);
    void resetFractionReplaceable();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    bool returnAirFractionCalculatedfromPlenumTemperature() const;
    bool isReturnAirFractionCalculatedfromPlenumTemperatureDefaulted() const;
    bool setReturnAirFractionCalculatedfromPlenumTemperature(bool returnAirFractionCalculatedfromPlenumTemperature);
    void resetReturnAirFractionCalculatedfromPlenumTemperature();

    double returnAirFractionFunctionofPlenumTemperatureCoefficient1() const;
    bool isReturnAirFractionFunctionofPlenumTemperatureCoefficient1Defaulted() const;
    bool setReturnAirFractionFunctionofPlenumTemperatureCoefficient1(double returnAirFractionFunctionofPlenumTemperatureCoefficient1);
    void resetReturnAirFractionFunctionofPlenumTemperatureCoefficient1();

    double returnAirFractionFunctionofPlenumTemperatureCoefficient2() const;
    bool isReturnAirFractionFunctionofPlenumTemperatureCoefficient2Defaulted() const;
    bool setReturnAirFractionFunctionofPlenumTemperatureCoefficient2(double returnAirFractionFunctionofPlenumTemperatureCoefficient2);
    void resetReturnAirFractionFunctionofPlenumTemperatureCoefficient2();

    bool setMultiplier(double multiplier);
    void resetMultiplier();

   protected:
    using ImplType = detail::Lights_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Lights(std::shared_ptr<detail::Lights_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
