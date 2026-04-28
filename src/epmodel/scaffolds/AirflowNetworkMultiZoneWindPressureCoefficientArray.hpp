/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONEWINDPRESSURECOEFFICIENTARRAY_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONEWINDPRESSURECOEFFICIENTARRAY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl;
}

class EPMODEL_API AirflowNetworkMultiZoneWindPressureCoefficientArray : public ModelObject
{
 public:
  explicit AirflowNetworkMultiZoneWindPressureCoefficientArray(const Model& model);

  virtual ~AirflowNetworkMultiZoneWindPressureCoefficientArray() override = default;
  AirflowNetworkMultiZoneWindPressureCoefficientArray(const AirflowNetworkMultiZoneWindPressureCoefficientArray& other) = default;
  AirflowNetworkMultiZoneWindPressureCoefficientArray(AirflowNetworkMultiZoneWindPressureCoefficientArray&& other) = default;
  AirflowNetworkMultiZoneWindPressureCoefficientArray& operator=(const AirflowNetworkMultiZoneWindPressureCoefficientArray&) = default;
  AirflowNetworkMultiZoneWindPressureCoefficientArray& operator=(AirflowNetworkMultiZoneWindPressureCoefficientArray&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: No type-specific non-name scalar fields exist for this object.
  // - Field Mapping: Extensible Wind Direction entries are intentionally excluded from simple scalar accessor scaffolding.
  // - TODO(parity): Add non-scalar extensible APIs if/when extensible-field parity is in scope.

 protected:
  using ImplType = detail::AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirflowNetworkMultiZoneWindPressureCoefficientArray(
    std::shared_ptr<detail::AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
