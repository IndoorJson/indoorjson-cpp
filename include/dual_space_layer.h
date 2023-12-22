/*
 * dual_space_layer.h
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/22
 *
 */
#pragma once

#include <vector>

#include "edge.h"
#include "feature.h"
#include "node.h"
#include "ptr.h"

namespace indoor_json {

struct DualSpaceLayer : Feature {
  std::vector<NodePtr> nodes;
  std::vector<EdgePtr> edges;
};

DEFINE_PTR(DualSpaceLayer)

}  // namespace indoor_json