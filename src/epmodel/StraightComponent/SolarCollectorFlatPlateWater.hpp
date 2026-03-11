/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORFLATPLATEWATER_HPP
#define EPMODEL_SOLARCOLLECTORFLATPLATEWATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SolarCollectorFlatPlateWater_Impl;
}

class EPMODEL_API SolarCollectorFlatPlateWater : public StraightComponent
{
 public:
  explicit SolarCollectorFlatPlateWater(const Model& model);

  virtual ~SolarCollectorFlatPlateWater() override = default;
  SolarCollectorFlatPlateWater(const SolarCollectorFlatPlateWater& other) = default;
  SolarCollectorFlatPlateWater(SolarCollectorFlatPlateWater&& other) = default;
  SolarCollectorFlatPlateWater& operator=(const SolarCollectorFlatPlateWater&) = default;
  SolarCollectorFlatPlateWater& operator=(SolarCollectorFlatPlateWater&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::SolarCollectorFlatPlateWater scalar accessor names/signatures.
  // - Field Mapping: maximumFlowRate maps directly to E+ SolarCollector:FlatPlate:Water MaximumFlowRate.
  // - Field Mapping: relationship/node fields (solar collector performance, surface, inlet/outlet nodes) are excluded from this scalar scaffold.
  // - ForwardTranslator evidence: ForwardTranslateSolarCollectorFlatPlateWater.cpp reads maximumFlowRate() and writes MaximumFlowRate.
  // - TODO(parity): add non-scalar relationship APIs incrementally without changing preserved scalar signatures.
  boost::optional<double> maximumFlowRate() const;
  bool setMaximumFlowRate(double maximumFlowRate);
  void resetMaximumFlowRate();

 protected:
  using ImplType = detail::SolarCollectorFlatPlateWater_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SolarCollectorFlatPlateWater(std::shared_ptr<detail::SolarCollectorFlatPlateWater_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
