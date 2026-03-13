/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEBIQUADRATIC_HPP
#define EPMODEL_CURVEBIQUADRATIC_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveBiquadratic_Impl;
  }

  class EPMODEL_API CurveBiquadratic : public ModelObject
  {
   public:
    explicit CurveBiquadratic(const Model& model);

    virtual ~CurveBiquadratic() override = default;
    CurveBiquadratic(const CurveBiquadratic& other) = default;
    CurveBiquadratic(CurveBiquadratic&& other) = default;
    CurveBiquadratic& operator=(const CurveBiquadratic&) = default;
    CurveBiquadratic& operator=(CurveBiquadratic&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validInputUnitTypeforXValues();
    static std::vector<std::string> validInputUnitTypeforYValues();
    static std::vector<std::string> validOutputUnitTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model CurveBiquadratic scalar accessor names/signatures.
    // - Field Mapping: coefficient/min/max and unit-type APIs map directly to E+ Curve:Biquadratic fields.
    // - Field Mapping: Input/Output unit type default/reset behavior mirrors ForwardTranslator default-omission checks.
    // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.

    /** @name Coefficient Accessors */
    //@{
    double coefficient1Constant() const;
    bool setCoefficient1Constant(double coefficient1Constant);

    double coefficient2x() const;
    bool setCoefficient2x(double coefficient2x);

    double coefficient3xPOW2() const;
    bool setCoefficient3xPOW2(double coefficient3xPOW2);

    double coefficient4y() const;
    bool setCoefficient4y(double coefficient4y);

    double coefficient5yPOW2() const;
    bool setCoefficient5yPOW2(double coefficient5yPOW2);

    double coefficient6xTIMESY() const;
    bool setCoefficient6xTIMESY(double coefficient6xTIMESY);
    //@}

    /** @name Domain Limits */
    //@{
    double minimumValueofx() const;
    bool setMinimumValueofx(double minimumValueofx);

    double maximumValueofx() const;
    bool setMaximumValueofx(double maximumValueofx);

    double minimumValueofy() const;
    bool setMinimumValueofy(double minimumValueofy);

    double maximumValueofy() const;
    bool setMaximumValueofy(double maximumValueofy);
    //@}

    /** @name Curve Output Range */
    //@{
    boost::optional<double> minimumCurveOutput() const;
    bool setMinimumCurveOutput(double minimumCurveOutput);
    void resetMinimumCurveOutput();

    boost::optional<double> maximumCurveOutput() const;
    bool setMaximumCurveOutput(double maximumCurveOutput);
    void resetMaximumCurveOutput();
    //@}

    /** @name Input Unit Types */
    //@{
    std::string inputUnitTypeforX() const;
    bool isInputUnitTypeforXDefaulted() const;
    bool setInputUnitTypeforX(const std::string& inputUnitTypeforX);
    void resetInputUnitTypeforX();

    std::string inputUnitTypeforY() const;
    bool isInputUnitTypeforYDefaulted() const;
    bool setInputUnitTypeforY(const std::string& inputUnitTypeforY);
    void resetInputUnitTypeforY();
    //@}

    /** @name Output Unit Type */
    //@{
    std::string outputUnitType() const;
    bool isOutputUnitTypeDefaulted() const;
    bool setOutputUnitType(const std::string& outputUnitType);
    void resetOutputUnitType();
    //@}

   protected:
    using ImplType = detail::CurveBiquadratic_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveBiquadratic(std::shared_ptr<detail::CurveBiquadratic_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
