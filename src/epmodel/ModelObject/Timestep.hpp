/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TIMESTEP_HPP
#define EPMODEL_TIMESTEP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Timestep_Impl;
  }

  /** \brief Timestep.
   *
   * \par EnergyPlus object
   * \epobject{group-simulation-parameters.html#timestep,Timestep}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::Timestep</code>. The number-of-timesteps-per-hour field maps directly to EnergyPlus.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API Timestep : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~Timestep() override = default;
    Timestep(const Timestep& other) = default;
    Timestep(Timestep&& other) = default;
    Timestep& operator=(const Timestep&) = default;
    Timestep& operator=(Timestep&&) = default;

    static IddObjectType iddObjectType();
    int numberOfTimestepsPerHour() const;

    bool setNumberOfTimestepsPerHour(int numberOfTimestepsPerHour);

    bool isNumberOfTimestepsPerHourDefaulted() const;

    void resetNumberOfTimestepsPerHour();

   protected:
    explicit Timestep(const Model& model);

    using ImplType = detail::Timestep_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Timestep(std::shared_ptr<detail::Timestep_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_TIMESTEP_HPP
