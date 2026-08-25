/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEFANPRESSURERISE_HPP
#define EPMODEL_CURVEFANPRESSURERISE_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveFanPressureRise_Impl;
  }

  /** \brief Represents a fan pressure-rise curve.
   *
   * \par EnergyPlus object
   * \epobject{group-performance-curves.html#curvefanpressurerise,Curve:FanPressureRise}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CurveFanPressureRise</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API CurveFanPressureRise : public Curve
  {
   public:
    explicit CurveFanPressureRise(const Model& model);

    virtual ~CurveFanPressureRise() override = default;
    CurveFanPressureRise(const CurveFanPressureRise& other) = default;
    CurveFanPressureRise(CurveFanPressureRise&& other) = default;
    CurveFanPressureRise& operator=(const CurveFanPressureRise&) = default;
    CurveFanPressureRise& operator=(CurveFanPressureRise&&) = default;

    static IddObjectType iddObjectType();

    double coefficient1C1() const;
    bool setCoefficient1C1(double coefficient1C1);

    double coefficient2C2() const;
    bool setCoefficient2C2(double coefficient2C2);

    double coefficient3C3() const;
    bool setCoefficient3C3(double coefficient3C3);

    double coefficient4C4() const;
    bool setCoefficient4C4(double coefficient4C4);

    double minimumValueofQfan() const;
    bool setMinimumValueofQfan(double minimumValueofQfan);

    double maximumValueofQfan() const;
    bool setMaximumValueofQfan(double maximumValueofQfan);

    double minimumValueofPsm() const;
    bool setMinimumValueofPsm(double minimumValueofPsm);

    double maximumValueofPsm() const;
    bool setMaximumValueofPsm(double maximumValueofPsm);

    boost::optional<double> minimumCurveOutput() const;
    bool setMinimumCurveOutput(double minimumCurveOutput);
    void resetMinimumCurveOutput();

    boost::optional<double> maximumCurveOutput() const;
    bool setMaximumCurveOutput(double maximumCurveOutput);
    void resetMaximumCurveOutput();

   protected:
    using ImplType = detail::CurveFanPressureRise_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveFanPressureRise(std::shared_ptr<detail::CurveFanPressureRise_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
