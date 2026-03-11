/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACSYSTEMROOTFINDINGALGORITHM_HPP
#define EPMODEL_HVACSYSTEMROOTFINDINGALGORITHM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACSystemRootFindingAlgorithm_Impl;
}

class EPMODEL_API HVACSystemRootFindingAlgorithm : public ModelObject
{
 public:
  explicit HVACSystemRootFindingAlgorithm(const Model& model);

  virtual ~HVACSystemRootFindingAlgorithm() override = default;
  HVACSystemRootFindingAlgorithm(const HVACSystemRootFindingAlgorithm& other) = default;
  HVACSystemRootFindingAlgorithm(HVACSystemRootFindingAlgorithm&& other) = default;
  HVACSystemRootFindingAlgorithm& operator=(const HVACSystemRootFindingAlgorithm&) = default;
  HVACSystemRootFindingAlgorithm& operator=(HVACSystemRootFindingAlgorithm&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> algorithmValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: algorithm and numberofIterationsBeforeAlgorithmSwitch map directly to
  //   EnergyPlus HVACSystemRootFindingAlgorithm scalar fields.
  // - TODO(parity): Keep relationship APIs out of scope for this scalar-only scaffold pass.
  std::string algorithm() const;
  bool isAlgorithmDefaulted() const;
  bool setAlgorithm(const std::string& algorithm);
  void resetAlgorithm();

  int numberofIterationsBeforeAlgorithmSwitch() const;
  bool isNumberofIterationsBeforeAlgorithmSwitchDefaulted() const;
  bool setNumberofIterationsBeforeAlgorithmSwitch(int numberofIterationsBeforeAlgorithmSwitch);
  void resetNumberofIterationsBeforeAlgorithmSwitch();

 protected:
  using ImplType = detail::HVACSystemRootFindingAlgorithm_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACSystemRootFindingAlgorithm(std::shared_ptr<detail::HVACSystemRootFindingAlgorithm_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
