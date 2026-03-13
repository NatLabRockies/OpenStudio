/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUADLINEAR_HPP
#define EPMODEL_CURVEQUADLINEAR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveQuadLinear_Impl;
  }

  class EPMODEL_API CurveQuadLinear : public ModelObject
  {
   public:
    explicit CurveQuadLinear(const Model& model);

    virtual ~CurveQuadLinear() override = default;
    CurveQuadLinear(const CurveQuadLinear& other) = default;
    CurveQuadLinear(CurveQuadLinear&& other) = default;
    CurveQuadLinear& operator=(const CurveQuadLinear&) = default;
    CurveQuadLinear& operator=(CurveQuadLinear&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> inputUnitTypeforwValues();
    static std::vector<std::string> inputUnitTypeforxValues();
    static std::vector<std::string> inputUnitTypeforyValues();
    static std::vector<std::string> inputUnitTypeforzValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model CurveQuadLinear scalar accessor names/signatures.
    // - Field Mapping: coefficient/min/max and input-unit APIs map directly to E+ Curve:QuadLinear fields.
    // - ForwardTranslator evidence: ForwardTranslateCurveQuadLinear.cpp writes these scalar fields directly.
    // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
    double coefficient1Constant() const;
    bool setCoefficient1Constant(double coefficient1Constant);

    double coefficient2w() const;
    bool setCoefficient2w(double coefficient2w);

    double coefficient3x() const;
    bool setCoefficient3x(double coefficient3x);

    double coefficient4y() const;
    bool setCoefficient4y(double coefficient4y);

    double coefficient5z() const;
    bool setCoefficient5z(double coefficient5z);

    double minimumValueofw() const;
    bool setMinimumValueofw(double minimumValueofw);

    double maximumValueofw() const;
    bool setMaximumValueofw(double maximumValueofw);

    double minimumValueofx() const;
    bool setMinimumValueofx(double minimumValueofx);

    double maximumValueofx() const;
    bool setMaximumValueofx(double maximumValueofx);

    double minimumValueofy() const;
    bool setMinimumValueofy(double minimumValueofy);

    double maximumValueofy() const;
    bool setMaximumValueofy(double maximumValueofy);

    double minimumValueofz() const;
    bool setMinimumValueofz(double minimumValueofz);

    double maximumValueofz() const;
    bool setMaximumValueofz(double maximumValueofz);

    boost::optional<double> minimumCurveOutput() const;
    bool setMinimumCurveOutput(double minimumCurveOutput);
    void resetMinimumCurveOutput();

    boost::optional<double> maximumCurveOutput() const;
    bool setMaximumCurveOutput(double maximumCurveOutput);
    void resetMaximumCurveOutput();

    std::string inputUnitTypeforw() const;
    bool isInputUnitTypeforwDefaulted() const;
    bool setInputUnitTypeforw(const std::string& inputUnitTypeforw);
    void resetInputUnitTypeforw();

    std::string inputUnitTypeforx() const;
    bool isInputUnitTypeforxDefaulted() const;
    bool setInputUnitTypeforx(const std::string& inputUnitTypeforx);
    void resetInputUnitTypeforx();

    std::string inputUnitTypefory() const;
    bool isInputUnitTypeforyDefaulted() const;
    bool setInputUnitTypefory(const std::string& inputUnitTypefory);
    void resetInputUnitTypefory();

    std::string inputUnitTypeforz() const;
    bool isInputUnitTypeforzDefaulted() const;
    bool setInputUnitTypeforz(const std::string& inputUnitTypeforz);
    void resetInputUnitTypeforz();

   protected:
    using ImplType = detail::CurveQuadLinear_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveQuadLinear(std::shared_ptr<detail::CurveQuadLinear_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
