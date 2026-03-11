/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTAMINANTSOURCEANDSINKCARBONDIOXIDE_HPP
#define EPMODEL_ZONECONTAMINANTSOURCEANDSINKCARBONDIOXIDE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
struct IddObjectType;

namespace epmodel {

  class Model;

  namespace detail {
    class ZoneContaminantSourceAndSinkCarbonDioxide_Impl;
  }

  class EPMODEL_API ZoneContaminantSourceAndSinkCarbonDioxide : public ModelObject
  {
   public:
    explicit ZoneContaminantSourceAndSinkCarbonDioxide(const Model& model);

    virtual ~ZoneContaminantSourceAndSinkCarbonDioxide() override = default;
    ZoneContaminantSourceAndSinkCarbonDioxide(const ZoneContaminantSourceAndSinkCarbonDioxide& other) = default;
    ZoneContaminantSourceAndSinkCarbonDioxide(ZoneContaminantSourceAndSinkCarbonDioxide&& other) = default;
    ZoneContaminantSourceAndSinkCarbonDioxide& operator=(const ZoneContaminantSourceAndSinkCarbonDioxide&) = default;
    ZoneContaminantSourceAndSinkCarbonDioxide& operator=(ZoneContaminantSourceAndSinkCarbonDioxide&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so class/accessor naming follows the IDD (ZoneContaminantSourceAndSink:CarbonDioxide) layout.
    // - Field Mapping: designGenerationRate maps directly to the EnergyPlus Design Generation Rate field (positive = source, negative = sink).
    // - Field Mapping: Zone Name and Schedule Name remain object-list relationships and are intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship helpers once scalar saturation is complete without altering the scalar API surface.
    boost::optional<double> designGenerationRate() const;
    bool setDesignGenerationRate(double designGenerationRate);
    void resetDesignGenerationRate();

   protected:
    using ImplType = detail::ZoneContaminantSourceAndSinkCarbonDioxide_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneContaminantSourceAndSinkCarbonDioxide(std::shared_ptr<detail::ZoneContaminantSourceAndSinkCarbonDioxide_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
