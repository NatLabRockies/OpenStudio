/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTSIDESURFACECONVECTIONALGORITHM_HPP
#define EPMODEL_OUTSIDESURFACECONVECTIONALGORITHM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutsideSurfaceConvectionAlgorithm_Impl;
  }

  /** \brief OutsideSurfaceConvectionAlgorithm.
   *
   * \par EnergyPlus object
   * \epobject{group-simulation-parameters.html#surfaceconvectionalgorithmoutside,SurfaceConvectionAlgorithm:Outside}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutsideSurfaceConvectionAlgorithm</code>. The algorithm methods and valid-value list map directly to the EnergyPlus algorithm field.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutsideSurfaceConvectionAlgorithm : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~OutsideSurfaceConvectionAlgorithm() override = default;
    OutsideSurfaceConvectionAlgorithm(const OutsideSurfaceConvectionAlgorithm& other) = default;
    OutsideSurfaceConvectionAlgorithm(OutsideSurfaceConvectionAlgorithm&& other) = default;
    OutsideSurfaceConvectionAlgorithm& operator=(const OutsideSurfaceConvectionAlgorithm&) = default;
    OutsideSurfaceConvectionAlgorithm& operator=(OutsideSurfaceConvectionAlgorithm&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> validAlgorithmValues();

    /** @name Algorithm field */
    //@{
    std::string algorithm() const;
    bool isAlgorithmDefaulted() const;
    bool setAlgorithm(const std::string& algorithm);
    void resetAlgorithm();
    //@}

   protected:
    explicit OutsideSurfaceConvectionAlgorithm(const Model& model);

    using ImplType = detail::OutsideSurfaceConvectionAlgorithm_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutsideSurfaceConvectionAlgorithm(std::shared_ptr<detail::OutsideSurfaceConvectionAlgorithm_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
