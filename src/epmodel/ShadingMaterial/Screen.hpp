/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCREEN_HPP
#define EPMODEL_SCREEN_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Screen_Impl;
  }

  class EPMODEL_API Screen : public ModelObject
  {
   public:
    explicit Screen(const Model& model);

    virtual ~Screen() override = default;
    Screen(const Screen& other) = default;
    Screen(Screen&& other) = default;
    Screen& operator=(const Screen&) = default;
    Screen& operator=(Screen&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> reflectedBeamTransmittanceAccountingMethodValues();
    static std::vector<std::string> angleofResolutionforScreenTransmittanceOutputMapValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::Screen scalar accessor names/signatures (thermal metrics plus optical scalars) so the epmodel
    //         facade mirrors the existing public API.
    // - Field Mapping: Every accessor delegates to the EnergyPlus WindowMaterial:Screen fields consumed by
    //         energyplus::ForwardTranslator::translateScreen (ForwardTranslator/ForwardTranslateScreen.cpp).
    // - TODO(parity): Keep the derived thermal conductance/resistance helpers aligned with the model counterpart as the field
    //         semantics evolve.
    double thermalConductivity() const;
    double thermalConductance() const;
    double thermalResistivity() const;
    double thermalResistance() const;

    std::string reflectedBeamTransmittanceAccountingMethod() const;
    bool isReflectedBeamTransmittanceAccountingMethodDefaulted() const;

    double diffuseSolarReflectance() const;

    double diffuseVisibleReflectance() const;

    double thermalHemisphericalEmissivity() const;
    bool isThermalHemisphericalEmissivityDefaulted() const;

    double conductivity() const;
    bool isConductivityDefaulted() const;

    double screenMaterialSpacing() const;

    double screenMaterialDiameter() const;

    double screentoGlassDistance() const;
    bool isScreentoGlassDistanceDefaulted() const;

    double topOpeningMultiplier() const;
    bool isTopOpeningMultiplierDefaulted() const;

    double bottomOpeningMultiplier() const;
    bool isBottomOpeningMultiplierDefaulted() const;

    double leftSideOpeningMultiplier() const;
    bool isLeftSideOpeningMultiplierDefaulted() const;

    double rightSideOpeningMultiplier() const;
    bool isRightSideOpeningMultiplierDefaulted() const;

    std::string angleofResolutionforScreenTransmittanceOutputMap() const;
    bool isAngleofResolutionforScreenTransmittanceOutputMapDefaulted() const;

    bool setThermalConductivity(double value);
    bool setThermalResistivity(double value);
    bool setReflectedBeamTransmittanceAccountingMethod(const std::string& reflectedBeamTransmittanceAccountingMethod);
    void resetReflectedBeamTransmittanceAccountingMethod();

    bool setDiffuseSolarReflectance(double diffuseSolarReflectance);
    bool setDiffuseVisibleReflectance(double diffuseVisibleReflectance);

    bool setThermalHemisphericalEmissivity(double thermalHemisphericalEmissivity);
    void resetThermalHemisphericalEmissivity();

    bool setConductivity(double conductivity);
    void resetConductivity();

    bool setScreenMaterialSpacing(double screenMaterialSpacing);
    bool setScreenMaterialDiameter(double screenMaterialDiameter);

    bool setScreentoGlassDistance(double screentoGlassDistance);
    void resetScreentoGlassDistance();

    bool setTopOpeningMultiplier(double topOpeningMultiplier);
    void resetTopOpeningMultiplier();

    bool setBottomOpeningMultiplier(double bottomOpeningMultiplier);
    void resetBottomOpeningMultiplier();

    bool setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier);
    void resetLeftSideOpeningMultiplier();

    bool setRightSideOpeningMultiplier(double rightSideOpeningMultiplier);
    void resetRightSideOpeningMultiplier();

    bool setAngleofResolutionforScreenTransmittanceOutputMap(const std::string& angleofResolutionforScreenTransmittanceOutputMap);
    void resetAngleofResolutionforScreenTransmittanceOutputMap();

   protected:
    using ImplType = detail::Screen_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class detail::Screen_Impl;

    explicit Screen(std::shared_ptr<detail::Screen_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
