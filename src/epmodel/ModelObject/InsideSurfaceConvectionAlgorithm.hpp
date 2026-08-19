/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_INSIDESURFACECONVECTIONALGORITHM_HPP
#define EPMODEL_INSIDESURFACECONVECTIONALGORITHM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class InsideSurfaceConvectionAlgorithm_Impl;
  }

  /** \brief InsideSurfaceConvectionAlgorithm.
   *
   * \par EnergyPlus object
   * \epobject{group-simulation-parameters.html#surfaceconvectionalgorithminside,SurfaceConvectionAlgorithm:Inside}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::InsideSurfaceConvectionAlgorithm</code>. The algorithm methods and valid-value list map directly to the EnergyPlus algorithm field.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API InsideSurfaceConvectionAlgorithm : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~InsideSurfaceConvectionAlgorithm() override = default;
    InsideSurfaceConvectionAlgorithm(const InsideSurfaceConvectionAlgorithm& other) = default;
    InsideSurfaceConvectionAlgorithm(InsideSurfaceConvectionAlgorithm&& other) = default;
    InsideSurfaceConvectionAlgorithm& operator=(const InsideSurfaceConvectionAlgorithm&) = default;
    InsideSurfaceConvectionAlgorithm& operator=(InsideSurfaceConvectionAlgorithm&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> validAlgorithmValues();

    std::string algorithm() const;
    bool isAlgorithmDefaulted() const;
    bool setAlgorithm(const std::string& algorithm);
    void resetAlgorithm();

   protected:
    explicit InsideSurfaceConvectionAlgorithm(const Model& model);

    using ImplType = detail::InsideSurfaceConvectionAlgorithm_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit InsideSurfaceConvectionAlgorithm(std::shared_ptr<detail::InsideSurfaceConvectionAlgorithm_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
