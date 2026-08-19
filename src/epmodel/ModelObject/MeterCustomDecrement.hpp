/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_METERCUSTOMDECREMENT_HPP
#define EPMODEL_METERCUSTOMDECREMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class MeterCustomDecrement_Impl;
  }

  /** \brief MeterCustomDecrement.
   *
   * \par EnergyPlus object
   * \epobject{group-simulation-parameters.html#metercustomdecrement,Meter:CustomDecrement}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::MeterCustomDecrement</code>. The resource type and source-meter name are exposed. Model's extensible key/output-variable groups are not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API MeterCustomDecrement : public ModelObject
  {
   public:
    explicit MeterCustomDecrement(const Model& model, const std::string& sourceMeterName);

    virtual ~MeterCustomDecrement() override = default;
    MeterCustomDecrement(const MeterCustomDecrement& other) = default;
    MeterCustomDecrement(MeterCustomDecrement&& other) = default;
    MeterCustomDecrement& operator=(const MeterCustomDecrement&) = default;
    MeterCustomDecrement& operator=(MeterCustomDecrement&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fuelTypeValues();
    boost::optional<std::string> fuelType() const;
    bool setFuelType(const std::string& fuelType);
    void resetFuelType();

    std::string sourceMeterName() const;
    bool setSourceMeterName(const std::string& sourceMeterName);

   protected:
    using ImplType = detail::MeterCustomDecrement_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit MeterCustomDecrement(std::shared_ptr<detail::MeterCustomDecrement_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
