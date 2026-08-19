/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUARTIC_HPP
#define EPMODEL_CURVEQUARTIC_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveQuartic_Impl;
  }

  /** \brief Represents a quartic curve.
   *
   * \par EnergyPlus object
   * \epobject{group-performance-curves.html#curvequartic,Curve:Quartic}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CurveQuartic</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API CurveQuartic : public Curve
  {
   public:
    explicit CurveQuartic(const Model& model);

    virtual ~CurveQuartic() override = default;
    CurveQuartic(const CurveQuartic& other) = default;
    CurveQuartic(CurveQuartic&& other) = default;
    CurveQuartic& operator=(const CurveQuartic&) = default;
    CurveQuartic& operator=(CurveQuartic&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validInputUnitTypeforXValues();
    static std::vector<std::string> validOutputUnitTypeValues();

    double coefficient1Constant() const;
    bool setCoefficient1Constant(double coefficient1Constant);

    double coefficient2x() const;
    bool setCoefficient2x(double coefficient2x);

    double coefficient3xPOW2() const;
    bool setCoefficient3xPOW2(double coefficient3xPOW2);

    double coefficient4xPOW3() const;
    bool setCoefficient4xPOW3(double coefficient4xPOW3);

    double coefficient5xPOW4() const;
    bool setCoefficient5xPOW4(double coefficient5xPOW4);

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

    std::string inputUnitTypeforX() const;
    bool isInputUnitTypeforXDefaulted() const;
    bool setInputUnitTypeforX(const std::string& inputUnitTypeforX);
    void resetInputUnitTypeforX();

    std::string outputUnitType() const;
    bool isOutputUnitTypeDefaulted() const;
    bool setOutputUnitType(const std::string& outputUnitType);
    void resetOutputUnitType();

   protected:
    using ImplType = detail::CurveQuartic_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveQuartic(std::shared_ptr<detail::CurveQuartic_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
