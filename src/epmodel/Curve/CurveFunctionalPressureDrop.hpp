/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEFUNCTIONALPRESSUREDROP_HPP
#define EPMODEL_CURVEFUNCTIONALPRESSUREDROP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveFunctionalPressureDrop_Impl;
  }

  class EPMODEL_API CurveFunctionalPressureDrop : public ModelObject
  {
   public:
    explicit CurveFunctionalPressureDrop(const Model& model);

    virtual ~CurveFunctionalPressureDrop() override = default;
    CurveFunctionalPressureDrop(const CurveFunctionalPressureDrop& other) = default;
    CurveFunctionalPressureDrop(CurveFunctionalPressureDrop&& other) = default;
    CurveFunctionalPressureDrop& operator=(const CurveFunctionalPressureDrop&) = default;
    CurveFunctionalPressureDrop& operator=(CurveFunctionalPressureDrop&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model CurveFunctionalPressureDrop scalar accessor names/signatures.
    // - Field Mapping: diameter/minorLossCoefficient/length/roughness/fixedFrictionFactor map directly to
    //   E+ Curve:Functional:PressureDrop fields.
    // - ForwardTranslator evidence: ForwardTranslateCurveFunctionalPressureDrop.cpp writes these scalar fields directly.
    // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
    double diameter() const;
    bool setDiameter(double diameter);

    boost::optional<double> minorLossCoefficient() const;
    bool setMinorLossCoefficient(double minorLossCoefficient);
    void resetMinorLossCoefficient();

    boost::optional<double> length() const;
    bool setLength(double length);
    void resetLength();

    boost::optional<double> roughness() const;
    bool setRoughness(double roughness);
    void resetRoughness();

    boost::optional<double> fixedFrictionFactor() const;
    bool setFixedFrictionFactor(double fixedFrictionFactor);
    void resetFixedFrictionFactor();

   protected:
    using ImplType = detail::CurveFunctionalPressureDrop_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveFunctionalPressureDrop(std::shared_ptr<detail::CurveFunctionalPressureDrop_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
