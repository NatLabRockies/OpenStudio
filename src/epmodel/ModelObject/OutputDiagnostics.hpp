/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTDIAGNOSTICS_HPP
#define EPMODEL_OUTPUTDIAGNOSTICS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputDiagnostics_Impl;
  }

  /** \brief OutputDiagnostics.
   *
   * \par EnergyPlus object
   * \epobject{group-simulation-parameters.html#outputdiagnostics,Output:Diagnostics}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputDiagnostics</code>. This object contains extensible diagnostic keys. EPModel currently exposes no public key-list mutation or query methods.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputDiagnostics : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~OutputDiagnostics() override = default;
    OutputDiagnostics(const OutputDiagnostics& other) = default;
    OutputDiagnostics(OutputDiagnostics&& other) = default;
    OutputDiagnostics& operator=(const OutputDiagnostics&) = default;
    OutputDiagnostics& operator=(OutputDiagnostics&&) = default;

    static IddObjectType iddObjectType();

   protected:
    explicit OutputDiagnostics(const Model& model);

    using ImplType = detail::OutputDiagnostics_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputDiagnostics(std::shared_ptr<detail::OutputDiagnostics_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
