/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONNECTORMIXER_IMPL_HPP
#define EPMODEL_CONNECTORMIXER_IMPL_HPP

#include "Mixer/Mixer_Impl.hpp"

namespace openstudio {
namespace epmodel {
  class Branch;
  namespace detail {

    class EPMODEL_API ConnectorMixer_Impl : public Mixer_Impl
    {
     public:
      using Mixer_Impl::Mixer_Impl;
      virtual ~ConnectorMixer_Impl() override = default;

      unsigned outletPort() const override;
      unsigned inletPort(unsigned branchIndex) const override;
      boost::optional<openstudio::epmodel::ModelObject> outletModelObject() const override;
      std::vector<openstudio::epmodel::ModelObject> inletModelObjects() const override;
      unsigned nextBranchIndex() const override;
      void removePortForBranch(unsigned branchIndex) override;
      bool setInletModelObject(unsigned branchIndex, const openstudio::epmodel::ModelObject& modelObject) override;

      boost::optional<openstudio::epmodel::Branch> outletBranch() const;
      bool setOutletBranch(const openstudio::epmodel::Branch& branch);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
