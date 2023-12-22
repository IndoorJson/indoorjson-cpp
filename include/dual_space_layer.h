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

#include <memory>
#include <vector>

#include "ptr.h"
#include "edge.h"
#include "node.h"

namespace indoor_json {

struct DualSpaceLayer {
  std::vector<NodePtr> nodes;
  std::vector<EdgePtr> edges;
};

DEFINE_PTR(DualSpaceLayer)

}  // namespace indoor_json