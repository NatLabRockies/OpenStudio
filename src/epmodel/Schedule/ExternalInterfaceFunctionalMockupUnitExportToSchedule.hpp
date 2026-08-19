/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOSCHEDULE_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOSCHEDULE_HPP

#include "EPModelAPI.hpp"
#include "Schedule/Schedule.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl;
  }

  /** \brief Provides a schedule value exported from EnergyPlus to an FMU.
   *
   * \par EnergyPlus object
   * \epobject{group-externalinterface.html#externalinterfacefunctionalmockupunitexporttoschedule,ExternalInterface:FunctionalMockupUnitExport:To:Schedule}
   *
   * \par Important behavior
   * The initial value is used by EnergyPlus during sizing and warm-up before
   * FMU values are available.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ExternalInterfaceFunctionalMockupUnitExportToSchedule</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API ExternalInterfaceFunctionalMockupUnitExportToSchedule : public Schedule
  {
   public:
    explicit ExternalInterfaceFunctionalMockupUnitExportToSchedule(const Model& model, const std::string& fMUVariableName);

    explicit ExternalInterfaceFunctionalMockupUnitExportToSchedule(const Model& model, const std::string& fMUVariableName, double initialValue);

    virtual ~ExternalInterfaceFunctionalMockupUnitExportToSchedule() override = default;
    ExternalInterfaceFunctionalMockupUnitExportToSchedule(const ExternalInterfaceFunctionalMockupUnitExportToSchedule& other) = default;
    ExternalInterfaceFunctionalMockupUnitExportToSchedule(ExternalInterfaceFunctionalMockupUnitExportToSchedule&& other) = default;
    ExternalInterfaceFunctionalMockupUnitExportToSchedule& operator=(const ExternalInterfaceFunctionalMockupUnitExportToSchedule&) = default;
    ExternalInterfaceFunctionalMockupUnitExportToSchedule& operator=(ExternalInterfaceFunctionalMockupUnitExportToSchedule&&) = default;

    static IddObjectType iddObjectType();

    /** @name FMU Variable Name */
    //@{
    std::string fMUVariableName() const;
    bool setFMUVariableName(const std::string& fMUVariableName);
    //@}

    /** @name Initial Value */
    //@{
    boost::optional<double> initialValue() const;
    bool setInitialValue(double initialValue);
    //@}

   protected:
    using ImplType = detail::ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceFunctionalMockupUnitExportToSchedule(
      std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
