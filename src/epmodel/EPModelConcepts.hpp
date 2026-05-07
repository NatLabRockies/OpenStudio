/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONCEPTS_HPP
#define EPMODEL_CONCEPTS_HPP

#ifndef SWIG
#  include <concepts>
#endif

namespace openstudio {
namespace epmodel {

#ifndef SWIG

  class ModelObject;

  template <class T>
  concept AnyModelObject = std::derived_from<T, ModelObject>;

  template <class T>
  concept AnyChildOfModelObject = AnyModelObject<T> && !std::same_as<ModelObject, T>;

  template <typename T>
  concept ConcreteModelObject = AnyChildOfModelObject<T> && requires {
    T::iddObjectType();  // required static member function
  };

  template <typename T>
  constexpr bool is_concrete_v = ConcreteModelObject<T>;

  template <typename T>
  concept UniqueModelObject = ConcreteModelObject<T> && requires {
    { T::is_unique } -> std::convertible_to<bool>;
    requires T::is_unique;
  };

  template <typename T>
  constexpr bool is_unique_model_object_v = UniqueModelObject<T>;

  template <typename T>
  concept TransientModelObject = AnyChildOfModelObject<T> && requires {
    { T::is_transient } -> std::convertible_to<bool>;
    requires T::is_transient;
  };

  template <typename T>
  constexpr bool is_transient_model_object_v = TransientModelObject<T>;

#else
#  define AnyModelObject typename
#  define AnyChildOfModelObject typename
#  define ConcreteModelObject typename
#  define UniqueModelObject typename
#  define TransientModelObject typename
#endif  // SWIG

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_CONCEPTS_HPP
