/*
 * File Name: cell_space.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/23
 *
 */
#include <geos/io/WKTReader.h>
#include <geos/io/WKTWriter.h>
#include <serialization.h>

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

  j.push_back({"node", space.node});

  j.push_back({"boundaries", space.boundaries});
}

void to_json(json &j, const CellSpacePtr &space) { to_json(j, *space.get()); }
void to_json(json &j, const CellSpaceWPtr &space) {
  if (auto s = space.lock())
    j = s->id;
  else
    j = nullptr;
}

void from_json(const json &j, CellSpace &space) {
  from_json(j, static_cast<Feature &>(space));

  from_json(j.at("geom").get<std::string>(), space.geom);

  j.at("boundaries").get_to(space.boundaries);

  j.at("node").get_to(space.node);
}
void from_json(const json &j, CellSpacePtr &space) {
  from_json(j, *space.get());
}
void from_json(const json &j, CellSpaceWPtr &space) {}

}  // namespace indoor_json
