/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVECUBICLINEAR_HPP
#define EPMODEL_CURVECUBICLINEAR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveCubicLinear_Impl;
  }

  class EPMODEL_API CurveCubicLinear : public ModelObject
  {
   public:
    explicit CurveCubicLinear(const Model& model);

    virtual ~CurveCubicLinear() override = default;
    CurveCubicLinear(const CurveCubicLinear& other) = default;
    CurveCubicLinear(CurveCubicLinear&& other) = default;
    CurveCubicLinear& operator=(const CurveCubicLinear&) = default;
    CurveCubicLinear& operator=(CurveCubicLinear&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validInputUnitTypeforXValues();
    static std::vector<std::string> validInputUnitTypeforYValues();
    static std::vector<std::string> validOutputUnitTypeValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists; accessor names are IDD-derived.
    // - Field Mapping: coefficient/min/max and unit-type APIs map directly to E+ Curve:CubicLinear fields.
    // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
    double coefficient1Constant() const;
    bool setCoefficient1Constant(double coefficient1Constant);

    double coefficient2x() const;
    bool setCoefficient2x(double coefficient2x);

    double coefficient3xPOW2() const;
    bool setCoefficient3xPOW2(double coefficient3xPOW2);

    double coefficient4xPOW3() const;
    bool setCoefficient4xPOW3(double coefficient4xPOW3);

    double coefficient5y() const;
    bool setCoefficient5y(double coefficient5y);

    double coefficient6xTIMESY() const;
    bool setCoefficient6xTIMESY(double coefficient6xTIMESY);

    double minimumValueofx() const;
    bool setMinimumValueofx(double minimumValueofx);

    double maximumValueofx() const;
    bool setMaximumValueofx(double maximumValueofx);

    double minimumValueofy() const;
    bool setMinimumValueofy(double minimumValueofy);

    double maximumValueofy() const;
    bool setMaximumValueofy(double maximumValueofy);

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

    std::string outputUnitType() const;
    bool isOutputUnitTypeDefaulted() const;
    bool setOutputUnitType(const std::string& outputUnitType);
    void resetOutputUnitType();

   protected:
    using ImplType = detail::CurveCubicLinear_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveCubicLinear(std::shared_ptr<detail::CurveCubicLinear_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
