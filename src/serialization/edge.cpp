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

using json = nlohmann::json;

void to_json(json &j, const Edge &edge) {
  to_json(j, static_cast<const Feature &>(edge));

  if (edge.geom != nullptr) {
    json j_geom;
    to_json(j_geom, edge.geom);
    j.push_back({"geom", j_geom});
  } else {
    j.push_back({"geom", nullptr});
  }

  if (auto boundary = edge.boundary.lock())
    j.push_back({"boundary", boundary->id});
  else
    j.push_back({"boundary", nullptr});

  json j_nodes = json::array();
  for (const auto &pnode : edge.nodes) {
    if (auto node = pnode.lock())
      j_nodes.push_back(node->id);
    else
      j_nodes.push_back(nullptr);
  }
  j.push_back({"nodes", j_nodes});

  j.push_back({"weight", edge.weight});
}

void from_json(const json &j, Edge &edge) {
  from_json(j, static_cast<Feature &>(edge));

  if (j.contains("geom")) {
    std::string wkt = j.at("geom").get<std::string>();
    from_json(wkt, edge.geom);
  }

  if (j.contains("weight")) j.at("weight").get_to(edge.weight);
}

}  // namespace indoor_json
