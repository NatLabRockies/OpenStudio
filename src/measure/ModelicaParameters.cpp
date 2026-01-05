/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelicaParameters.hpp"
#include <map>

namespace openstudio {
namespace measure {

  namespace detail {
    class ModelicaParameter_Impl
    {
     public:
      ModelicaParameter_Impl(std::string_view model, std::string_view key, std::string_view value) : m_model(model), m_key(key), m_value(value) {}

      std::string model() const {
        return m_model;
      };

      std::string key() const {
        return m_key;
      };

      std::string value() const {
        return m_value;
      }

      void setValue(std::string_view value) {
        m_value = value;
      }

     private:
      std::string m_model;
      std::string m_key;
      std::string m_value;
    };

    class ModelicaParameters_Impl
    {
     public:
      std::string getParameterValue(const std::string& model, const std::string& key) const {
        const auto it = m_parameters.find({model, key});
        if (it != m_parameters.end()) {
          return it->second.value();
        }

        return "";
      }

      void setParameterValue(const std::string& model, const std::string& key, const std::string& value) {
        const auto it = m_parameters.find({model, key});
        if (it != m_parameters.end()) {
          it->second.setValue(value);
          return;
        }

        m_parameters.emplace(std::pair<std::string, std::string>({model, key}), ModelicaParameter(model, key, value));
      }

      std::vector<ModelicaParameter> getAllParameters() const {
        std::vector<ModelicaParameter> parameters;
        parameters.reserve(m_parameters.size());

        for (const auto& [_, value] : m_parameters) {
          parameters.push_back(value);
        }

        return parameters;
      }

      void clearAllParameters() {
        m_parameters.clear();
      }

     private:
      static std::string keyHash(std::string_view model, std::string_view key) {
        return std::string(model) + std::string(key);
      }

      std::map<std::pair<std::string, std::string>, ModelicaParameter> m_parameters;
    };
  }  // namespace detail

  ModelicaParameter::ModelicaParameter(std::string_view model, std::string_view key, std::string_view value)
    : m_impl{std::make_unique<detail::ModelicaParameter_Impl>(model, key, value)} {};

  std::string ModelicaParameter::model() const {
    return m_impl->model();
  }

  std::string ModelicaParameter::key() const {
    return m_impl->key();
  }

  std::string ModelicaParameter::value() const {
    return m_impl->value();
  }

  void ModelicaParameter::setValue(std::string_view value) {
    m_impl->setValue(value);
  }

  ModelicaParameters::ModelicaParameters() : m_impl{std::make_unique<detail::ModelicaParameters_Impl>()} {};

  std::string ModelicaParameters::getParameterValue(const std::string& model, const std::string& key) const {
    return m_impl->getParameterValue(model, key);
  }

  void ModelicaParameters::setParameterValue(const std::string& model, const std::string& key, const std::string& value) {
    m_impl->setParameterValue(model, key, value);
  }

  std::vector<ModelicaParameter> ModelicaParameters::getAllParameters() const {
    return m_impl->getAllParameters();
  }

  void ModelicaParameters::clearAllParameters() {
    m_impl->clearAllParameters();
  }

}  // namespace measure
}  // namespace openstudio
