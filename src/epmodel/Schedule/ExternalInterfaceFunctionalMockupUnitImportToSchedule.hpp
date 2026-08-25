/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOSCHEDULE_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOSCHEDULE_HPP

#include "EPModelAPI.hpp"
#include "Schedule/Schedule.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl;
  }

  /** \brief Provides a schedule value received from an FMU.
   *
   * \par EnergyPlus object
   * \epobject{group-externalinterface.html#externalinterfacefunctionalmockupunitimporttoschedule,ExternalInterface:FunctionalMockupUnitImport:To:Schedule}
   *
   * \par Important behavior
   * The initial value is used by EnergyPlus on its first call before an FMU
   * value is available.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ExternalInterfaceFunctionalMockupUnitImportToSchedule</code>.
   *
   * - <b>Not yet available:</b> The constructor that accepts an
   *   <code>ExternalInterfaceFunctionalMockupUnitImport</code>, FMU instance
   *   name, FMU variable name, and initial value.
   * - <b>Not yet available:</b> <code>fMUFile()</code> and
   *   <code>setFMUFile(...)</code>. The EPModel wrapper cannot configure the
   *   EnergyPlus <code>FMU File Name</code> object-list relationship through a
   *   typed method.
   *
   * \par Known limitations
   * A complete FMU import-to-schedule relationship cannot be created or
   * changed using only this wrapper's public typed API because the FMU file
   * relationship is not exposed.
   */
  class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImportToSchedule : public Schedule
  {
   public:
    explicit ExternalInterfaceFunctionalMockupUnitImportToSchedule(const Model& model);

    virtual ~ExternalInterfaceFunctionalMockupUnitImportToSchedule() override = default;
    ExternalInterfaceFunctionalMockupUnitImportToSchedule(const ExternalInterfaceFunctionalMockupUnitImportToSchedule& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportToSchedule(ExternalInterfaceFunctionalMockupUnitImportToSchedule&& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportToSchedule& operator=(const ExternalInterfaceFunctionalMockupUnitImportToSchedule&) = default;
    ExternalInterfaceFunctionalMockupUnitImportToSchedule& operator=(ExternalInterfaceFunctionalMockupUnitImportToSchedule&&) = default;

    static IddObjectType iddObjectType();

    // FMU Instance Name accessors
    std::string fMUInstanceName() const;
    bool setFMUInstanceName(const std::string& fMUInstanceName);

    // FMU Variable Name accessors
    std::string fMUVariableName() const;
    bool setFMUVariableName(const std::string& fMUVariableName);

    // Initial Value accessors
    double initialValue() const;
    bool setInitialValue(double initialValue);

   protected:
    using ImplType = detail::ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceFunctionalMockupUnitImportToSchedule(
      std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
