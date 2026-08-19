/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIMPLEGLAZING_HPP
#define EPMODEL_SIMPLEGLAZING_HPP

#include "EPModelAPI.hpp"
#include "Glazing/Glazing.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SimpleGlazing_Impl;
  }

  /** \brief Represents glazing with simplified U-factor and solar-gain inputs.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#windowmaterialsimpleglazingsystem,WindowMaterial:SimpleGlazingSystem}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SimpleGlazing</code>. The U-factor, solar heat
   * gain coefficient, and visible-transmittance methods have the same public
   * meaning.
   *
   * \par Known limitations
   * This simplified object does not expose detailed layer optical or thermal
   * properties.
   */
  class EPMODEL_API SimpleGlazing : public Glazing
  {
   public:
    explicit SimpleGlazing(const Model& model, double uFactor = 0.1, double solarHeatGainCoefficient = 0.1);

    virtual ~SimpleGlazing() override = default;
    SimpleGlazing(const SimpleGlazing& other) = default;
    SimpleGlazing(SimpleGlazing&& other) = default;
    SimpleGlazing& operator=(const SimpleGlazing&) = default;
    SimpleGlazing& operator=(SimpleGlazing&&) = default;

    static IddObjectType iddObjectType();

    double uFactor() const;

    bool setUFactor(double uFactor);

    double solarHeatGainCoefficient() const;

    bool setSolarHeatGainCoefficient(double solarHeatGainCoefficient);

    boost::optional<double> visibleTransmittance() const;

    bool setVisibleTransmittance(double visibleTransmittance);

    void resetVisibleTransmittance();

   protected:
    using ImplType = detail::SimpleGlazing_Impl;

    explicit SimpleGlazing(std::shared_ptr<detail::SimpleGlazing_Impl> impl);

    friend class detail::SimpleGlazing_Impl;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_SIMPLEGLAZING_HPP
