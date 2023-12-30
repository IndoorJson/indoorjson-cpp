/*
 * File Name: indoor_features.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/25
 *
 */
#include <glog/logging.h>
#include <serialization.h>

namespace indoor_json {

void to_json(nlohmann::json& j, const IndoorFeatures& indoor_features) {
  j = {{"layers", indoor_features.layers},
       {"connections", indoor_features.connections}};
  to_json(j, static_cast<const Feature&>(indoor_features));
}

void HandleWeakRef(IndoorFeatures& indoor_features);

void from_json(const nlohmann::json& j, IndoorFeatures& indoor_features) {
  j.at("layers").get_to(indoor_features.layers);
  j.at("connections").get_to(indoor_features.connections);
  from_json(j, static_cast<Feature&>(indoor_features));

  HandleWeakRef(indoor_features);
}

template <typename T>
std::vector<std::weak_ptr<T>> HandleVectorWeakPtr(nlohmann::json j);

template <typename T>
std::weak_ptr<T> HandleWeakPtr(nlohmann::json j);

void HandleWeakRef(IndoorFeatures& indoor_features) {
  for (ConnectionPtr connection : indoor_features.connections) {
    nlohmann::json j = IdLookup<Connection>::Ins().Feature2Json(connection);
    connection->layers = HandleVectorWeakPtr<ThematicLayer>(j.at("layers"));
    connection->spaces = HandleVectorWeakPtr<CellSpace>(j.at("spaces"));
    connection->nodes = HandleVectorWeakPtr<Node>(j.at("nodes"));
  }

  for (ThematicLayerPtr layer : indoor_features.layers) {
    for (CellSpacePtr space : layer->primal_space->spaces) {
      nlohmann::json j = IdLookup<CellSpace>::Ins().Feature2Json(space);
      space->boundaries = HandleVectorWeakPtr<CellBoundary>(j.at("boundaries"));
      space->node = HandleWeakPtr<Node>(j.at("node"));
    }
    for (CellBoundaryPtr boundary : layer->primal_space->boundaries) {
      nlohmann::json j = IdLookup<CellBoundary>::Ins().Feature2Json(boundary);
      boundary->spaces = HandleVectorWeakPtr<CellSpace>(j.at("spaces"));
      boundary->edge = HandleWeakPtr<Edge>(j.at("edge"));
    }
    for (NodePtr node : layer->dual_space->nodes) {
      nlohmann::json j = IdLookup<Node>::Ins().Feature2Json(node);
      node->edges = HandleVectorWeakPtr<Edge>(j.at("edges"));
      node->space = HandleWeakPtr<CellSpace>(j.at("space"));
    }
    for (EdgePtr edge : layer->dual_space->edges) {
      nlohmann::json j = IdLookup<Edge>::Ins().Feature2Json(edge);
      edge->nodes = HandleVectorWeakPtr<Node>(j.at("nodes"));
      edge->boundary = HandleWeakPtr<CellBoundary>(j.at("boundary"));
    }
  }

  IdLookupClearAll();
}

template <typename T>
std::vector<std::weak_ptr<T>> HandleVectorWeakPtr(nlohmann::json j) {
  std::vector<std::weak_ptr<T>> results;
  for (nlohmann::json j : j) {
    if (j.is_null()) continue;
    auto ptr = IdLookup<T>::Ins().Id2Ptr(j.get<std::string>());
    results.push_back(ptr);
  }
  return results;
}

template <typename T>
std::weak_ptr<T> HandleWeakPtr(nlohmann::json j) {
  if (j.is_null()) return std::weak_ptr<T>();
  return IdLookup<T>::Ins().Id2Ptr(j.get<std::string>());
}

}  // namespace indoor_json