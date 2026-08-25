/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYMOISTUREPENETRATIONDEPTHSETTINGS_HPP
#define EPMODEL_MATERIALPROPERTYMOISTUREPENETRATIONDEPTHSETTINGS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class MaterialPropertyMoisturePenetrationDepthSettings_Impl;
  }

  /** MaterialPropertyMoisturePenetrationDepthSettings is a ModelObject that wraps the EnergyPlus IDD object
 * 'MaterialProperty:MoisturePenetrationDepth:Settings'. */
  /** \brief MaterialPropertyMoisturePenetrationDepthSettings.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#materialpropertymoisturepenetrationdepthsettings,MaterialProperty:MoisturePenetrationDepth:Settings}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::MaterialPropertyMoisturePenetrationDepthSettings</code>. The scalar moisture coefficients and penetration-depth autocalculate tokens are exposed. Model's material relationship is not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API MaterialPropertyMoisturePenetrationDepthSettings : public ModelObject
  {
   public:
    explicit MaterialPropertyMoisturePenetrationDepthSettings(const Model& model);

    virtual ~MaterialPropertyMoisturePenetrationDepthSettings() override = default;
    MaterialPropertyMoisturePenetrationDepthSettings(const MaterialPropertyMoisturePenetrationDepthSettings& other) = default;
    MaterialPropertyMoisturePenetrationDepthSettings(MaterialPropertyMoisturePenetrationDepthSettings&& other) = default;
    MaterialPropertyMoisturePenetrationDepthSettings& operator=(const MaterialPropertyMoisturePenetrationDepthSettings&) = default;
    MaterialPropertyMoisturePenetrationDepthSettings& operator=(MaterialPropertyMoisturePenetrationDepthSettings&&) = default;

    static IddObjectType iddObjectType();
    double waterVaporDiffusionResistanceFactor() const;
    bool setWaterVaporDiffusionResistanceFactor(double waterVaporDiffusionResistanceFactor);

    double moistureEquationCoefficientA() const;
    bool setMoistureEquationCoefficientA(double moistureEquationCoefficientA);

    double moistureEquationCoefficientB() const;
    bool setMoistureEquationCoefficientB(double moistureEquationCoefficientB);

    double moistureEquationCoefficientC() const;
    bool setMoistureEquationCoefficientC(double moistureEquationCoefficientC);

    double moistureEquationCoefficientD() const;
    bool setMoistureEquationCoefficientD(double moistureEquationCoefficientD);

    std::vector<double> moistureEquationCoefficients() const;
    bool setMoistureEquationCoefficients(double moistureEquationCoefficientA, double moistureEquationCoefficientB,
                                         double moistureEquationCoefficientC, double moistureEquationCoefficientD);

    boost::optional<double> surfaceLayerPenetrationDepth();
    bool isSurfaceLayerPenetrationDepthAutocalculated();
    bool setSurfaceLayerPenetrationDepth(double surfaceLayerPenetrationDepth);
    void autocalculateSurfaceLayerPenetrationDepth();

    boost::optional<double> deepLayerPenetrationDepth();
    bool isDeepLayerPenetrationDepthAutocalculated();
    bool setDeepLayerPenetrationDepth(double deepLayerPenetrationDepth);
    void autocalculateDeepLayerPenetrationDepth();

    double coatingLayerThickness() const;
    bool setCoatingLayerThickness(double coatingLayerThickness);

    double coatingLayerWaterVaporDiffusionResistanceFactor() const;
    bool setCoatingLayerWaterVaporDiffusionResistanceFactor(double coatingLayerWaterVaporDiffusionResistanceFactor);

   protected:
    using ImplType = detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit MaterialPropertyMoisturePenetrationDepthSettings(std::shared_ptr<detail::MaterialPropertyMoisturePenetrationDepthSettings_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
