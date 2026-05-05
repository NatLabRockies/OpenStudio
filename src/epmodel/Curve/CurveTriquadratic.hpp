/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVETRIQUADRATIC_HPP
#define EPMODEL_CURVETRIQUADRATIC_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveTriquadratic_Impl;
  }

  class EPMODEL_API CurveTriquadratic : public Curve
  {
   public:
    explicit CurveTriquadratic(const Model& model);

    virtual ~CurveTriquadratic() override = default;
    CurveTriquadratic(const CurveTriquadratic& other) = default;
    CurveTriquadratic(CurveTriquadratic&& other) = default;
    CurveTriquadratic& operator=(const CurveTriquadratic&) = default;
    CurveTriquadratic& operator=(CurveTriquadratic&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validInputUnitTypeforXValues();
    static std::vector<std::string> validInputUnitTypeforYValues();
    static std::vector<std::string> validInputUnitTypeforZValues();
    static std::vector<std::string> validOutputUnitTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model CurveTriquadratic scalar accessor names/signatures.
    // - Field Mapping: coefficient/min/max and unit-type APIs map directly to E+ Curve:Triquadratic fields.
    // - ForwardTranslator evidence: ForwardTranslateCurveTriquadratic.cpp writes these scalar fields directly.
    // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
    /** @name Field accessors */
    //@{

    boost::optional<double> coefficient1Constant() const;
    bool setCoefficient1Constant(double coefficient1Constant);
    void resetCoefficient1Constant();

    boost::optional<double> coefficient2xPOW2() const;
    bool setCoefficient2xPOW2(double coefficient2xPOW2);
    void resetCoefficient2xPOW2();

    boost::optional<double> coefficient3x() const;
    bool setCoefficient3x(double coefficient3x);
    void resetCoefficient3x();

    boost::optional<double> coefficient4yPOW2() const;
    bool setCoefficient4yPOW2(double coefficient4yPOW2);
    void resetCoefficient4yPOW2();

    boost::optional<double> coefficient5y() const;
    bool setCoefficient5y(double coefficient5y);
    void resetCoefficient5y();

    boost::optional<double> coefficient6zPOW2() const;
    bool setCoefficient6zPOW2(double coefficient6zPOW2);
    void resetCoefficient6zPOW2();

    boost::optional<double> coefficient7z() const;
    bool setCoefficient7z(double coefficient7z);
    void resetCoefficient7z();

    boost::optional<double> coefficient8xPOW2TIMESYPOW2() const;
    bool setCoefficient8xPOW2TIMESYPOW2(double coefficient8xPOW2TIMESYPOW2);
    void resetCoefficient8xPOW2TIMESYPOW2();

    boost::optional<double> coefficient9xTIMESY() const;
    bool setCoefficient9xTIMESY(double coefficient9xTIMESY);
    void resetCoefficient9xTIMESY();

    boost::optional<double> coefficient10xTIMESYPOW2() const;
    bool setCoefficient10xTIMESYPOW2(double coefficient10xTIMESYPOW2);
    void resetCoefficient10xTIMESYPOW2();

    boost::optional<double> coefficient11xPOW2TIMESY() const;
    bool setCoefficient11xPOW2TIMESY(double coefficient11xPOW2TIMESY);
    void resetCoefficient11xPOW2TIMESY();

    boost::optional<double> coefficient12xPOW2TIMESZPOW2() const;
    bool setCoefficient12xPOW2TIMESZPOW2(double coefficient12xPOW2TIMESZPOW2);
    void resetCoefficient12xPOW2TIMESZPOW2();

    boost::optional<double> coefficient13xTIMESZ() const;
    bool setCoefficient13xTIMESZ(double coefficient13xTIMESZ);
    void resetCoefficient13xTIMESZ();

    boost::optional<double> coefficient14xTIMESZPOW2() const;
    bool setCoefficient14xTIMESZPOW2(double coefficient14xTIMESZPOW2);
    void resetCoefficient14xTIMESZPOW2();

    boost::optional<double> coefficient15xPOW2TIMESZ() const;
    bool setCoefficient15xPOW2TIMESZ(double coefficient15xPOW2TIMESZ);
    void resetCoefficient15xPOW2TIMESZ();

    boost::optional<double> coefficient16yPOW2TIMESZPOW2() const;
    bool setCoefficient16yPOW2TIMESZPOW2(double coefficient16yPOW2TIMESZPOW2);
    void resetCoefficient16yPOW2TIMESZPOW2();

    boost::optional<double> coefficient17yTIMESZ() const;
    bool setCoefficient17yTIMESZ(double coefficient17yTIMESZ);
    void resetCoefficient17yTIMESZ();

    boost::optional<double> coefficient18yTIMESZPOW2() const;
    bool setCoefficient18yTIMESZPOW2(double coefficient18yTIMESZPOW2);
    void resetCoefficient18yTIMESZPOW2();

    boost::optional<double> coefficient19yPOW2TIMESZ() const;
    bool setCoefficient19yPOW2TIMESZ(double coefficient19yPOW2TIMESZ);
    void resetCoefficient19yPOW2TIMESZ();

    boost::optional<double> coefficient20xPOW2TIMESYPOW2TIMESZPOW2() const;
    bool setCoefficient20xPOW2TIMESYPOW2TIMESZPOW2(double coefficient20xPOW2TIMESYPOW2TIMESZPOW2);
    void resetCoefficient20xPOW2TIMESYPOW2TIMESZPOW2();

    boost::optional<double> coefficient21xPOW2TIMESYPOW2TIMESZ() const;
    bool setCoefficient21xPOW2TIMESYPOW2TIMESZ(double coefficient21xPOW2TIMESYPOW2TIMESZ);
    void resetCoefficient21xPOW2TIMESYPOW2TIMESZ();

    boost::optional<double> coefficient22xPOW2TIMESYTIMESZPOW2() const;
    bool setCoefficient22xPOW2TIMESYTIMESZPOW2(double coefficient22xPOW2TIMESYTIMESZPOW2);
    void resetCoefficient22xPOW2TIMESYTIMESZPOW2();

    boost::optional<double> coefficient23xTIMESYPOW2TIMESZPOW2() const;
    bool setCoefficient23xTIMESYPOW2TIMESZPOW2(double coefficient23xTIMESYPOW2TIMESZPOW2);
    void resetCoefficient23xTIMESYPOW2TIMESZPOW2();

    boost::optional<double> coefficient24xPOW2TIMESYTIMESZ() const;
    bool setCoefficient24xPOW2TIMESYTIMESZ(double coefficient24xPOW2TIMESYTIMESZ);
    void resetCoefficient24xPOW2TIMESYTIMESZ();

    boost::optional<double> coefficient25xTIMESYPOW2TIMESZ() const;
    bool setCoefficient25xTIMESYPOW2TIMESZ(double coefficient25xTIMESYPOW2TIMESZ);
    void resetCoefficient25xTIMESYPOW2TIMESZ();

    boost::optional<double> coefficient26xTIMESYTIMESZPOW2() const;
    bool setCoefficient26xTIMESYTIMESZPOW2(double coefficient26xTIMESYTIMESZPOW2);
    void resetCoefficient26xTIMESYTIMESZPOW2();

    boost::optional<double> coefficient27xTIMESYTIMESZ() const;
    bool setCoefficient27xTIMESYTIMESZ(double coefficient27xTIMESYTIMESZ);
    void resetCoefficient27xTIMESYTIMESZ();

    boost::optional<double> minimumValueofx() const;
    bool setMinimumValueofx(double minimumValueofx);
    void resetMinimumValueofx();

    boost::optional<double> maximumValueofx() const;
    bool setMaximumValueofx(double maximumValueofx);
    void resetMaximumValueofx();

    boost::optional<double> minimumValueofy() const;
    bool setMinimumValueofy(double minimumValueofy);
    void resetMinimumValueofy();

    boost::optional<double> maximumValueofy() const;
    bool setMaximumValueofy(double maximumValueofy);
    void resetMaximumValueofy();

    boost::optional<double> minimumValueofz() const;
    bool setMinimumValueofz(double minimumValueofz);
    void resetMinimumValueofz();

    boost::optional<double> maximumValueofz() const;
    bool setMaximumValueofz(double maximumValueofz);
    void resetMaximumValueofz();

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

    std::string inputUnitTypeforY() const;
    bool isInputUnitTypeforYDefaulted() const;
    bool setInputUnitTypeforY(const std::string& inputUnitTypeforY);
    void resetInputUnitTypeforY();

    std::string inputUnitTypeforZ() const;
    bool isInputUnitTypeforZDefaulted() const;
    bool setInputUnitTypeforZ(const std::string& inputUnitTypeforZ);
    void resetInputUnitTypeforZ();

    std::string outputUnitType() const;
    bool isOutputUnitTypeDefaulted() const;
    bool setOutputUnitType(const std::string& outputUnitType);
    void resetOutputUnitType();

    //@}

   protected:
    using ImplType = detail::CurveTriquadratic_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveTriquadratic(std::shared_ptr<detail::CurveTriquadratic_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
