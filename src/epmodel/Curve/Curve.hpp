/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVE_HPP
#define EPMODEL_CURVE_HPP

#include "EPModelAPI.hpp"
#include "ResourceObject/ResourceObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Curve_Impl;
  }

  class EPMODEL_API Curve : public ResourceObject
  {
   public:
    virtual ~Curve() override = default;
    Curve(const Curve& other) = default;
    Curve(Curve&& other) = default;
    Curve& operator=(const Curve&) = default;
    Curve& operator=(Curve&&) = default;

    int numVariables() const;

    double evaluate(const std::vector<double>& x) const;
    double evaluate(double x) const;
    double evaluate(double x, double y) const;
    double evaluate(double x, double y, double z) const;
    double evaluate(double w, double x, double y, double z) const;
    double evaluate(double v, double w, double x, double y, double z) const;

   protected:
    using ImplType = detail::Curve_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    Curve(IddObjectType type, const Model& model);
    explicit Curve(std::shared_ptr<ImplType> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
