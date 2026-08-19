/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MIXER_HPP
#define EPMODEL_MIXER_HPP

#include "HVACComponent/HVACComponent.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {
    class Loop_Impl;
    class Mixer_Impl;
  }  // namespace detail

  /** \brief Base interface for components that combine multiple inlet branches.
   *
   * \par EnergyPlus object
   * No single EnergyPlus object. Concrete mixer types provide the persisted object.
   *
   * \par Important behavior
   * Relationships are projected from EnergyPlus branch and node topology and mutators maintain that topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::Mixer</code>.
   * <b>Added: explicit inlet and outlet model-object mutators, including <code>setInletModelObject()</code>, <code>resetInletModelObject()</code>, <code>setOutletModelObject()</code>, and <code>resetOutletModelObject()</code>.</b>
   *
   * \par Known limitations
   * This abstract interface does not identify a concrete EnergyPlus object.
   */
  class EPMODEL_API Mixer : public HVACComponent
  {
   public:
    virtual ~Mixer() override = default;
    Mixer(const Mixer& other) = default;
    Mixer(Mixer&& other) = default;
    Mixer& operator=(const Mixer&) = default;
    Mixer& operator=(Mixer&&) = default;

    virtual boost::optional<ModelObject> outletModelObject() const;
    virtual bool setOutletModelObject(const ModelObject& modelObject);
    virtual void resetOutletModelObject();
    virtual unsigned outletPort() const;
    virtual unsigned inletPort(unsigned branchIndex) const;
    virtual unsigned nextInletPort() const;
    virtual boost::optional<ModelObject> inletModelObject(unsigned branchIndex) const;
    virtual boost::optional<ModelObject> lastInletModelObject() const;
    virtual std::vector<ModelObject> inletModelObjects() const;
    virtual unsigned newInletPortAfterBranch(unsigned branchIndex);
    virtual unsigned branchIndexForInletModelObject(const ModelObject& modelObject) const;
    virtual unsigned nextBranchIndex() const;
    virtual void removePortForBranch(unsigned branchIndex);
    virtual bool setInletModelObject(unsigned branchIndex, const ModelObject& modelObject);
    virtual void resetInletModelObject(unsigned branchIndex);

   protected:
    using ImplType = detail::Mixer_Impl;

    friend class openstudio::epmodel::detail::Loop_Impl;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Mixer(const Model& model);
    Mixer(IddObjectType type, const Model& model);
    explicit Mixer(std::shared_ptr<ImplType> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
