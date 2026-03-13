/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUADRATIC_HPP
#define EPMODEL_CURVEQUADRATIC_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveQuadratic_Impl;
  }

  class EPMODEL_API CurveQuadratic : public Curve
  {
   public:
    explicit CurveQuadratic(const Model& model);

    virtual ~CurveQuadratic() override = default;
    CurveQuadratic(const CurveQuadratic& other) = default;
    CurveQuadratic(CurveQuadratic&& other) = default;
    CurveQuadratic& operator=(const CurveQuadratic&) = default;
    CurveQuadratic& operator=(CurveQuadratic&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validInputUnitTypeforXValues();
    static std::vector<std::string> validOutputUnitTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model CurveQuadratic scalar accessor names/signatures.
    // - Field Mapping: coefficient/min/max and unit-type APIs map directly to E+ Curve:Quadratic fields.
    // - ForwardTranslator evidence: ForwardTranslateCurveQuadratic.cpp writes these scalar fields directly.
    // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.

    double coefficient1Constant() const;
    bool setCoefficient1Constant(double coefficient1Constant);

    double coefficient2x() const;
    bool setCoefficient2x(double coefficient2x);

    double coefficient3xPOW2() const;
    bool setCoefficient3xPOW2(double coefficient3xPOW2);

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
    bool setInputUnitTypeforX(const std::string& inputUnitTypeforX);
    bool isInputUnitTypeforXDefaulted() const;
    void resetInputUnitTypeforX();

    std::string outputUnitType() const;
    bool setOutputUnitType(const std::string& outputUnitType);
    bool isOutputUnitTypeDefaulted() const;
    void resetOutputUnitType();

   protected:
    using ImplType = detail::CurveQuadratic_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveQuadratic(std::shared_ptr<detail::CurveQuadratic_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
