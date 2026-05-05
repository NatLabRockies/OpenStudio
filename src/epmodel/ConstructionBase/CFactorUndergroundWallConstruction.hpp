/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CFACTORUNDERGROUNDWALLCONSTRUCTION_HPP
#define EPMODEL_CFACTORUNDERGROUNDWALLCONSTRUCTION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CFactorUndergroundWallConstruction_Impl;
  }

  class EPMODEL_API CFactorUndergroundWallConstruction : public ModelObject
  {
   public:
    explicit CFactorUndergroundWallConstruction(const Model& model, double cFactor = 0.1, double height = 0.1);

    virtual ~CFactorUndergroundWallConstruction() override = default;
    CFactorUndergroundWallConstruction(const CFactorUndergroundWallConstruction& other) = default;
    CFactorUndergroundWallConstruction(CFactorUndergroundWallConstruction&& other) = default;
    CFactorUndergroundWallConstruction& operator=(const CFactorUndergroundWallConstruction&) = default;
    CFactorUndergroundWallConstruction& operator=(CFactorUndergroundWallConstruction&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::CFactorUndergroundWallConstruction scalar accessor names/signatures.
    // - Field Mapping: cFactor -> Construction:CfactorUndergroundWall, field C-Factor.
    // - Field Mapping: height -> Construction:CfactorUndergroundWall, field Height.
    // - ForwardTranslator evidence: ForwardTranslateCFactorUndergroundWallConstruction.cpp maps OS cFactor/height
    //   directly to EnergyPlus Construction:CfactorUndergroundWall C-Factor/Height.
    // - TODO(parity): Add non-scalar/relationship APIs if needed in later parity passes.
    double cFactor() const;
    bool setCFactor(double cFactor);

    double height() const;
    bool setHeight(double height);

   protected:
    using ImplType = detail::CFactorUndergroundWallConstruction_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CFactorUndergroundWallConstruction(std::shared_ptr<detail::CFactorUndergroundWallConstruction_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
