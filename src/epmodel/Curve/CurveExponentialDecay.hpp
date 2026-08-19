/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEEXPONENTIALDECAY_HPP
#define EPMODEL_CURVEEXPONENTIALDECAY_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveExponentialDecay_Impl;
  }

  /** \brief Represents an exponential-decay curve.
   *
   * \par EnergyPlus object
   * \epobject{group-performance-curves.html#curveexponentialdecay,Curve:ExponentialDecay}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CurveExponentialDecay</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API CurveExponentialDecay : public Curve
  {
   public:
    explicit CurveExponentialDecay(const Model& model);

    virtual ~CurveExponentialDecay() override = default;
    CurveExponentialDecay(const CurveExponentialDecay& other) = default;
    CurveExponentialDecay(CurveExponentialDecay&& other) = default;
    CurveExponentialDecay& operator=(const CurveExponentialDecay&) = default;
    CurveExponentialDecay& operator=(CurveExponentialDecay&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validInputUnitTypeforxValues();
    static std::vector<std::string> validOutputUnitTypeValues();

    double coefficient1C1() const;
    bool setCoefficient1C1(double coefficient1C1);

    double coefficient2C2() const;
    bool setCoefficient2C2(double coefficient2C2);

    double coefficient3C3() const;
    bool setCoefficient3C3(double coefficient3C3);

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
    bool setInputUnitTypeforx(const std::string& inputUnitTypeforx);
    bool isInputUnitTypeforxDefaulted() const;
    void resetInputUnitTypeforx();

    std::string outputUnitType() const;
    bool setOutputUnitType(const std::string& outputUnitType);
    bool isOutputUnitTypeDefaulted() const;
    void resetOutputUnitType();

   protected:
    using ImplType = detail::CurveExponentialDecay_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveExponentialDecay(std::shared_ptr<detail::CurveExponentialDecay_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
