/*
 * File Name: thematic_layer.cpp
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
#include <thematic_layer.h>

namespace indoor_json {

using json = nlohmann::json;

NLOHMANN_JSON_SERIALIZE_ENUM(Theme, {{Theme::Topographic, "Topographic"},
                                     {Theme::Sensor, "Sensor"},
                                     {Theme::Logical, "Logical"},
                                     {Theme::Unknown, "Unknown"},
                                     {Theme::Property, "Property"},
                                     {Theme::Other, "Other"}})

void to_json(json &j, const ThematicLayer &layer) {
  j = {{"theme", layer.theme},
       {"primal_space", layer.primal_space},
       {"dual_space", layer.dual_space}};
  to_json(j, static_cast<const Feature &>(layer));
}

void from_json(const json &j, ThematicLayer &layer) {
  j.at("theme").get_to(layer.theme);
  j.at("primal_space").get_to(layer.primal_space);
  j.at("dual_space").get_to(layer.dual_space);
  from_json(j, static_cast<Feature &>(layer));
}

}  // namespace indoor_json
