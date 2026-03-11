/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MIXER_HPP
#define EPMODEL_MIXER_HPP

#include "HVACComponent/HVACComponent.hpp"

namespace openstudio {
namespace epmodel {

class EPMODEL_API Mixer : public HVACComponent
{
 public:
  virtual ~Mixer() override = default;
  explicit Mixer(const Model& model);
  Mixer(const Mixer& other) = default;
  Mixer(Mixer&& other) = default;
  Mixer& operator=(const Mixer&) = default;
  Mixer& operator=(Mixer&&) = default;

  virtual boost::optional<ModelObject> outletModelObject() const;
  virtual unsigned outletPort() const;
  virtual unsigned inletPort(unsigned branchIndex) const;
  virtual unsigned nextInletPort() const;
  boost::optional<ModelObject> inletModelObject(unsigned branchIndex) const;
  boost::optional<ModelObject> lastInletModelObject() const;
  virtual std::vector<ModelObject> inletModelObjects() const;
  virtual unsigned newInletPortAfterBranch(unsigned branchIndex);
  virtual unsigned branchIndexForInletModelObject(const ModelObject& modelObject) const;
  virtual unsigned nextBranchIndex() const;
  virtual void removePortForBranch(unsigned branchIndex);
  virtual bool setInletModelObject(unsigned branchIndex, const ModelObject& modelObject);

 protected:
  Mixer(IddObjectType type, const Model& model);
  explicit Mixer(std::shared_ptr<detail::HVACComponent_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
