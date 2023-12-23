/*
 * File Name: cell_space.cpp
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

void to_json(json &j, const CellSpace &space) {
  to_json(j, static_cast<const Feature &>(space));

  if (space.geom != nullptr) {
    geos::io::WKTWriter writer;
    j.push_back({"geom", writer.write(space.geom.get())});
  } else {
    j.push_back({"geom", nullptr});
  }

  if (auto node = space.node.lock())
    j.push_back({"node", node->id});
  else
    j.push_back({"node", nullptr});

  json j_boundaries = json::array();
  for (const auto &pboundary : space.boundaries) {
    if (auto boundary = pboundary.lock())
      j_boundaries.push_back(boundary->id);
    else
      j_boundaries.push_back(nullptr);
  }
  j.push_back({"boundaries", j_boundaries});
}

}  // namespace indoor_json
