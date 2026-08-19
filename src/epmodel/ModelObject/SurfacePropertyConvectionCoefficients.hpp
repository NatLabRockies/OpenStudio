/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYCONVECTIONCOEFFICIENTS_HPP
#define EPMODEL_SURFACEPROPERTYCONVECTIONCOEFFICIENTS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertyConvectionCoefficients_Impl;
  }

  /** \brief SurfacePropertyConvectionCoefficients.
   *
   * \par EnergyPlus object
   * \epobject{group-advanced-surface-concepts.html#surfacepropertyconvectioncoefficients,SurfaceProperty:ConvectionCoefficients}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SurfacePropertyConvectionCoefficients</code>. <b>Changed:</b> EPModel exposes direct construction from <code>Model</code>; Model construction requires a surface, subsurface, or internal-mass object. The scalar convection-coefficient fields map directly to EnergyPlus; surface and schedule relationships are not available.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SurfacePropertyConvectionCoefficients : public ModelObject
  {
   public:
    explicit SurfacePropertyConvectionCoefficients(const Model& model);

    virtual ~SurfacePropertyConvectionCoefficients() override = default;
    SurfacePropertyConvectionCoefficients(const SurfacePropertyConvectionCoefficients& other) = default;
    SurfacePropertyConvectionCoefficients(SurfacePropertyConvectionCoefficients&& other) = default;
    SurfacePropertyConvectionCoefficients& operator=(const SurfacePropertyConvectionCoefficients&) = default;
    SurfacePropertyConvectionCoefficients& operator=(SurfacePropertyConvectionCoefficients&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> convectionCoefficient1LocationValues();
    static std::vector<std::string> convectionCoefficient1TypeValues();
    static std::vector<std::string> convectionCoefficient2LocationValues();
    static std::vector<std::string> convectionCoefficient2TypeValues();
    boost::optional<std::string> convectionCoefficient1Location() const;
    bool setConvectionCoefficient1Location(const std::string& convectionCoefficient1Location);
    void resetConvectionCoefficient1Location();

    boost::optional<std::string> convectionCoefficient1Type() const;
    bool setConvectionCoefficient1Type(const std::string& convectionCoefficient1Type);
    void resetConvectionCoefficient1Type();

    boost::optional<double> convectionCoefficient1() const;
    bool setConvectionCoefficient1(double convectionCoefficient1);
    void resetConvectionCoefficient1();

    boost::optional<std::string> convectionCoefficient2Location() const;
    bool setConvectionCoefficient2Location(const std::string& convectionCoefficient2Location);
    void resetConvectionCoefficient2Location();

    boost::optional<std::string> convectionCoefficient2Type() const;
    bool setConvectionCoefficient2Type(const std::string& convectionCoefficient2Type);
    void resetConvectionCoefficient2Type();

    boost::optional<double> convectionCoefficient2() const;
    bool setConvectionCoefficient2(double convectionCoefficient2);
    void resetConvectionCoefficient2();

   protected:
    using ImplType = detail::SurfacePropertyConvectionCoefficients_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyConvectionCoefficients(std::shared_ptr<detail::SurfacePropertyConvectionCoefficients_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
