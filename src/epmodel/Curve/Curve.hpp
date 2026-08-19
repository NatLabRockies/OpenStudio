/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVE_HPP
#define EPMODEL_CURVE_HPP

#include "EPModelAPI.hpp"
#include "ResourceObject/ResourceObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Curve_Impl;
  }

  /** \brief Provides common access and evaluation operations for EnergyPlus curve objects.
   *
   * \par EnergyPlus object
   * No single EnergyPlus object. This is the abstract base for the concrete
   * EnergyPlus curve object types.
   *
   * \par Important behavior
   * <code>evaluate()</code> dispatches to the concrete curve type, clamps input
   * variables to the configured ranges, and applies configured output limits.
   * <code>numVariables()</code> reports the number of independent variables
   * expected by the concrete curve.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::Curve</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * <code>Table:Lookup</code> evaluation is not implemented and returns
   * <code>-9999.0</code> after logging a warning. Functional pressure-drop
   * curves do not provide <code>numVariables()</code> or
   * <code>evaluate()</code>; those calls throw because EnergyPlus must
   * evaluate the curve in the context of a plant pressure simulation.
   */
  class EPMODEL_API Curve : public ResourceObject
  {
   public:
    virtual ~Curve() override = default;
    Curve(const Curve& other) = default;
    Curve(Curve&& other) = default;
    Curve& operator=(const Curve&) = default;
    Curve& operator=(Curve&&) = default;

    int numVariables() const;

    double evaluate(const std::vector<double>& x) const;
    double evaluate(double x) const;
    double evaluate(double x, double y) const;
    double evaluate(double x, double y, double z) const;
    double evaluate(double w, double x, double y, double z) const;
    double evaluate(double v, double w, double x, double y, double z) const;

   protected:
    using ImplType = detail::Curve_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    Curve(IddObjectType type, const Model& model);
    explicit Curve(std::shared_ptr<ImplType> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
