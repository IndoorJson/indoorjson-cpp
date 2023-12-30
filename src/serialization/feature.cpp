/*
 * File Name: feature.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/23
 *
 */
#include <glog/logging.h>
#include <serialization.h>

namespace indoor_json {

using json = nlohmann::json;

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
  if (j.contains("id")) j.at("id").get_to(feature.id);
  if (j.contains("name")) j.at("name").get_to(feature.name);
  if (j.contains("description"))
    j.at("description").get_to(feature.description);
  if (j.contains("external_ref"))
    j.at("external_ref").get_to(feature.external_ref);
  if (j.contains("envelope"))
    feature.envelope.reset(
        new geos::geom::Envelope(j.at("envelope").get<std::string>()));
}

}  // namespace indoor_json