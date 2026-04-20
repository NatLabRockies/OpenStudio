/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICCONSTANT_HPP
#define EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICCONSTANT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
struct IddObjectType;

namespace epmodel {

  class Model;

  namespace detail {
    class ZoneContaminantSourceAndSinkGenericConstant_Impl;
  }

  class EPMODEL_API ZoneContaminantSourceAndSinkGenericConstant : public ModelObject
  {
   public:
    explicit ZoneContaminantSourceAndSinkGenericConstant(const Model& model);

    virtual ~ZoneContaminantSourceAndSinkGenericConstant() override = default;
    ZoneContaminantSourceAndSinkGenericConstant(const ZoneContaminantSourceAndSinkGenericConstant& other) = default;
    ZoneContaminantSourceAndSinkGenericConstant(ZoneContaminantSourceAndSinkGenericConstant&& other) = default;
    ZoneContaminantSourceAndSinkGenericConstant& operator=(const ZoneContaminantSourceAndSinkGenericConstant&) = default;
    ZoneContaminantSourceAndSinkGenericConstant& operator=(ZoneContaminantSourceAndSinkGenericConstant&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps the IDD-derived ZoneContaminantSourceAndSink:Generic:Constant naming.
    // - Field Mapping: designGenerationRate maps to the EnergyPlus Design Generation Rate field (non-negative source rate).
    // - Field Mapping: designRemovalCoefficient maps to the EnergyPlus Design Removal Coefficient field (non-negative sink capability).
    // - Field Mapping: Zone Name, Generation Schedule Name, and Removal Schedule Name remain object-list relationships and are intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship helpers once scalar saturation is complete without perturbing the scalar API surface.
    boost::optional<double> designGenerationRate() const;
    bool setDesignGenerationRate(double designGenerationRate);
    void resetDesignGenerationRate();

    boost::optional<double> designRemovalCoefficient() const;
    bool setDesignRemovalCoefficient(double designRemovalCoefficient);
    void resetDesignRemovalCoefficient();

   protected:
    using ImplType = detail::ZoneContaminantSourceAndSinkGenericConstant_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneContaminantSourceAndSinkGenericConstant(std::shared_ptr<detail::ZoneContaminantSourceAndSinkGenericConstant_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
