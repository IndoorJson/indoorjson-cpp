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

void to_json(json &j, const Theme &theme) {
  switch (theme) {
    case Theme::Topographic:
      j = "Topographic";
      break;
    case Theme::Sensor:
      j = "Sensor";
      break;
    case Theme::Logical:
      j = "Logical";
      break;
    case Theme::Unknown:
      j = "Unknown";
      break;
    case Theme::Property:
      j = "Property";
      break;
    case Theme::Other:
      j = "Other";
      break;
  }
}

void to_json(json &j, const ThematicLayer &layer) {
  j = {{"theme", layer.theme},
       {"primal_space", layer.primal_space},
       {"dual_space", layer.dual_space}};
}
void to_json(json &j, const ThematicLayerPtr &layer) {
  to_json(j, *layer.get());
}
void from_json(const json &j, ThematicLayer &layer) {
  j.at("theme").get_to(layer.theme);
  j.at("primal_space").get_to(layer.primal_space);
  j.at("dual_space").get_to(layer.dual_space);
}
void from_json(const json &j, ThematicLayerPtr &layer) {
  from_json(j, *layer.get());
}
}  // namespace indoor_json
