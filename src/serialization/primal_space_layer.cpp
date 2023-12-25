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
#include <primal_space_layer.h>

namespace indoor_json {

using json = nlohmann::json;

void to_json(json &j, const PrimalSpaceLayer &layer) {
  j = {{"spaces", layer.spaces}, {"boundaries", layer.boundaries}};
}
void to_json(json &j, const PrimalSpaceLayerPtr &layer) {
  to_json(j, *layer.get());
}
void from_json(const json &j, PrimalSpaceLayer &layer) {
  j.at("spaces").get_to(layer.spaces);
  j.at("boundaries").get_to(layer.boundaries);
}
void from_json(const json &j, PrimalSpaceLayerPtr &layer) {
  from_json(j, *layer.get());
}

}  // namespace indoor_json
