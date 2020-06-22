#pragma once

#include <entt/entt.hpp>

namespace osp
{

class SysNewton;

// in case Newton Dynamics gets swapped out, one can implement a system class
// with all the same methods
using SysPhysics = SysNewton;

using ActiveEnt = entt::entity;

class ActiveScene;

constexpr unsigned gc_heir_physics_level = 1;

}