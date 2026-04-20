/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICDEPOSITIONRATESINK_HPP
#define EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICDEPOSITIONRATESINK_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl;
  }

  class EPMODEL_API ZoneContaminantSourceAndSinkGenericDepositionRateSink : public ModelObject
  {
   public:
    explicit ZoneContaminantSourceAndSinkGenericDepositionRateSink(const Model& model);

    virtual ~ZoneContaminantSourceAndSinkGenericDepositionRateSink() override = default;
    ZoneContaminantSourceAndSinkGenericDepositionRateSink(const ZoneContaminantSourceAndSinkGenericDepositionRateSink& other) = default;
    ZoneContaminantSourceAndSinkGenericDepositionRateSink(ZoneContaminantSourceAndSinkGenericDepositionRateSink&& other) = default;
    ZoneContaminantSourceAndSinkGenericDepositionRateSink& operator=(const ZoneContaminantSourceAndSinkGenericDepositionRateSink&) = default;
    ZoneContaminantSourceAndSinkGenericDepositionRateSink& operator=(ZoneContaminantSourceAndSinkGenericDepositionRateSink&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type follows the EnergyPlus IDD naming for ZoneContaminantSourceAndSink:Generic:DepositionRateSink.
    // - Field Mapping: depositionRate maps directly to the Deposition Rate field on the EnergyPlus object.
    // - Field Mapping: Zone Name and Schedule Name remain object-list relationships and are intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship helpers once scalar saturation completes without altering scalar APIs.
    boost::optional<double> depositionRate() const;
    bool setDepositionRate(double depositionRate);
    void resetDepositionRate();

   protected:
    using ImplType = detail::ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneContaminantSourceAndSinkGenericDepositionRateSink(
      std::shared_ptr<detail::ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
