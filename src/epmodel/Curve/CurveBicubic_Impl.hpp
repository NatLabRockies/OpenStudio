/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEBICUBIC_IMPL_HPP
#define EPMODEL_CURVEBICUBIC_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CurveBicubic_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~CurveBicubic_Impl() override = default;

      std::vector<std::string> validInputUnitTypeforXValues() const;
      std::vector<std::string> validInputUnitTypeforYValues() const;
      std::vector<std::string> validOutputUnitTypeValues() const;

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

      double coefficient7xPOW3() const;
      bool setCoefficient7xPOW3(double coefficient7xPOW3);

      double coefficient8yPOW3() const;
      bool setCoefficient8yPOW3(double coefficient8yPOW3);

      double coefficient9xPOW2TIMESY() const;
      bool setCoefficient9xPOW2TIMESY(double coefficient9xPOW2TIMESY);

      double coefficient10xTIMESYPOW2() const;
      bool setCoefficient10xTIMESYPOW2(double coefficient10xTIMESYPOW2);

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
