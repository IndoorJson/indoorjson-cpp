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
  json base;
  to_json(base, static_cast<const Feature &>(boundary));
  j.merge_patch(base);

  if (boundary.geom != nullptr) {
    geos::io::WKTWriter writer;
    j.push_back({"geom", writer.write(boundary.geom.get())});
  } else {
    j.push_back({"geom", nullptr});
  }

  j.push_back({"edge", boundary.edge});
  j.push_back({"spaces", boundary.spaces});
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
  from_json(j, static_cast<Feature &>(boundary));

  from_json(j.at("geom").get<std::string>(), boundary.geom);

  j.at("edge").get_to(boundary.edge);

  j.at("spaces").get_to(boundary.spaces);
}
void from_json(const json &j, CellBoundaryPtr &boundary) {
  boundary = std::make_shared<CellBoundary>();
  from_json(j, *boundary.get());
}
void from_json(const json &j, CellBoundaryWPtr &boundary) {}

}  // namespace indoor_json
