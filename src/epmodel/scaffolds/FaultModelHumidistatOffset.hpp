/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELHUMIDISTATOFFSET_HPP
#define EPMODEL_FAULTMODELHUMIDISTATOFFSET_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FaultModelHumidistatOffset_Impl;
  }

  class EPMODEL_API FaultModelHumidistatOffset : public ModelObject
  {
   public:
    explicit FaultModelHumidistatOffset(const Model& model);

    virtual ~FaultModelHumidistatOffset() override = default;
    FaultModelHumidistatOffset(const FaultModelHumidistatOffset& other) = default;
    FaultModelHumidistatOffset(FaultModelHumidistatOffset&& other) = default;
    FaultModelHumidistatOffset& operator=(const FaultModelHumidistatOffset&) = default;
    FaultModelHumidistatOffset& operator=(FaultModelHumidistatOffset&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> humidistatOffsetTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: humidistatOffsetType maps directly to EnergyPlus FaultModel:HumidistatOffset / Humidistat Offset Type.
    // - Field Mapping: referenceHumidistatOffset maps directly to EnergyPlus FaultModel:HumidistatOffset / Reference Humidistat Offset.
    // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
    // - Field Mapping: Humidistat Name, Availability Schedule Name, Severity Schedule Name, and Related Thermostat Offset Fault Name are
    //   relationship-like object-list fields and intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
    std::string humidistatOffsetType() const;
    bool isHumidistatOffsetTypeDefaulted() const;
    bool setHumidistatOffsetType(const std::string& humidistatOffsetType);
    void resetHumidistatOffsetType();

    double referenceHumidistatOffset() const;
    bool isReferenceHumidistatOffsetDefaulted() const;
    bool setReferenceHumidistatOffset(double referenceHumidistatOffset);
    void resetReferenceHumidistatOffset();

   protected:
    using ImplType = detail::FaultModelHumidistatOffset_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FaultModelHumidistatOffset(std::shared_ptr<detail::FaultModelHumidistatOffset_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
