/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEFUNCTIONALPRESSUREDROP_HPP
#define EPMODEL_CURVEFUNCTIONALPRESSUREDROP_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CurveFunctionalPressureDrop_Impl;
  }

  /** \brief Represents a functional pressure-drop curve.
   *
   * \par EnergyPlus object
   * \epobject{group-performance-curves.html#curvefunctionalpressuredrop,Curve:Functional:PressureDrop}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CurveFunctionalPressureDrop</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * <code>numVariables()</code> and <code>evaluate()</code> throw for this
   * curve. EnergyPlus must evaluate it in the context of a plant pressure
   * simulation.
   */
  class EPMODEL_API CurveFunctionalPressureDrop : public Curve
  {
   public:
    explicit CurveFunctionalPressureDrop(const Model& model);

    virtual ~CurveFunctionalPressureDrop() override = default;
    CurveFunctionalPressureDrop(const CurveFunctionalPressureDrop& other) = default;
    CurveFunctionalPressureDrop(CurveFunctionalPressureDrop&& other) = default;
    CurveFunctionalPressureDrop& operator=(const CurveFunctionalPressureDrop&) = default;
    CurveFunctionalPressureDrop& operator=(CurveFunctionalPressureDrop&&) = default;

    static IddObjectType iddObjectType();

    double diameter() const;
    bool setDiameter(double diameter);

    boost::optional<double> minorLossCoefficient() const;
    bool setMinorLossCoefficient(double minorLossCoefficient);
    void resetMinorLossCoefficient();

    boost::optional<double> length() const;
    bool setLength(double length);
    void resetLength();

    boost::optional<double> roughness() const;
    bool setRoughness(double roughness);
    void resetRoughness();

    boost::optional<double> fixedFrictionFactor() const;
    bool setFixedFrictionFactor(double fixedFrictionFactor);
    void resetFixedFrictionFactor();

   protected:
    using ImplType = detail::CurveFunctionalPressureDrop_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CurveFunctionalPressureDrop(std::shared_ptr<detail::CurveFunctionalPressureDrop_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
