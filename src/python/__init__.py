#    Addon info
from . import engine

bl_info = {
    'name': 'JPCEngine',
    'author': 'Jeremy Funk, Peer Drescher & Christian Libner',
    'location': 'Rendertab',
    'category': 'Render'
    }

import bpy
def register():
	engine.register()
def unregister():
	engine.unregister()
	
