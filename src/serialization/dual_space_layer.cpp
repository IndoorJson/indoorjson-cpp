/*
 * File Name: dual_space.cpp
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
}
void to_json(json &j, const DualSpaceLayerPtr &layer) {
  to_json(j, *layer.get());
}
void from_json(const json &j, DualSpaceLayer &layer) {
  j.at("nodes").get_to(layer.nodes);
  j.at("edges").get_to(layer.edges);
}
void from_json(const json &j, DualSpaceLayerPtr &layer) {
  from_json(j, *layer.get());
}
}  // namespace indoor_json
