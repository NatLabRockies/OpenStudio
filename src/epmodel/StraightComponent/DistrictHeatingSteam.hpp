/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DISTRICTHEATINGSTEAM_HPP
#define EPMODEL_DISTRICTHEATINGSTEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class DistrictHeatingSteam_Impl;
}

class EPMODEL_API DistrictHeatingSteam : public StraightComponent
{
 public:
  explicit DistrictHeatingSteam(const Model& model);

  virtual ~DistrictHeatingSteam() override = default;
  DistrictHeatingSteam(const DistrictHeatingSteam& other) = default;
  DistrictHeatingSteam(DistrictHeatingSteam&& other) = default;
  DistrictHeatingSteam& operator=(const DistrictHeatingSteam&) = default;
  DistrictHeatingSteam& operator=(DistrictHeatingSteam&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::DistrictHeatingSteam scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: nominalCapacity/isNominalCapacityAutosized/setNominalCapacity/autosizeNominalCapacity map to E+ DistrictHeating:Steam Nominal Capacity.
  // - ForwardTranslator evidence: ForwardTranslateDistrictHeatingSteam.cpp writes model.nominalCapacity()/isNominalCapacityAutosized() to DistrictHeating:Steam Nominal Capacity.
  // - Field Mapping: Steam inlet/outlet node names and Capacity Fraction Schedule are relationship-like fields and excluded in this scalar pass.
  // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
  boost::optional<double> nominalCapacity() const;
  bool isNominalCapacityAutosized() const;

  bool setNominalCapacity(double nominalCapacity);
  void autosizeNominalCapacity();

  boost::optional<double> autosizedNominalCapacity() const;

 protected:
  using ImplType = detail::DistrictHeatingSteam_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit DistrictHeatingSteam(std::shared_ptr<detail::DistrictHeatingSteam_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
