/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEELECTRIC_HPP
#define EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEELECTRIC_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACBaseboardRadiantConvectiveElectric_Impl;
  }

  class EPMODEL_API ZoneHVACBaseboardRadiantConvectiveElectric : public ModelObject
  {
   public:
    explicit ZoneHVACBaseboardRadiantConvectiveElectric(const Model& model);

    virtual ~ZoneHVACBaseboardRadiantConvectiveElectric() override = default;
    ZoneHVACBaseboardRadiantConvectiveElectric(const ZoneHVACBaseboardRadiantConvectiveElectric& other) = default;
    ZoneHVACBaseboardRadiantConvectiveElectric(ZoneHVACBaseboardRadiantConvectiveElectric&& other) = default;
    ZoneHVACBaseboardRadiantConvectiveElectric& operator=(const ZoneHVACBaseboardRadiantConvectiveElectric&) = default;
    ZoneHVACBaseboardRadiantConvectiveElectric& operator=(ZoneHVACBaseboardRadiantConvectiveElectric&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatingDesignCapacityMethodValues();

    // Schema Alignment Notes:
    // - API: heatingDesignCapacityMethod/heatingDesignCapacity/heatingDesignCapacityPerFloorArea/fractionofAutosizedHeatingDesignCapacity
    //   map to EnergyPlus ZoneHVAC:Baseboard:RadiantConvective:Electric Heating Design Capacity group fields via ForwardTranslateZoneHVACBaseboardRadiantConvectiveElectric.cpp.
    // - API: efficiency/fractionRadiant/fractionofRadiantEnergyIncidentonPeople map to the corresponding Efficiency, Fraction Radiant and
    //   Fraction of Radiant Energy Incident on People fields while Availability Schedule Name, Heating Coil Name and the extensible surface entries
    //   remain relationship-only targets until dedicated APIs exist.
    std::string heatingDesignCapacityMethod() const;
    bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);

    boost::optional<double> heatingDesignCapacity() const;
    bool isHeatingDesignCapacityAutosized() const;
    bool setHeatingDesignCapacity(double heatingDesignCapacity);
    void autosizeHeatingDesignCapacity();

    double heatingDesignCapacityPerFloorArea() const;
    bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);

    double fractionofAutosizedHeatingDesignCapacity() const;
    bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);

    double efficiency() const;
    bool setEfficiency(double efficiency);

    double fractionRadiant() const;
    bool setFractionRadiant(double fractionRadiant);

    double fractionofRadiantEnergyIncidentonPeople() const;
    bool setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople);

   protected:
    using ImplType = detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACBaseboardRadiantConvectiveElectric(std::shared_ptr<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
