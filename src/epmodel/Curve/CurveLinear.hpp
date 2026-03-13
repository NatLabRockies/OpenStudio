/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVELINEAR_HPP
#define EPMODEL_CURVELINEAR_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveLinear_Impl;
  }

  class EPMODEL_API CurveLinear : public Curve
  {
   public:
    explicit CurveLinear(const Model& model);

    virtual ~CurveLinear() override = default;
    CurveLinear(const CurveLinear& other) = default;
    CurveLinear(CurveLinear&& other) = default;
    CurveLinear& operator=(const CurveLinear&) = default;
    CurveLinear& operator=(CurveLinear&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validInputUnitTypeforXValues();
    static std::vector<std::string> validOutputUnitTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model CurveLinear scalar accessor names/signatures.
    // - Field Mapping: coefficient/min/max and unit-type APIs map directly to E+ Curve:Linear fields.
    // - ForwardTranslator evidence: ForwardTranslateCurveLinear.cpp writes these scalar fields directly.
    // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
    double coefficient1Constant() const;
    bool setCoefficient1Constant(double coefficient1Constant);

    double coefficient2x() const;
    bool setCoefficient2x(double coefficient2x);

    double minimumValueofx() const;
    bool setMinimumValueofx(double minimumValueofx);

    double maximumValueofx() const;
    bool setMaximumValueofx(double maximumValueofx);

    boost::optional<double> minimumCurveOutput() const;
    bool setMinimumCurveOutput(double minimumCurveOutput);
    void resetMinimumCurveOutput();

    boost::optional<double> maximumCurveOutput() const;
    bool setMaximumCurveOutput(double maximumCurveOutput);
    void resetMaximumCurveOutput();

    std::string inputUnitTypeforX() const;
    bool isInputUnitTypeforXDefaulted() const;
    bool setInputUnitTypeforX(const std::string& inputUnitTypeforX);
    void resetInputUnitTypeforX();

    std::string outputUnitType() const;
    bool isOutputUnitTypeDefaulted() const;
    bool setOutputUnitType(const std::string& outputUnitType);
    void resetOutputUnitType();

   protected:
    using ImplType = detail::CurveLinear_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveLinear(std::shared_ptr<detail::CurveLinear_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
