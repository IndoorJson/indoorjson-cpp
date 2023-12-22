/*
 * serialization.h
 *
 * Copyright (c) 2023 Syrius Robotics
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/22
 *
 */

#pragma once

#include <nlohmann/json.hpp>

#include "cell_space.h"
#include "indoor_features.h"

using json = nlohmann::json;

namespace indoor_json {

void to_json(json &j, const Feature &feature) {
  j = json{{"id", feature.id}};
  if (!feature.name.empty()) j.push_back({"name", feature.name});
  if (!feature.description.empty())
    j.push_back({"description", feature.description});
  if (!feature.external_ref.empty())
    j.push_back({"external_ref", feature.external_ref});
  if (feature.envelope != nullptr)
    j.push_back({"envelope", feature.envelope->toString()});
}

void from_json(const json &j, Feature &feature) {
  j.at("id").get_to(feature.id);
  if (j.contains("name")) j.at("name").get_to(feature.name);
  if (j.contains("description"))
    j.at("description").get_to(feature.description);
  if (j.contains("external_ref"))
    j.at("external_ref").get_to(feature.external_ref);
  if (j.contains("envelope"))
    feature.envelope.reset(
        new geos::geom::Envelope(j.at("envelope").get<std::string>()));
}

void to_json(json &j, const Node &node) {
  to_json(j, static_cast<const Feature &>(node));

  if (node.geom != nullptr) {
    geos::io::WKTWriter writer;
    j.push_back({"geom", writer.write(node.geom.get())});
  } else {
    j.push_back({"geom", nullptr});
  }

  if (auto space = node.space.lock())
    j.push_back({"space", space->id});
  else
    j.push_back({"space", nullptr});

  json j_edges = json::array();
  for (const auto &pedge : node.edges) {
    if (auto edge = pedge.lock())
      j_edges.push_back(edge->id);
    else
      j_edges.push_back(nullptr);
  }
  j.push_back({"edges", j_edges});
}

void to_json(json& j, const CellSpace& space) {
  to_json(j, static_cast<const Feature &>(space));

  if (space.geom != nullptr) {
    geos::io::WKTWriter writer;
    j.push_back({"geom", writer.write(space.geom.get())});
  } else {
    j.push_back({"geom", nullptr});
  }

  if (auto node = space.node.lock())
    j.push_back({"node", node->id});
  else
    j.push_back({"node", nullptr});

  json j_boundaries = json::array();
  for (const auto &pboundary : space.boundaries) {
    if (auto boundary = pboundary.lock())
      j_boundaries.push_back(boundary->id);
    else
      j_boundaries.push_back(nullptr);
  }
  j.push_back({"boundaries", j_boundaries});
}

}  // namespace indoor_json