/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONEWINDPRESSURECOEFFICIENTVALUES_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONEWINDPRESSURECOEFFICIENTVALUES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl;
  }

  class EPMODEL_API AirflowNetworkMultiZoneWindPressureCoefficientValues : public ModelObject
  {
   public:
    explicit AirflowNetworkMultiZoneWindPressureCoefficientValues(const Model& model);

    virtual ~AirflowNetworkMultiZoneWindPressureCoefficientValues() override = default;
    AirflowNetworkMultiZoneWindPressureCoefficientValues(const AirflowNetworkMultiZoneWindPressureCoefficientValues& other) = default;
    AirflowNetworkMultiZoneWindPressureCoefficientValues(AirflowNetworkMultiZoneWindPressureCoefficientValues&& other) = default;
    AirflowNetworkMultiZoneWindPressureCoefficientValues& operator=(const AirflowNetworkMultiZoneWindPressureCoefficientValues&) = default;
    AirflowNetworkMultiZoneWindPressureCoefficientValues& operator=(AirflowNetworkMultiZoneWindPressureCoefficientValues&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: No type-specific non-name scalar fields exist for this object.
    // - Field Mapping: AirflowNetwork:MultiZone:WindPressureCoefficientArray Name is a relationship field and is excluded.
    // - Field Mapping: Extensible Wind Pressure Coefficient Value entries are intentionally excluded from simple scalar accessor scaffolding.
    // - TODO(parity): Add non-scalar relationship/extensible APIs if/when parity scope expands.

   protected:
    using ImplType = detail::AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkMultiZoneWindPressureCoefficientValues(
      std::shared_ptr<detail::AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
