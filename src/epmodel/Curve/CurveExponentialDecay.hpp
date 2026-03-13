/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEEXPONENTIALDECAY_HPP
#define EPMODEL_CURVEEXPONENTIALDECAY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveExponentialDecay_Impl;
  }

  class EPMODEL_API CurveExponentialDecay : public ModelObject
  {
   public:
    explicit CurveExponentialDecay(const Model& model);

    virtual ~CurveExponentialDecay() override = default;
    CurveExponentialDecay(const CurveExponentialDecay& other) = default;
    CurveExponentialDecay(CurveExponentialDecay&& other) = default;
    CurveExponentialDecay& operator=(const CurveExponentialDecay&) = default;
    CurveExponentialDecay& operator=(CurveExponentialDecay&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validInputUnitTypeforxValues();
    static std::vector<std::string> validOutputUnitTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model CurveExponentialDecay scalar accessor names/signatures.
    // - Field Mapping: coefficient/min/max and unit-type APIs map directly to E+ Curve:ExponentialDecay fields.
    // - ForwardTranslator evidence: ForwardTranslateCurveExponentialDecay.cpp writes these scalar fields directly.
    // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
    double coefficient1C1() const;
    bool setCoefficient1C1(double coefficient1C1);

    double coefficient2C2() const;
    bool setCoefficient2C2(double coefficient2C2);

    double coefficient3C3() const;
    bool setCoefficient3C3(double coefficient3C3);

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

    std::string inputUnitTypeforx() const;
    bool setInputUnitTypeforx(const std::string& inputUnitTypeforx);
    bool isInputUnitTypeforxDefaulted() const;
    void resetInputUnitTypeforx();

    std::string outputUnitType() const;
    bool setOutputUnitType(const std::string& outputUnitType);
    bool isOutputUnitTypeDefaulted() const;
    void resetOutputUnitType();

   protected:
    using ImplType = detail::CurveExponentialDecay_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveExponentialDecay(std::shared_ptr<detail::CurveExponentialDecay_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
