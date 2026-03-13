/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVECHILLERPARTLOADWITHLIFT_IMPL_HPP
#define EPMODEL_CURVECHILLERPARTLOADWITHLIFT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CurveChillerPartLoadWithLift_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~CurveChillerPartLoadWithLift_Impl() override = default;

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

      double coefficient6C6() const;
      bool setCoefficient6C6(double coefficient6C6);

      double coefficient7C7() const;
      bool setCoefficient7C7(double coefficient7C7);

      double coefficient8C8() const;
      bool setCoefficient8C8(double coefficient8C8);

      double coefficient9C9() const;
      bool setCoefficient9C9(double coefficient9C9);

      double coefficient10C10() const;
      bool setCoefficient10C10(double coefficient10C10);

      double coefficient11C11() const;
      bool setCoefficient11C11(double coefficient11C11);

      double coefficient12C12() const;
      bool setCoefficient12C12(double coefficient12C12);

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

      std::string outputUnitType() const;
      bool isOutputUnitTypeDefaulted() const;
      bool setOutputUnitType(const std::string& outputUnitType);
      void resetOutputUnitType();

      std::vector<std::string> validInputUnitTypeforxValues() const;
      std::vector<std::string> validInputUnitTypeforyValues() const;
      std::vector<std::string> validInputUnitTypeforzValues() const;
      std::vector<std::string> validOutputUnitTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
