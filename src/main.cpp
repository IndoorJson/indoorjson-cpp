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
#include <geos/io/WKTWriter.h>

#include <iostream>
#include <nlohmann/json-schema.hpp>

#include <indoor_features.h>

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

int main() {
  auto factory = geos::geom::GeometryFactory::create();

  std::initializer_list<geos::geom::Coordinate> coordList = {
      {1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}};
  geos::geom::CoordinateSequence cs(coordList);

  auto ls = factory->createLineString(cs);

  geos::io::WKTWriter writer;
  std::cout << writer.write(ls.get()) << std::endl;

  try {
    json_validator validator{rectangle_schema};
    /* validate empty json -> will be expanded by the default values defined
    in the schema */
    json rectangle = "{}"_json;
    const auto default_patch = validator.validate(rectangle);
    rectangle = rectangle.patch(default_patch);
    std::cout << rectangle.dump() << std::endl;  // {"height":10,"width":20}
  } catch (const std::exception &e) {
    std::cerr << "Validation of schema failed: " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
