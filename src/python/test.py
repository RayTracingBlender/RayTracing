
from .src import _JPCEngine

import numpy as np

def fill_array(collection,prop,dtype,size=1):
    arr=np.empty(len(collection)*size,dtype)
    collection.foreach_get(prop,arr)
    return arr

def test(*args):
    return _JPCEngine.size(*args)

def mesh_add(*args):
    #bpy.types.JPCENGINE.test(bpy.data.meshes['Cube'])
    mesh=args[0]
    verts=mesh.vertices
    #get verts
    lverts=fill_array(verts,"co",float,size=3)
    print("Lverts: ",lverts)
    _JPCEngine.mesh_add_triangle(lverts)
