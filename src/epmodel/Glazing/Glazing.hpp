/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GLAZING_HPP
#define EPMODEL_GLAZING_HPP

#include "EPModelAPI.hpp"
#include "FenestrationMaterial/FenestrationMaterial.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  namespace detail {
    class Glazing_Impl;
  }

  /** \brief Base class for glass layers in fenestration constructions.
   *
   * \par EnergyPlus object
   * This class has no single EnergyPlus object. Concrete glazing subclasses
   * encapsulate the applicable <code>WindowMaterial:*</code> object.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::Glazing</code>. No additional public API
   * differences are known.
   *
   * \par Known limitations
   * This abstract class cannot be persisted without a concrete glazing type.
   */
  class EPMODEL_API Glazing : public FenestrationMaterial
  {
   public:
    virtual ~Glazing() override = default;
    Glazing(const Glazing& other) = default;
    Glazing(Glazing&& other) = default;
    Glazing& operator=(const Glazing&) = default;
    Glazing& operator=(Glazing&&) = default;

   protected:
    using ImplType = detail::Glazing_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    Glazing(IddObjectType type, const Model& model);

    explicit Glazing(std::shared_ptr<detail::Glazing_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.Glazing");
  };

  using OptionalGlazing = boost::optional<Glazing>;
  using GlazingVector = std::vector<Glazing>;

}  // namespace epmodel
}  // namespace openstudio

#endif
