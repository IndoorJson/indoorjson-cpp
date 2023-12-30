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
  j = {{"space", node.space}, {"edges", node.edges}, {"geom", node.geom}};
  to_json(j, static_cast<const Feature &>(node));
}

void from_json(const json &j, Node &node) {
  j.at("geom").get_to(node.geom);
  j.at("space").get_to(node.space);
  j.at("edges").get_to(node.edges);
  from_json(j, static_cast<Feature &>(node));
}

}  // namespace indoor_json
