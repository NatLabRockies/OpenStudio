/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIMPLEGLAZING_HPP
#define EPMODEL_SIMPLEGLAZING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SimpleGlazing_Impl;
  }

  class EPMODEL_API SimpleGlazing : public ModelObject
  {
   public:
    explicit SimpleGlazing(const Model& model, double uFactor = 0.1, double solarHeatGainCoefficient = 0.1);

    virtual ~SimpleGlazing() override = default;
    SimpleGlazing(const SimpleGlazing& other) = default;
    SimpleGlazing(SimpleGlazing&& other) = default;
    SimpleGlazing& operator=(const SimpleGlazing&) = default;
    SimpleGlazing& operator=(SimpleGlazing&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Mirrors openstudio::model::SimpleGlazing scalar accessor names/signatures so the forward/back translators
    //   can share the same preserved API surface while this scaffold keeps the scalar-only focus.
    // - Field Mapping: uFactor, solarHeatGainCoefficient, and visibleTransmittance map directly to the
    //   WindowMaterial_SimpleGlazingSystemFields (U Factor, Solar Heat Gain Coefficient, Visible Transmittance).
    // - ForwardTranslator evidence: ForwardTranslateSimpleGlazing.cpp uses these fields when translating SimpleGlazing to IDF.
    // - Excluded fields: The Name field is handled by ModelObject base behavior and no relationship-like targets exist.

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
