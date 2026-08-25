/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONWITHINTERNALSOURCE_HPP
#define EPMODEL_CONSTRUCTIONWITHINTERNALSOURCE_HPP

#include "EPModelAPI.hpp"
#include "LayeredConstruction/LayeredConstruction.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  namespace detail {
    class ConstructionWithInternalSource_Impl;
  }

  /** \brief Represents a layered construction with an internal heat source.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#constructioninternalsource,ConstructionProperty:InternalHeatSource}. Its construction
   * name field references a layered construction and the remaining fields hold
   * source and temperature-calculation inputs.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ConstructionWithInternalSource</code>. The scalar
   * source and temperature-calculation methods have the same public meaning.
   * Model's <code>reverseConstructionWithInternalSource()</code> helper and
   * direct construction relationship methods are not available.
   *
   * \par Known limitations
   * The referenced construction cannot be assigned through this wrapper's
   * public API.
   */
  class EPMODEL_API ConstructionWithInternalSource : public LayeredConstruction
  {
   public:
    explicit ConstructionWithInternalSource(const Model& model);

    virtual ~ConstructionWithInternalSource() override = default;
    ConstructionWithInternalSource(const ConstructionWithInternalSource& other) = default;
    ConstructionWithInternalSource(ConstructionWithInternalSource&& other) = default;
    ConstructionWithInternalSource& operator=(const ConstructionWithInternalSource&) = default;
    ConstructionWithInternalSource& operator=(ConstructionWithInternalSource&&) = default;

    static IddObjectType iddObjectType();

    int sourcePresentAfterLayerNumber() const;
    bool setSourcePresentAfterLayerNumber(int sourcePresentAfterLayerNumber);

    int temperatureCalculationRequestedAfterLayerNumber() const;
    bool setTemperatureCalculationRequestedAfterLayerNumber(int temperatureCalculationRequestedAfterLayerNumber);

    int dimensionsForTheCTFCalculation() const;
    bool setDimensionsForTheCTFCalculation(int dimensionsForTheCTFCalculation);

    double tubeSpacing() const;
    bool setTubeSpacing(double tubeSpacing);

    double twoDimensionalTemperatureCalculationPosition() const;
    bool setTwoDimensionalTemperatureCalculationPosition(double twoDimensionalTemperatureCalculationPosition);
    bool isTwoDimensionalTemperatureCalculationPositionDefaulted() const;
    void resetTwoDimensionalTemperatureCalculationPosition();

   protected:
    using ImplType = detail::ConstructionWithInternalSource_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ConstructionWithInternalSource(std::shared_ptr<detail::ConstructionWithInternalSource_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
