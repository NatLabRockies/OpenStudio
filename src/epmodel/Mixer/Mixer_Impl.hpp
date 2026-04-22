/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MIXER_IMPL_HPP
#define EPMODEL_MIXER_IMPL_HPP

#include "HVACComponent/HVACComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

class ModelObject;

namespace detail {

class EPMODEL_API Mixer_Impl : public HVACComponent_Impl
{
 public:
  using HVACComponent_Impl::HVACComponent_Impl;
  virtual ~Mixer_Impl() override = default;

  virtual unsigned outletPort() const = 0;
  virtual unsigned inletPort(unsigned branchIndex) const = 0;
  virtual unsigned nextInletPort() const;

  virtual boost::optional<ModelObject> outletModelObject() const;
  virtual bool setOutletModelObject(const ModelObject& modelObject);
  virtual void resetOutletModelObject();
  virtual boost::optional<ModelObject> inletModelObject(unsigned branchIndex) const;
  virtual boost::optional<ModelObject> lastInletModelObject() const;
  virtual std::vector<ModelObject> inletModelObjects() const;
  virtual unsigned newInletPortAfterBranch(unsigned branchIndex);
  virtual unsigned branchIndexForInletModelObject(const ModelObject& modelObject) const;
  virtual unsigned nextBranchIndex() const;
  virtual void removePortForBranch(unsigned branchIndex);
  virtual bool setInletModelObject(unsigned branchIndex, const ModelObject& modelObject);
  virtual void resetInletModelObject(unsigned branchIndex);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
