/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CFACTORUNDERGROUNDWALLCONSTRUCTION_HPP
#define EPMODEL_CFACTORUNDERGROUNDWALLCONSTRUCTION_HPP

#include "EPModelAPI.hpp"
#include "ConstructionBase/ConstructionBase.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CFactorUndergroundWallConstruction_Impl;
  }

  /** \brief Defines a C-factor underground wall construction.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#constructioncfactorundergroundwall,Construction:CfactorUndergroundWall}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CFactorUndergroundWallConstruction</code>. The
   * <code>cFactor()</code> and <code>height()</code> fields have the same public
   * meaning.
   *
   * \par Known limitations
   * The object exposes only the two EnergyPlus scalar fields; no additional
   * relationship API is provided.
   */
  class EPMODEL_API CFactorUndergroundWallConstruction : public ConstructionBase
  {
   public:
    explicit CFactorUndergroundWallConstruction(const Model& model, double cFactor = 0.1, double height = 0.1);

    virtual ~CFactorUndergroundWallConstruction() override = default;
    CFactorUndergroundWallConstruction(const CFactorUndergroundWallConstruction& other) = default;
    CFactorUndergroundWallConstruction(CFactorUndergroundWallConstruction&& other) = default;
    CFactorUndergroundWallConstruction& operator=(const CFactorUndergroundWallConstruction&) = default;
    CFactorUndergroundWallConstruction& operator=(CFactorUndergroundWallConstruction&&) = default;

    static IddObjectType iddObjectType();

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
