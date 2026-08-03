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

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ConstructionWithInternalSource scalar accessor names/signatures.
    // - Field Mapping: Preserved ConstructionWithInternalSource scalar APIs map to
    //   ConstructionProperty:InternalHeatSource scalar fields in EnergyPlus.
    // - Field Mapping: Construction Name is an object-list relationship field and is intentionally excluded.
    // - ForwardTranslator evidence: ForwardTranslateConstructionWithInternalSource.cpp maps
    //   sourcePresentAfterLayerNumber / temperatureCalculationRequestedAfterLayerNumber /
    //   dimensionsForTheCTFCalculation / tubeSpacing /
    //   twoDimensionalTemperatureCalculationPosition directly to
    //   ConstructionProperty:InternalHeatSource fields.
    // - TODO(parity): Add layered material relationship APIs in a follow-up LayeredConstruction parity pass.
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
