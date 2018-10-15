from . import test
from . import Scene_types
import bpy,os
class JPCEngine(bpy.types.RenderEngine):
    bl_idname="JPCENGINE"
    bl_label="JPC-Engine"
    
    JPCvariations={}

    def update(self,data,scene):
        #referenz: ["WORLDSTART","ANIMATIONSTART","FRAMESTART","RENDER","FRAMEEND","ANIMATIONEND","WORLDEND"]
        states=scene.JPC_state_manager
        if not states.ready:
            #bind render to data
            states.render_setup(scene)
            states.Status="WORLDSTART"
        elif not states.scene==scene:
            #ueberfruefen ob Scene gleich geblieben ist
            if states.Status=="FRAMEEND":
                states.Status="ANIMATIONEND"
            if not state.Status=="WORLDEND":
                state.Status="WORLDEND"
        if self.is_animation:
            if scene.frame_start==scene.frame_current:
                states.Status="ANIMATIONSTART"
        else:
            states.Status="ANIMATIONSTART"
        states.Status="FRAMESTART"


    def render(self,scene):
        print("render")

        states=scene.JPC_state_manager
        #init rendern
        states.Status="RENDER"
        
        states.Status="FRAMEEND"
        if self.is_animation:
             if scene.frame_end==scene.frame_current:
                 states.Status="ANIMATIONEND"
        else:
            states.Status="ANIMATIONEND"



    def __init__(self):
        print("hi")

    def test(*args):
        return test.test(*args)



def register():
    st=Scene_types.State_manager()
    bpy.types.Scene.JPC_state_manager=st
    path=os.path.realpath(__file__)[:-10]+"\\Shapes"
    print(path)
    Scene_types.register_a_type(bpy.types.Object,
                                path,st)

    bpy.utils.register_class(JPCEngine)

    from bl_ui import (
            properties_render,
            properties_material,
            )
    properties_render.RENDER_PT_render.COMPAT_ENGINES.add(JPCEngine.bl_idname)
    properties_material.MATERIAL_PT_preview.COMPAT_ENGINES.add(JJPCEngine.bl_idname)


def unregister():
    bpy.utils.unregister_class(JPCEngine)
    from bl_ui import (
            properties_render,
            properties_material,
            )
    properties_render.RENDER_PT_render.COMPAT_ENGINES.remove(JPCEngine.bl_idname)
    properties_material.MATERIAL_PT_preview.COMPAT_ENGINES.remove(JPCEngine.bl_idname)