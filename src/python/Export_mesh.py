import time
import bmesh as bm
import numpy as np
import bpy


def get_arrays(obj,scene):
    #object to world transformation
    transform=np.array(obj.matrix_world,copy=False)
    mesh=obj.to_mesh(scene,True,"RENDER",calc_tessface=True)
    #vertices
    nvert=len(mesh.vertices)
    #position of verts
    P=np.empty(nvert*3,"float32")
    #normals of verts
    N=np.empty(nvert*3,"float32")
    
    #Polygons
    
    nQuades=len(mesh.tessfaces)
    QuadesIndices=np.empty(nQuades*4,"float32")
    
    #get Values
    mesh.tessfaces.foreach_get("vertices_raw",QuadesIndices)
    mesh.vertices.foreach_get("co",P)
    mesh.vertices.foreach_get("normal",P)
    
    return (transform,QuadesIndices,nQuades,nvert,P,N)

if __name__=="__main__":
    start=time.time()
    obj=bpy.context.object
    a=get_arrays(obj,bpy.context.scene)
    bpy.types.JPCENGINE.test(obj.name,a[0],a[1],a[2],a[3],a[3],a[4])
    print("\n")
    print(time.time()-start)