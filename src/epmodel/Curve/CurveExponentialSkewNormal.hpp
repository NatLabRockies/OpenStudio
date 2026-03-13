/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEEXPONENTIALSKEWNORMAL_HPP
#define EPMODEL_CURVEEXPONENTIALSKEWNORMAL_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveExponentialSkewNormal_Impl;
  }

  class EPMODEL_API CurveExponentialSkewNormal : public Curve
  {
   public:
    explicit CurveExponentialSkewNormal(const Model& model);

    virtual ~CurveExponentialSkewNormal() override = default;
    CurveExponentialSkewNormal(const CurveExponentialSkewNormal& other) = default;
    CurveExponentialSkewNormal(CurveExponentialSkewNormal&& other) = default;
    CurveExponentialSkewNormal& operator=(const CurveExponentialSkewNormal&) = default;
    CurveExponentialSkewNormal& operator=(CurveExponentialSkewNormal&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validInputUnitTypeforxValues();
    static std::vector<std::string> validOutputUnitTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model CurveExponentialSkewNormal scalar accessor names/signatures.
    // - Field Mapping: coefficient/min/max and unit-type APIs map directly to E+ Curve:ExponentialSkewNormal fields.
    // - ForwardTranslator evidence: ForwardTranslateCurveExponentialSkewNormal.cpp writes these scalar fields directly.
    // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.

    double coefficient1C1() const;
    bool setCoefficient1C1(double coefficient1C1);

    double coefficient2C2() const;
    bool setCoefficient2C2(double coefficient2C2);

    double coefficient3C3() const;
    bool setCoefficient3C3(double coefficient3C3);

    double coefficient4C4() const;
    bool setCoefficient4C4(double coefficient4C4);

    double minimumValueofx() const;
    bool setMinimumValueofx(double minimumValueofx);

    boost::optional<double> minimumCurveOutput() const;
    bool setMinimumCurveOutput(double minimumCurveOutput);
    void resetMinimumCurveOutput();

    double maximumValueofx() const;
    bool setMaximumValueofx(double maximumValueofx);

    boost::optional<double> maximumCurveOutput() const;
    bool setMaximumCurveOutput(double maximumCurveOutput);
    void resetMaximumCurveOutput();

    std::string inputUnitTypeforx() const;
    bool setInputUnitTypeforx(const std::string& inputUnitTypeforx);
    bool isInputUnitTypeforxDefaulted() const;
    void resetInputUnitTypeforx();

    std::string outputUnitType() const;
    bool setOutputUnitType(const std::string& outputUnitType);
    bool isOutputUnitTypeDefaulted() const;
    void resetOutputUnitType();

   protected:
    using ImplType = detail::CurveExponentialSkewNormal_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveExponentialSkewNormal(std::shared_ptr<detail::CurveExponentialSkewNormal_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
