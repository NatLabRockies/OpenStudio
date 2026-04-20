/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALSTORAGESIZING_HPP
#define EPMODEL_THERMALSTORAGESIZING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermalStorageSizing_Impl;
  }

  class EPMODEL_API ThermalStorageSizing : public ModelObject
  {
   public:
    explicit ThermalStorageSizing(const Model& model);

    virtual ~ThermalStorageSizing() override = default;
    ThermalStorageSizing(const ThermalStorageSizing& other) = default;
    ThermalStorageSizing(ThermalStorageSizing&& other) = default;
    ThermalStorageSizing& operator=(const ThermalStorageSizing&) = default;
    ThermalStorageSizing& operator=(ThermalStorageSizing&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Scalar getters mirror the EnergyPlus ThermalStorage:Sizing on-peak window and sizing factor fields.
    // - Field Mapping: onPeakPeriodStartTime()/onPeakPeriodEndTime() map to the "On Peak Period Start Time" and
    //   "On Peak Period End Time" fields, and sizingFactor()/isSizingFactorDefaulted()/resetSizingFactor() map to
    //   the "Sizing Factor" field (default 1.0) on ThermalStorage:Sizing.
    // - Field Mapping: The Name field is an EnergyPlus reference to another ThermalStorageSizing object and is intentionally
    //   excluded (relationship-like reference) from this scalar-only scaffold.
    // - TODO(parity): Surface additional relationship helpers once ThermalStorageSizing is part of a dedicated model counterpart.

    double onPeakPeriodStartTime() const;
    bool setOnPeakPeriodStartTime(double onPeakPeriodStartTime);

    double onPeakPeriodEndTime() const;
    bool setOnPeakPeriodEndTime(double onPeakPeriodEndTime);

    double sizingFactor() const;
    bool setSizingFactor(double sizingFactor);
    bool isSizingFactorDefaulted() const;
    void resetSizingFactor();

   protected:
    using ImplType = detail::ThermalStorageSizing_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermalStorageSizing(std::shared_ptr<detail::ThermalStorageSizing_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
