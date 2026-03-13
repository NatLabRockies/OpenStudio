/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUINTLINEAR_HPP
#define EPMODEL_CURVEQUINTLINEAR_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveQuintLinear_Impl;
  }

  class EPMODEL_API CurveQuintLinear : public Curve
  {
   public:
    explicit CurveQuintLinear(const Model& model);

    virtual ~CurveQuintLinear() override = default;
    CurveQuintLinear(const CurveQuintLinear& other) = default;
    CurveQuintLinear(CurveQuintLinear&& other) = default;
    CurveQuintLinear& operator=(const CurveQuintLinear&) = default;
    CurveQuintLinear& operator=(CurveQuintLinear&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> inputUnitTypeforvValues();
    static std::vector<std::string> inputUnitTypeforwValues();
    static std::vector<std::string> inputUnitTypeforxValues();
    static std::vector<std::string> inputUnitTypeforyValues();
    static std::vector<std::string> inputUnitTypeforzValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model CurveQuintLinear scalar accessor names/signatures.
    // - Field Mapping: coefficient/min-max and input-unit APIs map directly to E+ Curve:QuintLinear fields.
    // - ForwardTranslator evidence: ForwardTranslateCurveQuintLinear.cpp writes these scalar fields directly.
    // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.

    double coefficient1Constant() const;
    bool setCoefficient1Constant(double coefficient1Constant);

    double coefficient2v() const;
    bool setCoefficient2v(double coefficient2v);

    double coefficient3w() const;
    bool setCoefficient3w(double coefficient3w);

    double coefficient4x() const;
    bool setCoefficient4x(double coefficient4x);

    double coefficient5y() const;
    bool setCoefficient5y(double coefficient5y);

    double coefficient6z() const;
    bool setCoefficient6z(double coefficient6z);

    double minimumValueofv() const;
    bool setMinimumValueofv(double minimumValueofv);

    double maximumValueofv() const;
    bool setMaximumValueofv(double maximumValueofv);

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

    std::string inputUnitTypeforv() const;
    bool isInputUnitTypeforvDefaulted() const;
    bool setInputUnitTypeforv(const std::string& inputUnitTypeforv);
    void resetInputUnitTypeforv();

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
    using ImplType = detail::CurveQuintLinear_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveQuintLinear(std::shared_ptr<detail::CurveQuintLinear_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
