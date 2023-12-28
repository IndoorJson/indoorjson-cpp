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
#include <connection.h>

namespace indoor_json {

using json = nlohmann::json;

void to_json(json &j, const Connection &connection) {
  j = {{"comment", connection.comment},
       {"layers", connection.layers},
       {"spaces", connection.spaces},
       {"nodes", connection.nodes}};

  json base;
  to_json(base, static_cast<const Feature &>(connection));
  j.merge_patch(base);
}

void to_json(json &j, const ConnectionPtr &connection) {
  to_json(j, *connection.get());
}

void from_json(const json &j, Connection &connection) {
  j.at("comment").get_to(connection.comment);
  j.at("layers").get_to(connection.layers);
  j.at("spaces").get_to(connection.spaces);
  j.at("nodes").get_to(connection.nodes);
}

void from_json(const json &j, ConnectionPtr &connection) {
  from_json(j, *connection.get());
}
}  // namespace indoor_json