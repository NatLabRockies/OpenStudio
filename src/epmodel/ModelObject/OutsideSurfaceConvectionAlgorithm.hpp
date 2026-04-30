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

  class EPMODEL_API OutsideSurfaceConvectionAlgorithm : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    explicit OutsideSurfaceConvectionAlgorithm(const Model& model);

    virtual ~OutsideSurfaceConvectionAlgorithm() override = default;
    OutsideSurfaceConvectionAlgorithm(const OutsideSurfaceConvectionAlgorithm& other) = default;
    OutsideSurfaceConvectionAlgorithm(OutsideSurfaceConvectionAlgorithm&& other) = default;
    OutsideSurfaceConvectionAlgorithm& operator=(const OutsideSurfaceConvectionAlgorithm&) = default;
    OutsideSurfaceConvectionAlgorithm& operator=(OutsideSurfaceConvectionAlgorithm&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: Algorithm maps directly to E+ SurfaceConvectionAlgorithm:Outside field A1.
    static std::vector<std::string> validAlgorithmValues();

    /** @name Algorithm field */
    //@{
    std::string algorithm() const;
    bool isAlgorithmDefaulted() const;
    bool setAlgorithm(const std::string& algorithm);
    void resetAlgorithm();
    //@}

   protected:
    using ImplType = detail::OutsideSurfaceConvectionAlgorithm_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutsideSurfaceConvectionAlgorithm(std::shared_ptr<detail::OutsideSurfaceConvectionAlgorithm_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
