/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONSUBCOOLERMECHANICAL_HPP
#define EPMODEL_REFRIGERATIONSUBCOOLERMECHANICAL_HPP

#include "EPModelAPI.hpp"
#include "RefrigerationSubcooler.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RefrigerationSubcoolerMechanical_Impl;
  }

  class EPMODEL_API RefrigerationSubcoolerMechanical : public RefrigerationSubcooler
  {
   public:
    explicit RefrigerationSubcoolerMechanical(const Model& model);

    virtual ~RefrigerationSubcoolerMechanical() override = default;
    RefrigerationSubcoolerMechanical(const RefrigerationSubcoolerMechanical& other) = default;
    RefrigerationSubcoolerMechanical(RefrigerationSubcoolerMechanical&& other) = default;
    RefrigerationSubcoolerMechanical& operator=(const RefrigerationSubcoolerMechanical&) = default;
    RefrigerationSubcoolerMechanical& operator=(RefrigerationSubcoolerMechanical&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<double> outletControlTemperature() const;

    bool setOutletControlTemperature(double value);
    void resetOutletControlTemperature();

   protected:
    using ImplType = detail::RefrigerationSubcoolerMechanical_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class detail::RefrigerationSubcoolerMechanical_Impl;

    explicit RefrigerationSubcoolerMechanical(std::shared_ptr<detail::RefrigerationSubcoolerMechanical_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
