from . import test
import bpy
class JPCEngine(bpy.types.RenderEngine):
    bl_idname="JPCENGINE"
    bl_label="JPC-Engine"

    def test(*args):
        return test.test(*args)


def register():
    bpy.utils.register_class(JPCEngine)
def unregister():
    bpy.utils.unregister_class(JPCEngine)