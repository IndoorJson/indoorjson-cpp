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

  json base;
  to_json(base, static_cast<const Feature &>(layer));
  j.merge_patch(base);
}
void to_json(json &j, const DualSpaceLayerPtr &layer) {
  to_json(j, *layer.get());
}
void from_json(const json &j, DualSpaceLayer &layer) {
  j.at("nodes").get_to(layer.nodes);
  j.at("edges").get_to(layer.edges);
}
void from_json(const json &j, DualSpaceLayerPtr &layer) {
  layer = std::make_shared<DualSpaceLayer>();
  from_json(j, *layer.get());
}
}  // namespace indoor_json
