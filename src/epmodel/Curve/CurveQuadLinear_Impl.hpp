/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUADLINEAR_IMPL_HPP
#define EPMODEL_CURVEQUADLINEAR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CurveQuadLinear_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~CurveQuadLinear_Impl() override = default;

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

      std::vector<std::string> inputUnitTypeforwValues() const;
      std::vector<std::string> inputUnitTypeforxValues() const;
      std::vector<std::string> inputUnitTypeforyValues() const;
      std::vector<std::string> inputUnitTypeforzValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
