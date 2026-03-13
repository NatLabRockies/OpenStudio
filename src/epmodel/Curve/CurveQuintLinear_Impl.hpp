/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUINTLINEAR_IMPL_HPP
#define EPMODEL_CURVEQUINTLINEAR_IMPL_HPP

#include "Curve/Curve_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CurveQuintLinear_Impl : public Curve_Impl
    {
     public:
      using Curve_Impl::Curve_Impl;
      virtual ~CurveQuintLinear_Impl() override = default;

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

      std::vector<std::string> inputUnitTypeforvValues() const;
      std::vector<std::string> inputUnitTypeforwValues() const;
      std::vector<std::string> inputUnitTypeforxValues() const;
      std::vector<std::string> inputUnitTypeforyValues() const;
      std::vector<std::string> inputUnitTypeforzValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
