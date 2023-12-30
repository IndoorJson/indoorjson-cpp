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
  to_json(j, static_cast<const Feature&>(indoor_features));
}

void from_json(const json& j, IndoorFeatures& indoor_features) {
  j.at("layers").get_to(indoor_features.layers);
  j.at("connections").get_to(indoor_features.connections);
  from_json(j, static_cast<Feature&>(indoor_features));
}

}  // namespace indoor_json