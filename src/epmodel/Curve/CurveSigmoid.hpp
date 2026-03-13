/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVESIGMOID_HPP
#define EPMODEL_CURVESIGMOID_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveSigmoid_Impl;
  }

  class EPMODEL_API CurveSigmoid : public ModelObject
  {
   public:
    explicit CurveSigmoid(const Model& model);

    virtual ~CurveSigmoid() override = default;
    CurveSigmoid(const CurveSigmoid& other) = default;
    CurveSigmoid(CurveSigmoid&& other) = default;
    CurveSigmoid& operator=(const CurveSigmoid&) = default;
    CurveSigmoid& operator=(CurveSigmoid&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validInputUnitTypeforxValues();
    static std::vector<std::string> validOutputUnitTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model CurveSigmoid scalar accessor names/signatures.
    // - Field Mapping: coefficient/min/max and unit-type APIs map directly to E+ Curve:Sigmoid fields.
    // - ForwardTranslator evidence: ForwardTranslateCurveSigmoid.cpp writes these scalar fields directly.
    // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
    double coefficient1C1() const;
    bool setCoefficient1C1(double coefficient1C1);

    double coefficient2C2() const;
    bool setCoefficient2C2(double coefficient2C2);

    double coefficient3C3() const;
    bool setCoefficient3C3(double coefficient3C3);

    double coefficient4C4() const;
    bool setCoefficient4C4(double coefficient4C4);

    double coefficient5C5() const;
    bool setCoefficient5C5(double coefficient5C5);

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
    bool isInputUnitTypeforxDefaulted() const;
    bool setInputUnitTypeforx(const std::string& inputUnitTypeforx);
    void resetInputUnitTypeforx();

    std::string outputUnitType() const;
    bool isOutputUnitTypeDefaulted() const;
    bool setOutputUnitType(const std::string& outputUnitType);
    void resetOutputUnitType();

   protected:
    using ImplType = detail::CurveSigmoid_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveSigmoid(std::shared_ptr<detail::CurveSigmoid_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
