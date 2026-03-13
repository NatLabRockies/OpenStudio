/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DUCTLOSSCONDUCTION_HPP
#define EPMODEL_DUCTLOSSCONDUCTION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DuctLossConduction_Impl;
  }

  class EPMODEL_API DuctLossConduction : public ModelObject
  {
   public:
    explicit DuctLossConduction(const Model& model);

    virtual ~DuctLossConduction() override = default;
    DuctLossConduction(const DuctLossConduction& other) = default;
    DuctLossConduction(DuctLossConduction&& other) = default;
    DuctLossConduction& operator=(const DuctLossConduction&) = default;
    DuctLossConduction& operator=(DuctLossConduction&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> environmentTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: environmentType maps directly to EnergyPlus Duct:Loss:Conduction Environment Type.
    // - Field Mapping: AirLoopHVAC Name, AirflowNetwork:Distribution:Linkage Name, Ambient Zone Name, Ambient Temperature Schedule Name,
    //   and Ambient Humidity Ratio Schedule Name are relationship-like object-list fields and are excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs incrementally after scalar saturation.

    /** @name Environment Type Accessors */
    //@{
    std::string environmentType() const;
    bool setEnvironmentType(const std::string& environmentType);
    bool isEnvironmentTypeDefaulted() const;
    void resetEnvironmentType();
    //@}

   protected:
    using ImplType = detail::DuctLossConduction_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DuctLossConduction(std::shared_ptr<detail::DuctLossConduction_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
