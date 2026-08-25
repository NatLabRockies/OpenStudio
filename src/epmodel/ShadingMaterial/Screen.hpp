/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCREEN_HPP
#define EPMODEL_SCREEN_HPP

#include "EPModelAPI.hpp"
#include "ShadingMaterial/ShadingMaterial.hpp"

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

  /** \brief Represents a window screen shading material.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#windowmaterialscreen,WindowMaterial:Screen}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::Screen</code>. Thermal, optical, spacing, opening,
   * and output-resolution methods have the same public meaning.
   *
   * \par Known limitations
   * This wrapper represents screen material properties only; placement and
   * shading-control relationships belong to other objects.
   */
  class EPMODEL_API Screen : public ShadingMaterial
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

    double thermalConductivity() const;
    bool setThermalConductivity(double value);

    double thermalConductance() const;

    double thermalResistivity() const;
    bool setThermalResistivity(double value);

    double thermalResistance() const;

    std::string reflectedBeamTransmittanceAccountingMethod() const;
    bool isReflectedBeamTransmittanceAccountingMethodDefaulted() const;
    bool setReflectedBeamTransmittanceAccountingMethod(const std::string& reflectedBeamTransmittanceAccountingMethod);
    void resetReflectedBeamTransmittanceAccountingMethod();

    double diffuseSolarReflectance() const;
    bool setDiffuseSolarReflectance(double diffuseSolarReflectance);

    double diffuseVisibleReflectance() const;
    bool setDiffuseVisibleReflectance(double diffuseVisibleReflectance);

    double thermalHemisphericalEmissivity() const;
    bool isThermalHemisphericalEmissivityDefaulted() const;
    bool setThermalHemisphericalEmissivity(double thermalHemisphericalEmissivity);
    void resetThermalHemisphericalEmissivity();

    double conductivity() const;
    bool isConductivityDefaulted() const;
    bool setConductivity(double conductivity);
    void resetConductivity();

    double screenMaterialSpacing() const;
    bool setScreenMaterialSpacing(double screenMaterialSpacing);

    double screenMaterialDiameter() const;
    bool setScreenMaterialDiameter(double screenMaterialDiameter);

    double screentoGlassDistance() const;
    bool isScreentoGlassDistanceDefaulted() const;
    bool setScreentoGlassDistance(double screentoGlassDistance);
    void resetScreentoGlassDistance();

    double topOpeningMultiplier() const;
    bool isTopOpeningMultiplierDefaulted() const;
    bool setTopOpeningMultiplier(double topOpeningMultiplier);
    void resetTopOpeningMultiplier();

    double bottomOpeningMultiplier() const;
    bool isBottomOpeningMultiplierDefaulted() const;
    bool setBottomOpeningMultiplier(double bottomOpeningMultiplier);
    void resetBottomOpeningMultiplier();

    double leftSideOpeningMultiplier() const;
    bool isLeftSideOpeningMultiplierDefaulted() const;
    bool setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier);
    void resetLeftSideOpeningMultiplier();

    double rightSideOpeningMultiplier() const;
    bool isRightSideOpeningMultiplierDefaulted() const;
    bool setRightSideOpeningMultiplier(double rightSideOpeningMultiplier);
    void resetRightSideOpeningMultiplier();

    std::string angleofResolutionforScreenTransmittanceOutputMap() const;
    bool isAngleofResolutionforScreenTransmittanceOutputMapDefaulted() const;
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
