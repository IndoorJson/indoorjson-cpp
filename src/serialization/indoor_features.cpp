/*
 * File Name: indoor_features.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/25
 *
 */

#include <serialization.h>
namespace indoor_json {

using json = nlohmann::json;

void to_json(json& j, const IndoorFeatures& indoor_features) {
  j = {{"layers", indoor_features.layers},
       {"connections", indoor_features.connections}};
  json base;
  to_json(base, static_cast<const Feature&>(indoor_features));
  j.merge_patch(base);
}
void to_json(json& j, const IndoorFeaturesPtr& indoor_features) {
  to_json(j, *indoor_features.get());
}
void from_json(const json& j, IndoorFeatures& indoor_features) {
  j.at("layers").get_to(indoor_features.layers);
  j.at("connections").get_to(indoor_features.connections);
}
void from_json(const json& j, IndoorFeaturesPtr& indoor_features) {
  indoor_features = std::make_shared<IndoorFeatures>();
  from_json(j, *indoor_features.get());
}

}  // namespace indoor_json