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

namespace indoor_json {

void to_json(nlohmann::json &j, const CellSpace &space) {
  j = {{"node", space.node},
       {"boundaries", space.boundaries},
       {"geom", space.geom}};
  to_json(j, static_cast<const Feature &>(space));
}

void from_json(const nlohmann::json &j, CellSpace &space) {
  j.at("geom").get_to(space.geom);
  j.at("boundaries").get_to(space.boundaries);
  j.at("node").get_to(space.node);
  from_json(j, static_cast<Feature &>(space));
}

}  // namespace indoor_json
