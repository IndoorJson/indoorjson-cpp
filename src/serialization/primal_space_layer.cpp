/*
 * File Name: primal_space_layer.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/25
 *
 */
#include <serialization.h>

namespace indoor_json {

void to_json(nlohmann::json &j, const PrimalSpaceLayer &layer) {
  j = {{"spaces", layer.spaces}, {"boundaries", layer.boundaries}};
  to_json(j, static_cast<const Feature &>(layer));
}

void from_json(const nlohmann::json &j, PrimalSpaceLayer &layer) {
  j.at("spaces").get_to(layer.spaces);
  j.at("boundaries").get_to(layer.boundaries);
  from_json(j, static_cast<Feature &>(layer));
}

}  // namespace indoor_json
