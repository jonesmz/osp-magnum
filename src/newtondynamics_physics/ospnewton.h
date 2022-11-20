/**
 * Open Space Program
 * Copyright © 2019-2021 Open Space Program Project
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

#include <osp/Active/activetypes.h>
#include <osp/Active/SysPhysics.h>

#include <osp/id_map.h>

#include <Newton.h>

#include <longeron/id_management/registry_stl.hpp>


namespace ospnewton
{

struct DeleterNewtonBody
{
    void operator() (NewtonBody const* pCollision)
    { NewtonDestroyBody(pCollision); }
};

using NwtBodyPtr_t = std::unique_ptr<NewtonBody const, DeleterNewtonBody>;

struct DeleterNewtonCollision
{
    void operator() (NewtonCollision const* pCollision)
    { NewtonDestroyCollision(pCollision); }
};

using ACompNwtCollider_t = std::unique_ptr<NewtonCollision const, DeleterNewtonCollision>;

//using ForceFactor_t = void (*)(
//        ActiveEnt, ViewProjMatrix const&, UserData_t) noexcept;

using NewtonBodyId = uint32_t;

/**
 * @brief Represents an instance of a Newton physics world in the scane
 */
struct ACtxNwtWorld
{

    struct Deleter
    {
        void operator() (NewtonWorld* pNwtWorld) { NewtonDestroy(pNwtWorld); }
    };

    ACtxNwtWorld(int threadCount)
     : m_world(NewtonCreate())
    {
        NewtonWorldSetUserData(m_world.get(), this);
    }

    // note: important that m_nwtBodies and m_nwtColliders are destructed
    //       before m_nwtWorld
    std::unique_ptr<NewtonWorld, Deleter> m_world;

    lgrn::IdRegistryStl<NewtonBodyId>                   m_bodyIds;
    std::vector<NwtBodyPtr_t>                           m_bodyPtrs;
    std::vector<osp::active::ActiveEnt>                 m_bodyToEnt;
    osp::IdMap_t<osp::active::ActiveEnt, NewtonBodyId>  m_entToBody;

    osp::active::acomp_storage_t<ACompNwtCollider_t>    m_colliders;

    osp::active::acomp_storage_t<osp::active::ACompTransform> *m_pTransform;
};




}
