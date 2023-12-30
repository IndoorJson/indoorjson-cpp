/*
 * File Name: connection.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/25
 *
 */
#include <serialization.h>

namespace indoor_json {

void to_json(nlohmann::json &j, const Connection &connection) {
  j = {{"comment", connection.comment},
       {"layers", connection.layers},
       {"spaces", connection.spaces},
       {"nodes", connection.nodes}};
  to_json(j, static_cast<const Feature &>(connection));
}

void from_json(const nlohmann::json &j, Connection &connection) {
  j.at("comment").get_to(connection.comment);
  j.at("layers").get_to(connection.layers);
  j.at("spaces").get_to(connection.spaces);
  j.at("nodes").get_to(connection.nodes);
  from_json(j, static_cast<Feature &>(connection));
}

}  // namespace indoor_json
