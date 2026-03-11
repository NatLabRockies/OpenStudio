/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTTOWEROBJECTREFERENCE_HPP
#define EPMODEL_HVACTEMPLATEPLANTTOWEROBJECTREFERENCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplatePlantTowerObjectReference_Impl;
}

class EPMODEL_API HVACTemplatePlantTowerObjectReference : public ModelObject
{
 public:
  explicit HVACTemplatePlantTowerObjectReference(const Model& model);

  virtual ~HVACTemplatePlantTowerObjectReference() override = default;
  HVACTemplatePlantTowerObjectReference(const HVACTemplatePlantTowerObjectReference& other) = default;
  HVACTemplatePlantTowerObjectReference(HVACTemplatePlantTowerObjectReference&& other) = default;
  HVACTemplatePlantTowerObjectReference& operator=(const HVACTemplatePlantTowerObjectReference&) = default;
  HVACTemplatePlantTowerObjectReference& operator=(HVACTemplatePlantTowerObjectReference&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> coolingTowerObjectTypeValues();
  static std::vector<std::string> templatePlantLoopTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map to HVACTemplate:Plant:Tower:ObjectReference fields Cooling Tower Object Type,
  //   Priority, and Template Plant Loop Type.
  // - Field Mapping: Cooling Tower Name is an object-list relationship field and is intentionally excluded in scalar-only scaffold.
  // - TODO(parity): Revisit only if a future parity pass introduces relationship/object-link APIs.
  std::string coolingTowerObjectType() const;
  boost::optional<double> priority() const;
  boost::optional<std::string> templatePlantLoopType() const;

  bool isCoolingTowerObjectTypeDefaulted() const;

  bool setCoolingTowerObjectType(const std::string& coolingTowerObjectType);
  bool setPriority(double priority);
  bool setTemplatePlantLoopType(const std::string& templatePlantLoopType);

  void resetCoolingTowerObjectType();
  void resetPriority();
  void resetTemplatePlantLoopType();

 protected:
  using ImplType = detail::HVACTemplatePlantTowerObjectReference_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplatePlantTowerObjectReference(std::shared_ptr<detail::HVACTemplatePlantTowerObjectReference_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
