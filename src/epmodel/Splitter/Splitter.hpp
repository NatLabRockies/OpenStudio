/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPLITTER_HPP
#define EPMODEL_SPLITTER_HPP

#include "HVACComponent/HVACComponent.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {
    class Loop_Impl;
    class Splitter_Impl;
  }  // namespace detail

  /** \brief Base interface for components that distribute one inlet to branches.
   *
   * \par EnergyPlus object
   * No single EnergyPlus object. Concrete splitter types provide the persisted object.
   *
   * \par Important behavior
   * Relationships are projected from EnergyPlus branch and node topology and mutators maintain that topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::Splitter</code>.
   * <b>No known public API differences.</b>
   *
   * \par Known limitations
   * This abstract interface does not identify a concrete EnergyPlus object.
   */
  class EPMODEL_API Splitter : public HVACComponent
  {
   public:
    virtual ~Splitter() override = default;
    Splitter(const Splitter& other) = default;
    Splitter(Splitter&& other) = default;
    Splitter& operator=(const Splitter&) = default;
    Splitter& operator=(Splitter&&) = default;

    virtual boost::optional<ModelObject> inletModelObject() const;
    virtual unsigned inletPort() const;
    virtual unsigned outletPort(unsigned branchIndex) const;
    virtual unsigned nextOutletPort() const;
    virtual boost::optional<ModelObject> outletModelObject(unsigned branchIndex) const;
    virtual boost::optional<ModelObject> lastOutletModelObject() const;
    virtual std::vector<ModelObject> outletModelObjects() const;
    virtual unsigned newOutletPortAfterBranch(unsigned branchIndex);
    virtual unsigned branchIndexForOutletModelObject(ModelObject modelObject) const;
    virtual unsigned nextBranchIndex() const;
    virtual void removePortForBranch(unsigned branchIndex);

   protected:
    using ImplType = detail::Splitter_Impl;

    friend class openstudio::epmodel::detail::Loop_Impl;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Splitter(const Model& model);
    Splitter(IddObjectType type, const Model& model);
    explicit Splitter(std::shared_ptr<ImplType> impl);
    virtual bool setOutletModelObject(unsigned branchIndex, const ModelObject& modelObject);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
