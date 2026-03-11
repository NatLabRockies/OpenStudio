/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPLITTER_HPP
#define EPMODEL_SPLITTER_HPP

#include "HVACComponent.hpp"

namespace openstudio {
namespace epmodel {

class EPMODEL_API Splitter : public HVACComponent
{
 public:
  virtual ~Splitter() override = default;
  explicit Splitter(const Model& model);
  Splitter(const Splitter& other) = default;
  Splitter(Splitter&& other) = default;
  Splitter& operator=(const Splitter&) = default;
  Splitter& operator=(Splitter&&) = default;

  virtual boost::optional<ModelObject> inletModelObject() const;
  virtual unsigned inletPort() const;
  virtual unsigned outletPort(unsigned branchIndex) const;
  virtual unsigned nextOutletPort() const;
  boost::optional<ModelObject> outletModelObject(unsigned branchIndex) const;
  boost::optional<ModelObject> lastOutletModelObject() const;
  virtual std::vector<ModelObject> outletModelObjects() const;
  virtual unsigned newOutletPortAfterBranch(unsigned branchIndex);
  virtual unsigned branchIndexForOutletModelObject(ModelObject modelObject) const;
  virtual unsigned nextBranchIndex() const;
  virtual void removePortForBranch(unsigned branchIndex);
  virtual bool setOutletModelObject(unsigned branchIndex, const ModelObject& modelObject);

 protected:
  Splitter(IddObjectType type, const Model& model);
  explicit Splitter(std::shared_ptr<detail::HVACComponent_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
