/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DUCT_HPP
#define EPMODEL_DUCT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Duct_Impl;
  }

/** \brief A straight duct component.
 *
 * \par EnergyPlus object
 * \epobject{group-node-branch-management.html#duct,Duct}
 *
 * \par Important behavior
 * The inherited straight-component topology maps its inlet and outlet nodes to the EnergyPlus Duct object.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::Duct</code>.
 *
 * \par Known limitations
 * No type-specific scalar API is provided.
 */
  class EPMODEL_API Duct : public StraightComponent
  {
   public:
    explicit Duct(const Model& model);

    virtual ~Duct() override = default;
    Duct(const Duct& other) = default;
    Duct(Duct&& other) = default;
    Duct& operator=(const Duct&) = default;
    Duct& operator=(Duct&&) = default;

    static IddObjectType iddObjectType();


   protected:
    using ImplType = detail::Duct_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Duct(std::shared_ptr<detail::Duct_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
