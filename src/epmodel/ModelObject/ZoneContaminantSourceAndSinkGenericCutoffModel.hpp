/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICCUTOFFMODEL_HPP
#define EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICCUTOFFMODEL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneContaminantSourceAndSinkGenericCutoffModel_Impl;
  }

  class EPMODEL_API ZoneContaminantSourceAndSinkGenericCutoffModel : public ModelObject
  {
   public:
    explicit ZoneContaminantSourceAndSinkGenericCutoffModel(const Model& model);

    virtual ~ZoneContaminantSourceAndSinkGenericCutoffModel() override = default;
    ZoneContaminantSourceAndSinkGenericCutoffModel(const ZoneContaminantSourceAndSinkGenericCutoffModel&) = default;
    ZoneContaminantSourceAndSinkGenericCutoffModel(ZoneContaminantSourceAndSinkGenericCutoffModel&&) = default;
    ZoneContaminantSourceAndSinkGenericCutoffModel& operator=(const ZoneContaminantSourceAndSinkGenericCutoffModel&) = default;
    ZoneContaminantSourceAndSinkGenericCutoffModel& operator=(ZoneContaminantSourceAndSinkGenericCutoffModel&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to ZoneContaminantSourceAndSink:Generic:CutoffModel numeric fields.
    // - Field Mapping: Zone Name and Schedule Name linkage fields remain excluded because they are relationship object-lists.
    // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.

    // Field group: Design Generation Rate Coefficient (DesignGenerationRateCoefficient)
    boost::optional<double> designGenerationRateCoefficient() const;
    bool setDesignGenerationRateCoefficient(double designGenerationRateCoefficient);
    void resetDesignGenerationRateCoefficient();

    // Field group: Cutoff Generic Contaminant At Which Emission Ceases (CutoffGenericContaminantAtWhichEmissionCeases)
    boost::optional<double> cutoffGenericContaminantAtWhichEmissionCeases() const;
    bool setCutoffGenericContaminantAtWhichEmissionCeases(double cutoffGenericContaminantAtWhichEmissionCeases);
    void resetCutoffGenericContaminantAtWhichEmissionCeases();

   protected:
    using ImplType = detail::ZoneContaminantSourceAndSinkGenericCutoffModel_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneContaminantSourceAndSinkGenericCutoffModel(std::shared_ptr<detail::ZoneContaminantSourceAndSinkGenericCutoffModel_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
