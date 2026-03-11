/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "UtilityCostComputation.hpp"
#include "UtilityCostComputation_Impl.hpp"

#include "Model.hpp"

namespace openstudio {
namespace epmodel {

  UtilityCostComputation::UtilityCostComputation(const Model& model) : ModelObject(UtilityCostComputation::iddObjectType(), model) {}

  UtilityCostComputation::UtilityCostComputation(std::shared_ptr<detail::UtilityCostComputation_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType UtilityCostComputation::iddObjectType() {
    static const IddObjectType type("UtilityCost_Computation");
    return type;
  }

}  // namespace epmodel
}  // namespace openstudio
