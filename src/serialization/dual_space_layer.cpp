/*
 * File Name: dual_space_layer.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/25
 *
 */
#include <geos/io/WKTReader.h>
#include <geos/io/WKTWriter.h>
#include <serialization.h>
#include <dual_space_layer.h>

namespace indoor_json {

using json = nlohmann::json;

void to_json(json &j, const DualSpaceLayer &layer) {
  j = {{"nodes", layer.nodes},
       {"edges", layer.edges}};
  to_json(j, static_cast<const Feature &>(layer));
}

void from_json(const json &j, DualSpaceLayer &layer) {
  j.at("nodes").get_to(layer.nodes);
  j.at("edges").get_to(layer.edges);
  from_json(j, static_cast<Feature &>(layer));
}

}  // namespace indoor_json
