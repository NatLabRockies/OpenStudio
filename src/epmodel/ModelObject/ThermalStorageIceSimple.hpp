/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALSTORAGEICESIMPLE_HPP
#define EPMODEL_THERMALSTORAGEICESIMPLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermalStorageIceSimple_Impl;
  }

  class EPMODEL_API ThermalStorageIceSimple : public ModelObject
  {
   public:
    explicit ThermalStorageIceSimple(const Model& model);

    virtual ~ThermalStorageIceSimple() override = default;
    ThermalStorageIceSimple(const ThermalStorageIceSimple& other) = default;
    ThermalStorageIceSimple(ThermalStorageIceSimple&& other) = default;
    ThermalStorageIceSimple& operator=(const ThermalStorageIceSimple&) = default;
    ThermalStorageIceSimple& operator=(ThermalStorageIceSimple&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> iceStorageTypeValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so IDD-derived ThermalStorageIceSimple naming is preserved.
    // - Field Mapping: iceStorageType() targets the EnergyPlus Ice Storage Type choice on ThermalStorage:Ice:Simple.
    // - Field Mapping: capacity(), its autosize helpers, and optional getter map to the EnergyPlus Capacity field (autosizable).
    // - Field Mapping: Inlet Node Name, Outlet Node Name, and Thermal Storage Sizing Object Name are relationship-like node/object links that are intentionally left out of this scalar-only scaffold.
    // - TODO(parity): Add node/link helpers once scalar field saturation for this type is complete.

    boost::optional<double> capacity() const;
    bool setCapacity(double capacity);
    bool isCapacityAutosized() const;
    void autosizeCapacity();

    std::string iceStorageType() const;
    bool setIceStorageType(const std::string& iceStorageType);

   protected:
    using ImplType = detail::ThermalStorageIceSimple_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermalStorageIceSimple(std::shared_ptr<detail::ThermalStorageIceSimple_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
