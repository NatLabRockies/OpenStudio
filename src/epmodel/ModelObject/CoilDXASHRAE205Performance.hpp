/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILDXASHRAE205PERFORMANCE_HPP
#define EPMODEL_COILDXASHRAE205PERFORMANCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilDXASHRAE205Performance_Impl;
  }

  class EPMODEL_API CoilDXASHRAE205Performance : public ModelObject
  {
   public:
    explicit CoilDXASHRAE205Performance(const Model& model);

    virtual ~CoilDXASHRAE205Performance() override = default;
    CoilDXASHRAE205Performance(const CoilDXASHRAE205Performance& other) = default;
    CoilDXASHRAE205Performance(CoilDXASHRAE205Performance&& other) = default;
    CoilDXASHRAE205Performance& operator=(const CoilDXASHRAE205Performance&) = default;
    CoilDXASHRAE205Performance& operator=(CoilDXASHRAE205Performance&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> performanceInterpolationMethodValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class and accessor names.
    // - Field Mapping: Scalar APIs map directly to Coil:DX:ASHRAE205:Performance fields.
    // - Field Mapping: This object has no relationship-like fields; all non-name fields are included.
    // - TODO(parity): Extend beyond scalar accessors only if future IDD revisions add relationship fields.

    // Representation file name
    std::string representationFileName() const;
    bool setRepresentationFileName(const std::string& representationFileName);

    // Performance interpolation method
    std::string performanceInterpolationMethod() const;
    bool isPerformanceInterpolationMethodDefaulted() const;
    bool setPerformanceInterpolationMethod(const std::string& performanceInterpolationMethod);
    void resetPerformanceInterpolationMethod();

    // Rated total cooling capacity
    boost::optional<double> ratedTotalCoolingCapacity() const;
    bool isRatedTotalCoolingCapacityAutosized() const;
    bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
    void resetRatedTotalCoolingCapacity();
    void autosizeRatedTotalCoolingCapacity();

    // Rated steady-state heating capacity
    boost::optional<double> ratedSteadyStateHeatingCapacity() const;
    bool isRatedSteadyStateHeatingCapacityAutosized() const;
    bool setRatedSteadyStateHeatingCapacity(double ratedSteadyStateHeatingCapacity);
    void resetRatedSteadyStateHeatingCapacity();
    void autosizeRatedSteadyStateHeatingCapacity();

   protected:
    using ImplType = detail::CoilDXASHRAE205Performance_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilDXASHRAE205Performance(std::shared_ptr<detail::CoilDXASHRAE205Performance_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
