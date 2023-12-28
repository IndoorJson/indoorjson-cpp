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
  json base;
  to_json(base, static_cast<const Feature &>(edge));
  j.merge_patch(base);

  if (edge.geom != nullptr) {
    json j_geom;
    to_json(j_geom, edge.geom);
    j.push_back({"geom", j_geom});
  } else {
    j.push_back({"geom", nullptr});
  }

  j.push_back({"boundary", edge.boundary});
  j.push_back({"nodes", edge.nodes});
  j.push_back({"weight", edge.weight});
}

void to_json(json &j, const EdgePtr &edge) { to_json(j, *edge.get()); }
void to_json(json &j, const EdgeWPtr &edge) {
  if (auto e = edge.lock())
    j = e->id;
  else
    j = nullptr;
}

void from_json(const json &j, Edge &edge) {
  from_json(j, static_cast<Feature &>(edge));

  from_json(j.at("geom").get<std::string>(), edge.geom);

  j.at("weight").get_to(edge.weight);

  j.at("nodes").get_to(edge.nodes);

  j.at("boundary").get_to(edge.boundary);
}

void from_json(const json &j, EdgePtr &edge) {
  edge = std::make_shared<Edge>();
  from_json(j, *edge.get());
}
void from_json(const json &j, EdgeWPtr &edge) {}

}  // namespace indoor_json
