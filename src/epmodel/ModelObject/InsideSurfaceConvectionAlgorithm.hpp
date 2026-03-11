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

  class EPMODEL_API InsideSurfaceConvectionAlgorithm : public ModelObject
  {
   public:
    explicit InsideSurfaceConvectionAlgorithm(const Model& model);

    virtual ~InsideSurfaceConvectionAlgorithm() override = default;
    InsideSurfaceConvectionAlgorithm(const InsideSurfaceConvectionAlgorithm& other) = default;
    InsideSurfaceConvectionAlgorithm(InsideSurfaceConvectionAlgorithm&& other) = default;
    InsideSurfaceConvectionAlgorithm& operator=(const InsideSurfaceConvectionAlgorithm&) = default;
    InsideSurfaceConvectionAlgorithm& operator=(InsideSurfaceConvectionAlgorithm&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: Algorithm maps directly to E+ SurfaceConvectionAlgorithm:Inside field A1.
    static std::vector<std::string> validAlgorithmValues();

    std::string algorithm() const;
    bool isAlgorithmDefaulted() const;
    bool setAlgorithm(const std::string& algorithm);
    void resetAlgorithm();

   protected:
    using ImplType = detail::InsideSurfaceConvectionAlgorithm_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit InsideSurfaceConvectionAlgorithm(std::shared_ptr<detail::InsideSurfaceConvectionAlgorithm_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
