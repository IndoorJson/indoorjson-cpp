/*
 * File Name: geometry.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/24
 *
 */
#include <geos/geom/Geometry.h>
#include <geos/io/WKTReader.h>
#include <geos/io/WKTWriter.h>
#include <serialization.h>

#include <glog/logging.h>

namespace indoor_json {

  // We put to_json and from_json in "indoor_json" namespace.
  // So we can not use j.get<geos::geom::Geometry::Ptr>();
  // Instead we can call to_json and from_json explicitly.

using json = nlohmann::json;

void to_json(json &j, const geos::geom::Geometry::Ptr &geom) {
  geos::io::WKTWriter writer;
  std::string wkt_str =  writer.write(geom.get());
  j = wkt_str;
}

void from_json(const json &j, geos::geom::Geometry::Ptr &geom) {
  std::string wkt_str = j.get<std::string>();
  geos::io::WKTReader reader;
  geom = reader.read(wkt_str);
}

}  // namespace indoor_json
