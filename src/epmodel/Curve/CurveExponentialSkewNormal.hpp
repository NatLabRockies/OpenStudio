/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEEXPONENTIALSKEWNORMAL_HPP
#define EPMODEL_CURVEEXPONENTIALSKEWNORMAL_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveExponentialSkewNormal_Impl;
  }

  /** \brief Represents an exponential skew-normal curve.
   *
   * \par EnergyPlus object
   * \epobject{group-performance-curves.html#curveexponentialskewnormal,Curve:ExponentialSkewNormal}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CurveExponentialSkewNormal</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API CurveExponentialSkewNormal : public Curve
  {
   public:
    explicit CurveExponentialSkewNormal(const Model& model);

    virtual ~CurveExponentialSkewNormal() override = default;
    CurveExponentialSkewNormal(const CurveExponentialSkewNormal& other) = default;
    CurveExponentialSkewNormal(CurveExponentialSkewNormal&& other) = default;
    CurveExponentialSkewNormal& operator=(const CurveExponentialSkewNormal&) = default;
    CurveExponentialSkewNormal& operator=(CurveExponentialSkewNormal&&) = default;

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
    bool setCoefficient4C4(double coefficient4C4);

    double minimumValueofx() const;
    bool setMinimumValueofx(double minimumValueofx);

    boost::optional<double> minimumCurveOutput() const;
    bool setMinimumCurveOutput(double minimumCurveOutput);
    void resetMinimumCurveOutput();

    double maximumValueofx() const;
    bool setMaximumValueofx(double maximumValueofx);

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
    using ImplType = detail::CurveExponentialSkewNormal_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveExponentialSkewNormal(std::shared_ptr<detail::CurveExponentialSkewNormal_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
