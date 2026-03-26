/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPLITTER_IMPL_HPP
#define EPMODEL_SPLITTER_IMPL_HPP

#include "HVACComponent/HVACComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

class ModelObject;

namespace detail {

class EPMODEL_API Splitter_Impl : public HVACComponent_Impl
{
 public:
  using HVACComponent_Impl::HVACComponent_Impl;
  virtual ~Splitter_Impl() override = default;

  virtual unsigned inletPort() const = 0;
  virtual unsigned outletPort(unsigned branchIndex) const = 0;
  virtual unsigned nextOutletPort() const;

  virtual boost::optional<ModelObject> inletModelObject() const;
  virtual boost::optional<ModelObject> outletModelObject(unsigned branchIndex) const;
  virtual boost::optional<ModelObject> lastOutletModelObject() const;
  virtual std::vector<ModelObject> outletModelObjects() const;
  virtual unsigned newOutletPortAfterBranch(unsigned branchIndex);
  virtual unsigned branchIndexForOutletModelObject(ModelObject modelObject) const;
  virtual unsigned nextBranchIndex() const;
  virtual void removePortForBranch(unsigned branchIndex);
  virtual bool setOutletModelObject(unsigned branchIndex, const ModelObject& modelObject);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
