/*
 * File Name: id_lookup.h
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/30
 *
 */
#pragma once

#include <feature.h>
#include <glog/logging.h>
#include <indoor_features.h>

#include <map>
#include <mutex>
#include <nlohmann/json.hpp>
#include <string>

namespace indoor_json {

void IdLookupClearAll();

template <typename T>
class IdLookup {
 private:
  std::map<std::string, std::shared_ptr<T>> id_2_feature_;
  std::map<std::shared_ptr<T>, nlohmann::json> feature_2_json_;

  IdLookup() = default;
  static IdLookup* instance_;

 public:
  static IdLookup& Ins() {
    if (instance_ == nullptr) {
      instance_ = new IdLookup();
    }
    return *instance_;
  }

  void Register(const std::string& id, const std::shared_ptr<T>& feature,
                const nlohmann::json json) {
    id_2_feature_[id] = feature;
    feature_2_json_[feature] = json;
  };

  std::shared_ptr<T> Id2Ptr(const std::string& id) { return id_2_feature_[id]; }

  nlohmann::json Feature2Json(const std::shared_ptr<T>& feature) {
    return feature_2_json_[feature];
  }

  void Clear() {
    id_2_feature_.clear();
    feature_2_json_.clear();
  }
};

}  // namespace indoor_json