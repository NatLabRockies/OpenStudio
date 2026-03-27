/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONNECTORSPLITTER_HPP
#define EPMODEL_CONNECTORSPLITTER_HPP

#include "EPModelAPI.hpp"
#include "Splitter/Splitter.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
  class ConnectorSplitter_Impl;
}

class EPMODEL_API ConnectorSplitter : public Splitter
{
 public:
  explicit ConnectorSplitter(const Model& model);

  virtual ~ConnectorSplitter() override = default;
  ConnectorSplitter(const ConnectorSplitter& other) = default;
  ConnectorSplitter(ConnectorSplitter&& other) = default;
  ConnectorSplitter& operator=(const ConnectorSplitter&) = default;
  ConnectorSplitter& operator=(ConnectorSplitter&&) = default;

  static IddObjectType iddObjectType();

  unsigned inletPort() const override;
  unsigned outletPort(unsigned branchIndex) const override;
  unsigned nextOutletPort() const override;
  boost::optional<ModelObject> inletModelObject() const override;
  std::vector<ModelObject> outletModelObjects() const override;
  unsigned nextBranchIndex() const override;
  void removePortForBranch(unsigned branchIndex) override;
  bool setOutletModelObject(unsigned branchIndex, const ModelObject& modelObject) override;

 protected:
  using ImplType = detail::ConnectorSplitter_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class openstudio::epmodel::Model;

  explicit ConnectorSplitter(std::shared_ptr<detail::ConnectorSplitter_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
