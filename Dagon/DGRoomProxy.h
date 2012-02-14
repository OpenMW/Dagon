////////////////////////////////////////////////////////////
//
// DAGON - An Adventure Game Engine
// Copyright (c) 2011 Senscape s.r.l.
// All rights reserved.
//
// NOTICE: Senscape permits you to use, modify, and
// distribute this file in accordance with the terms of the
// license agreement accompanying it.
//
////////////////////////////////////////////////////////////

#ifndef DG_ROOMPROXY_H
#define DG_ROOMPROXY_H

////////////////////////////////////////////////////////////
// NOTE: This header file should never be included directly.
// It's auto-included by DGProxy.h
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "DGControl.h"
#include "DGRoom.h"

////////////////////////////////////////////////////////////
// Interface
////////////////////////////////////////////////////////////

class DGRoomProxy {
public:
    static const char className[];
    static Luna<DGRoomProxy>::RegType methods[];
    
    // Constructor
    DGRoomProxy(lua_State *L) {
        // TODO: Support custom room names with a second parameter
        
        r = new DGRoom;
        r->setName(luaL_checkstring(L, 1));
        
        // Register the new room
        DGControl::getInstance().registerObject(r);
    }
    
    // Destructor
    ~DGRoomProxy() { delete r; }
    
    // Add a node to the room
    int addNode(lua_State *L) {
        if (DGCheckProxy(L, 1) == DGObjectNode) {
            r->addNode(DGProxyToNode(L, 1));
            
            // Now we get the metatable of the added node and set it
            // as a return value
            lua_getfield(L, LUA_REGISTRYINDEX, DGNodeProxyName);
            lua_setmetatable(L, -2);
            
            return 1;
        }
        
        return 0;
    }
    
    DGRoom* ptr() { return r; }
    
private:
    DGRoom* r;    
};

////////////////////////////////////////////////////////////
// Static definitions
////////////////////////////////////////////////////////////

const char DGRoomProxy::className[] = DGRoomProxyName;

Luna<DGRoomProxy>::RegType DGRoomProxy::methods[] = {
    method(DGRoomProxy, addNode),
    {0,0}
};

#endif // DG_ROOMPROXY_H