/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUADRATICLINEAR_HPP
#define EPMODEL_CURVEQUADRATICLINEAR_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveQuadraticLinear_Impl;
  }

  class EPMODEL_API CurveQuadraticLinear : public Curve
  {
   public:
    explicit CurveQuadraticLinear(const Model& model);

    virtual ~CurveQuadraticLinear() override = default;
    CurveQuadraticLinear(const CurveQuadraticLinear& other) = default;
    CurveQuadraticLinear(CurveQuadraticLinear&& other) = default;
    CurveQuadraticLinear& operator=(const CurveQuadraticLinear&) = default;
    CurveQuadraticLinear& operator=(CurveQuadraticLinear&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validInputUnitTypeforXValues();
    static std::vector<std::string> validInputUnitTypeforYValues();
    static std::vector<std::string> validOutputUnitTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model CurveQuadraticLinear scalar accessor names/signatures.
    // - Field Mapping: coefficients/min-max/unit-type APIs map directly to E+ Curve:QuadraticLinear fields.
    // - ForwardTranslator evidence: ForwardTranslateCurveQuadraticLinear.cpp writes these scalar fields directly.
    // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.

    // Coefficient terms (these map directly to the EnergyPlus Curve:QuadraticLinear coefficients)
    double coefficient1Constant() const;
    bool setCoefficient1Constant(double coefficient1Constant);

    double coefficient2x() const;
    bool setCoefficient2x(double coefficient2x);

    double coefficient3xPOW2() const;
    bool setCoefficient3xPOW2(double coefficient3xPOW2);

    double coefficient4y() const;
    bool setCoefficient4y(double coefficient4y);

    double coefficient5xTIMESY() const;
    bool setCoefficient5xTIMESY(double coefficient5xTIMESY);

    double coefficient6xPOW2TIMESY() const;
    bool setCoefficient6xPOW2TIMESY(double coefficient6xPOW2TIMESY);

    // Domain bounds for x and y values
    double minimumValueofx() const;
    bool setMinimumValueofx(double minimumValueofx);

    double maximumValueofx() const;
    bool setMaximumValueofx(double maximumValueofx);

    double minimumValueofy() const;
    bool setMinimumValueofy(double minimumValueofy);

    double maximumValueofy() const;
    bool setMaximumValueofy(double maximumValueofy);

    // Optional curve output bounds
    boost::optional<double> minimumCurveOutput() const;
    bool setMinimumCurveOutput(double minimumCurveOutput);
    void resetMinimumCurveOutput();

    boost::optional<double> maximumCurveOutput() const;
    bool setMaximumCurveOutput(double maximumCurveOutput);
    void resetMaximumCurveOutput();

    // Unit type metadata
    std::string inputUnitTypeforX() const;
    bool isInputUnitTypeforXDefaulted() const;
    bool setInputUnitTypeforX(const std::string& inputUnitTypeforX);
    void resetInputUnitTypeforX();

    std::string inputUnitTypeforY() const;
    bool isInputUnitTypeforYDefaulted() const;
    bool setInputUnitTypeforY(const std::string& inputUnitTypeforY);
    void resetInputUnitTypeforY();

    std::string outputUnitType() const;
    bool isOutputUnitTypeDefaulted() const;
    bool setOutputUnitType(const std::string& outputUnitType);
    void resetOutputUnitType();

   protected:
    using ImplType = detail::CurveQuadraticLinear_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveQuadraticLinear(std::shared_ptr<detail::CurveQuadraticLinear_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
