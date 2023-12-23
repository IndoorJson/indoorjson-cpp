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

#include <geos/io/WKTReader.h>
#include <geos/io/WKTWriter.h>

namespace indoor_json {

using json = nlohmann::json;

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

void from_json(const json &j, Node &node) {
  from_json(j, static_cast<Feature &>(node));

  if (j.contains("geom")) {
    std::string wkt = j.at("geom").get<std::string>();
    geos::io::WKTReader reader;
    node.geom = reader.read(wkt);
  }
}

}  // namespace indoor_json
