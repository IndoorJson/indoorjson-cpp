/*
 * ptr.h
 *
 * Copyright (c) 2023 Syrius Robotics
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/22
 *
 */
#pragma once

#include <memory>

#define DEFINE_PTR(type)                   \
  using type##Ptr = std::shared_ptr<type>; \
  using type##WPtr = std::weak_ptr<type>;

#define FORWARD_DEC_WPTR(type) \
  struct type;                 \
  using type##WPtr = std::weak_ptr<type>;
