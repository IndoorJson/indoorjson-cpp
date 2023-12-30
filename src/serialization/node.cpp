/*
 * File Name: node.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/23
 *
 */
#include <serialization.h>

namespace indoor_json {

using json = nlohmann::json;

void to_json(json &j, const Node &node) {
  json base;
  to_json(base, static_cast<const Feature &>(node));
  j.merge_patch(base);

  if (node.geom != nullptr) {
    json j_geom;
    to_json(j_geom, node.geom);
    j.push_back({"geom", j_geom});
  } else {
    j.push_back({"geom", nullptr});
  }

  j.push_back({"space", node.space});
  j.push_back({"edges", node.edges});
}

void to_json(json &j, const NodePtr &node) { to_json(j, *node.get()); }

void to_json(json &j, const NodeWPtr &node) {
  if (auto n = node.lock())
    j = n->id;
  else
    j = nullptr;
}

void from_json(const json &j, Node &node) {
  from_json(j, static_cast<Feature &>(node));
  from_json(j.at("geom").get<std::string>(), node.geom);
  j.at("space").get_to(node.space);
  j.at("edges").get_to(node.edges);
  from_json(j, static_cast<Feature &>(node));
}

void from_json(const json &j, NodePtr &node) {
  node = std::make_shared<Node>();
  from_json(j, *node.get());
}

void from_json(const json &j, NodeWPtr &node) {}

}  // namespace indoor_json
