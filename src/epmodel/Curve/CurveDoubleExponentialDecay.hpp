/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEDOUBLEEXPONENTIALDECAY_HPP
#define EPMODEL_CURVEDOUBLEEXPONENTIALDECAY_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <utilities/core/Deprecated.hpp>
#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveDoubleExponentialDecay_Impl;
  }

  /** \brief Represents a double-exponential decay curve.
   *
   * \par EnergyPlus object
   * \epobject{group-performance-curves.html#curvedoubleexponentialdecay,Curve:DoubleExponentialDecay}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CurveDoubleExponentialDecay</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API CurveDoubleExponentialDecay : public Curve
  {
   public:
    explicit CurveDoubleExponentialDecay(const Model& model);

    virtual ~CurveDoubleExponentialDecay() override = default;
    CurveDoubleExponentialDecay(const CurveDoubleExponentialDecay& other) = default;
    CurveDoubleExponentialDecay(CurveDoubleExponentialDecay&& other) = default;
    CurveDoubleExponentialDecay& operator=(const CurveDoubleExponentialDecay&) = default;
    CurveDoubleExponentialDecay& operator=(CurveDoubleExponentialDecay&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validInputUnitTypeforxValues();
    static std::vector<std::string> validOutputUnitTypeValues();

    double coefficient1C1() const;
    bool setCoefficient1C1(double coefficient1C1);

    double coefficient2C2() const;
    bool setCoefficient2C2(double coefficient2C2);

    double coefficient3C3() const;
    bool setCoefficient3C3(double coefficient3C3);

    double coefficient4C4() const;
    OS_DEPRECATED(3, 1, 0) double coefficient3C4() const;
    bool setCoefficient4C4(double coefficient4C4);
    OS_DEPRECATED(3, 1, 0) bool setCoefficient3C4(double coefficient4C4);

    double coefficient5C5() const;
    OS_DEPRECATED(3, 1, 0) double coefficient3C5() const;
    bool setCoefficient5C5(double coefficient5C5);
    OS_DEPRECATED(3, 1, 0) bool setCoefficient3C5(double coefficient5C5);

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
    using ImplType = detail::CurveDoubleExponentialDecay_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveDoubleExponentialDecay(std::shared_ptr<detail::CurveDoubleExponentialDecay_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
