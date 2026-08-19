/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVERECTANGULARHYPERBOLA2_HPP
#define EPMODEL_CURVERECTANGULARHYPERBOLA2_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveRectangularHyperbola2_Impl;
  }

  /** \brief Represents a second rectangular-hyperbola curve.
   *
   * \par EnergyPlus object
   * \epobject{group-performance-curves.html#curverectangularhyperbola2,Curve:RectangularHyperbola2}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CurveRectangularHyperbola2</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API CurveRectangularHyperbola2 : public Curve
  {
   public:
    explicit CurveRectangularHyperbola2(const Model& model);

    virtual ~CurveRectangularHyperbola2() override = default;
    CurveRectangularHyperbola2(const CurveRectangularHyperbola2& other) = default;
    CurveRectangularHyperbola2(CurveRectangularHyperbola2&& other) = default;
    CurveRectangularHyperbola2& operator=(const CurveRectangularHyperbola2&) = default;
    CurveRectangularHyperbola2& operator=(CurveRectangularHyperbola2&&) = default;

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
    using ImplType = detail::CurveRectangularHyperbola2_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveRectangularHyperbola2(std::shared_ptr<detail::CurveRectangularHyperbola2_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
