/*
 * File Name: edge.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/25
 *
 */
#include <serialization.h>

namespace indoor_json {

void to_json(nlohmann::json &j, const Edge &edge) {
  j = {{"boundary", edge.boundary},
       {"nodes", edge.nodes},
       {"weight", edge.weight},
       {"geom", edge.geom}};
  to_json(j, static_cast<const Feature &>(edge));
}

void from_json(const nlohmann::json &j, Edge &edge) {
  j.at("geom").get_to(edge.geom);
  j.at("weight").get_to(edge.weight);
  j.at("nodes").get_to(edge.nodes);
  j.at("boundary").get_to(edge.boundary);
  from_json(j, static_cast<Feature &>(edge));
}

}  // namespace indoor_json
