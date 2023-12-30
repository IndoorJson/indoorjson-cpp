/*
 * File Name: cell_boundary.cpp
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

namespace indoor_json {

using json = nlohmann::json;

void to_json(json &j, const CellBoundary &boundary) {
  j = {{"edge", boundary.edge},
       {"spaces", boundary.spaces},
       {"geom", boundary.geom}};
  to_json(j, static_cast<const Feature &>(boundary));
}

void to_json(json &j, const CellBoundaryPtr &boundary) {
  to_json(j, *boundary.get());
}
void to_json(json &j, const CellBoundaryWPtr &boundary) {
  if (auto s = boundary.lock())
    j = s->id;
  else
    j = nullptr;
}

void from_json(const json &j, CellBoundary &boundary) {
  j.at("geom").get_to(boundary.geom);
  j.at("edge").get_to(boundary.edge);
  j.at("spaces").get_to(boundary.spaces);
  from_json(j, static_cast<Feature &>(boundary));
}
void from_json(const json &j, CellBoundaryPtr &boundary) {
  boundary = std::make_shared<CellBoundary>();
  from_json(j, *boundary.get());
}
void from_json(const json &j, CellBoundaryWPtr &boundary) {}

}  // namespace indoor_json
