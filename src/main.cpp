/*
 * main.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/20
 *
 */


#include <geos/geom/Geometry.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/Envelope.h>
#include <geos/io/WKTWriter.h>

#include <iostream>
#include <nlohmann/json-schema.hpp>

#include <serialization.h>
#include <indoor_features.h>

#include <glog/logging.h>

using nlohmann::json;
using nlohmann::json_schema::json_validator;

static const json rectangle_schema = R"(
{
     "$schema": "http://json-schema.org/draft-07/schema#",
     "title": "A rectangle",
     "properties": {
         "width": {
             "$ref": "#/definitions/length",
             "default": 20
         },
         "height": {
             "$ref": "#/definitions/length"
         }
     },
     "definitions": {
         "length": {
             "type": "integer",
             "minimum": 1,
             "default": 10
         }
     }
 })"_json;

int main(int argc, char* argv[]) {

  auto factory = geos::geom::GeometryFactory::create();

  std::initializer_list<geos::geom::Coordinate> coordList = {
      {1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}};
  geos::geom::CoordinateSequence cs(coordList);

  auto ls = factory->createLineString(cs);

  geos::io::WKTWriter writer;
  LOG(INFO) << writer.write(ls.get()) << std::endl;

  try {
    json_validator validator{rectangle_schema};
    /* validate empty json -> will be expanded by the default values defined
    in the schema */
    json rectangle = "{}"_json;
    const auto default_patch = validator.validate(rectangle);
    rectangle = rectangle.patch(default_patch);
    LOG(INFO) << rectangle.dump() << std::endl;  // {"height":10,"width":20}
  } catch (const std::exception &e) {
    std::cerr << "Validation of schema failed: " << e.what() << "\n";
    return EXIT_FAILURE;
  }

  indoor_json::Node node;
  node.id = "$123";
  node.name = "my node";
  node.description = "description of node";
  node.external_ref = "https://indoorgml.org/";
  node.envelope.reset(new geos::geom::Envelope(0.1, 1.04, 2.05, 3.06));
  node.geom = factory->createLineString(cs);

  indoor_json::EdgePtr edge;
  edge.reset(new indoor_json::Edge());
  edge->id = "@edge_id";
  node.edges.emplace_back(indoor_json::EdgeWPtr(edge));

  indoor_json::CellSpacePtr space;
  space.reset(new indoor_json::CellSpace());
  space->id = "$space_id";
  node.space = indoor_json::CellSpaceWPtr(space);

  json j;
  to_json(j, node);
  std::string json_str = j.dump(2);
  LOG(INFO) << json_str << std::endl;

  json j2 = json::parse(json_str);
  indoor_json::Feature feature2 = j2.get<indoor_json::Feature>();

  json j3;
  to_json(j3, feature2);
  LOG(INFO) << j3.dump(2) << std::endl;

  return EXIT_SUCCESS;
}
